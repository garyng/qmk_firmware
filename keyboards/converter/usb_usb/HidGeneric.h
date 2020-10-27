#pragma once
#include <usbhid.h>

//
//// Modified from USBHIDMultimediaKbd.ino
//// This will select all interfaces available
//class HidGeneric : public HIDComposite {
//public:
//    HidGeneric(USB *p)
//        : HIDComposite(p) { bHasReportId = true; };
//
//protected:
//    void ParseHIDData(USBHID *hid, uint8_t ep, bool is_rpt_id, uint8_t len, uint8_t *buf); // Called by the HIDComposite library
//    bool SelectInterface(uint8_t iface, uint8_t proto);
//};
//
//bool HidGeneric::SelectInterface(uint8_t iface, uint8_t proto) {
//    xprintf("iface %d, proto %d", iface, proto);
//    return true;
//}
//
//void HidGeneric::ParseHIDData(USBHID *hid, uint8_t ep, bool is_rpt_id, uint8_t len, uint8_t *buf) {
//    if (len && buf) {
//        xprintf("ep: %d ", ep, is_rpt_id);
//        for (uint8_t i = 0; i < len; i++) {
//            xprintf("%02X ", buf[i]);
//        }
//        print("\n\r");
//    }
//}
//
//
//

class HidGenericReportParser {
public:
    virtual void Parse(uint16_t vid, uint16_t pid, uint8_t iface, uint8_t endpoint, uint8_t len, uint8_t *buff);
};

void HidGenericReportParser::Parse(uint16_t vid, uint16_t pid, uint8_t iface, uint8_t endpoint, uint8_t len, uint8_t *buff) {
    xprintf("vid: %04X pid: %04X", vid, pid);
    xprintf(" iface: %02X endpoint: %02X\n\r", iface, endpoint);
}


class HidGeneric : public USBHID {
    //struct ReportParser {
    //    uint8_t          rptId;
    //    HIDReportParser *rptParser;
    //} rptParsers[MAX_REPORT_PARSERS];
    HidGenericReportParser *_reportParser;

    // HID class specific descriptor type and length info obtained from HID descriptor
    HID_CLASS_DESCRIPTOR_LEN_AND_TYPE descrInfo[HID_MAX_HID_CLASS_DESCRIPTORS];

    // Returns HID class specific descriptor length by its type and order number
    uint16_t GetHidClassDescrLen(uint8_t type, uint8_t num);

    struct HIDInterface {
        struct {
            uint8_t bmInterface : 3;
            uint8_t bmAltSet : 3;
            uint8_t bmProtocol : 2;
        };
        uint8_t epIndex[maxEpPerInterface];
    };

    uint8_t  bConfNum;       // configuration number
    uint8_t  bNumIface;      // number of interfaces in the configuration
    uint8_t  bNumEP;         // total number of EP in the configuration
    uint32_t qNextPollTime;  // next poll time
    uint8_t  pollInterval;
    bool     bPollEnable;  // poll enable flag

    static const uint16_t constBuffLen = 64;  // event buffer length

    void          Initialize();
    HIDInterface *FindInterface(uint8_t iface, uint8_t alt, uint8_t proto);

    void ZeroMemory(uint8_t len, uint8_t *buf);

   protected:
    EpInfo       epInfo[totalEndpoints];
    HIDInterface hidInterfaces[maxHidInterfaces];

    bool bHasReportId;

    uint16_t PID, VID;  // PID and VID of connected device

    // HID implementation
    //HIDReportParser *GetReportParser(uint8_t id);

    //virtual uint8_t OnInitSuccessful() { return 0; };

    //virtual void ParseHIDData(USBHID *hid, uint8_t ep, bool is_rpt_id, uint8_t len, uint8_t *buf);

   public:
    HidGeneric(USB *p, HidGenericReportParser *reportParser);

    // HID implementation
    //bool SetReportParser(uint8_t id, HIDReportParser *prs);

    // USBDeviceConfig implementation
    uint8_t Init(uint8_t parent, uint8_t port, bool lowspeed);
    uint8_t Release();
    uint8_t Poll();

    virtual uint8_t GetAddress() { return bAddress; };

    virtual bool isReady() { return bPollEnable; };

    // UsbConfigXtracter implementation
    void EndpointXtract(uint8_t conf, uint8_t iface, uint8_t alt, uint8_t proto, const USB_ENDPOINT_DESCRIPTOR *ep);

    // Send report - do not mix with SetReport()!
    uint8_t SndRpt(uint16_t nbytes, uint8_t *dataptr);

    // Returns true if we should listen on an interface, false if not
    virtual bool SelectInterface(uint8_t iface, uint8_t proto);
};



HidGeneric::HidGeneric(USB *p, HidGenericReportParser *reportParser) : USBHID(p), _reportParser(reportParser), qNextPollTime(0), pollInterval(0), bPollEnable(false), bHasReportId(true) {
    Initialize();

    if (pUsb) pUsb->RegisterDeviceClass(this);
}


uint16_t HidGeneric::GetHidClassDescrLen(uint8_t type, uint8_t num) {
    for (uint8_t i = 0, n = 0; i < HID_MAX_HID_CLASS_DESCRIPTORS; i++) {
        if (descrInfo[i].bDescrType == type) {
            if (n == num) return descrInfo[i].wDescriptorLength;
            n++;
        }
    }
    return 0;
}

void HidGeneric::Initialize() {
    //for (uint8_t i = 0; i < MAX_REPORT_PARSERS; i++) {
    //    rptParsers[i].rptId     = 0;
    //    rptParsers[i].rptParser = NULL;
    //}

    for (uint8_t i = 0; i < HID_MAX_HID_CLASS_DESCRIPTORS; i++) {
        descrInfo[i].bDescrType        = 0;
        descrInfo[i].wDescriptorLength = 0;
    }
    for (uint8_t i = 0; i < maxHidInterfaces; i++) {
        hidInterfaces[i].bmInterface = 0;
        hidInterfaces[i].bmProtocol  = 0;

        for (uint8_t j = 0; j < maxEpPerInterface; j++) hidInterfaces[i].epIndex[j] = 0;
    }
    for (uint8_t i = 0; i < totalEndpoints; i++) {
        epInfo[i].epAddr      = 0;
        epInfo[i].maxPktSize  = (i) ? 0 : 8;
        epInfo[i].bmSndToggle = 0;
        epInfo[i].bmRcvToggle = 0;
        epInfo[i].bmNakPower  = (i) ? USB_NAK_NOWAIT : USB_NAK_MAX_POWER;
    }
    bNumEP       = 1;
    bNumIface    = 0;
    bConfNum     = 0;
    pollInterval = 0;
}

//bool HidGeneric::SetReportParser(uint8_t id, HIDReportParser *prs) {
//    for (uint8_t i = 0; i < MAX_REPORT_PARSERS; i++) {
//        if (rptParsers[i].rptId == 0 && rptParsers[i].rptParser == NULL) {
//            rptParsers[i].rptId     = id;
//            rptParsers[i].rptParser = prs;
//            return true;
//        }
//    }
//    return false;
//}
//
//HIDReportParser *HidGeneric::GetReportParser(uint8_t id) {
//    if (!bHasReportId) return ((rptParsers[0].rptParser) ? rptParsers[0].rptParser : NULL);
//
//    for (uint8_t i = 0; i < MAX_REPORT_PARSERS; i++) {
//        if (rptParsers[i].rptId == id) return rptParsers[i].rptParser;
//    }
//    return NULL;
//}

uint8_t HidGeneric::Init(uint8_t parent, uint8_t port, bool lowspeed) {
    const uint8_t constBufSize = sizeof(USB_DEVICE_DESCRIPTOR);

    uint8_t                buf[constBufSize];
    USB_DEVICE_DESCRIPTOR *udd = reinterpret_cast<USB_DEVICE_DESCRIPTOR *>(buf);
    uint8_t                rcode;
    UsbDevice *            p         = NULL;
    EpInfo *               oldep_ptr = NULL;
    uint8_t                len       = 0;

    uint8_t num_of_conf;  // number of configurations
    // uint8_t num_of_intf; // number of interfaces

    AddressPool &addrPool = pUsb->GetAddressPool();

    USBTRACE("HU Init\r\n");

    if (bAddress) return USB_ERROR_CLASS_INSTANCE_ALREADY_IN_USE;

    // Get pointer to pseudo device with address 0 assigned
    p = addrPool.GetUsbDevicePtr(0);

    if (!p) return USB_ERROR_ADDRESS_NOT_FOUND_IN_POOL;

    if (!p->epinfo) {
        USBTRACE("epinfo\r\n");
        return USB_ERROR_EPINFO_IS_NULL;
    }

    // Save old pointer to EP_RECORD of address 0
    oldep_ptr = p->epinfo;

    // Temporary assign new pointer to epInfo to p->epinfo in order to avoid toggle inconsistence
    p->epinfo = epInfo;

    p->lowspeed = lowspeed;

    // Get device descriptor
    rcode = pUsb->getDevDescr(0, 0, 8, (uint8_t *)buf);

    if (!rcode) len = (buf[0] > constBufSize) ? constBufSize : buf[0];

    if (rcode) {
        // Restore p->epinfo
        p->epinfo = oldep_ptr;

        goto FailGetDevDescr;
    }

    // Restore p->epinfo
    p->epinfo = oldep_ptr;

    // Allocate new address according to device class
    bAddress = addrPool.AllocAddress(parent, false, port);

    if (!bAddress) return USB_ERROR_OUT_OF_ADDRESS_SPACE_IN_POOL;

    // Extract Max Packet Size from the device descriptor
    epInfo[0].maxPktSize = udd->bMaxPacketSize0;

    // Assign new address to the device
    rcode = pUsb->setAddr(0, 0, bAddress);

    if (rcode) {
        p->lowspeed = false;
        addrPool.FreeAddress(bAddress);
        bAddress = 0;
        USBTRACE2("setAddr:", rcode);
        return rcode;
    }

    // delay(2); //per USB 2.0 sect.9.2.6.3

    USBTRACE2("Addr:", bAddress);

    p->lowspeed = false;

    p = addrPool.GetUsbDevicePtr(bAddress);

    if (!p) return USB_ERROR_ADDRESS_NOT_FOUND_IN_POOL;

    p->lowspeed = lowspeed;

    if (len) rcode = pUsb->getDevDescr(bAddress, 0, len, (uint8_t *)buf);

    if (rcode) goto FailGetDevDescr;

    VID = udd->idVendor;  // Can be used by classes that inherits this class to check the VID and PID of the connected device
    PID = udd->idProduct;
    USBTRACE2("VID:", VID);
    USBTRACE2("PID:", PID);

    num_of_conf = udd->bNumConfigurations;

    // Assign epInfo to epinfo pointer
    rcode = pUsb->setEpInfoEntry(bAddress, 1, epInfo);

    if (rcode) goto FailSetDevTblEntry;

    USBTRACE2("NC:", num_of_conf);

    for (uint8_t i = 0; i < num_of_conf; i++) {
        // HexDumper<USBReadParser, uint16_t, uint16_t> HexDump;
        ConfigDescParser<USB_CLASS_HID, 0, 0, CP_MASK_COMPARE_CLASS> confDescrParser(this);

        // rcode = pUsb->getConfDescr(bAddress, 0, i, &HexDump);
        rcode = pUsb->getConfDescr(bAddress, 0, i, &confDescrParser);

        if (rcode) goto FailGetConfDescr;

        if (bNumEP > 1) break;
    }  // for

    if (bNumEP < 2) return USB_DEV_CONFIG_ERROR_DEVICE_NOT_SUPPORTED;

    // Assign epInfo to epinfo pointer
    rcode = pUsb->setEpInfoEntry(bAddress, bNumEP, epInfo);

    USBTRACE2("Cnf:", bConfNum);

    // Set Configuration Value
    rcode = pUsb->setConf(bAddress, 0, bConfNum);

    if (rcode) goto FailSetConfDescr;

    USBTRACE2("NumIface:", bNumIface);

    for (uint8_t i = 0; i < bNumIface; i++) {
        if (hidInterfaces[i].epIndex[epInterruptInIndex] == 0) continue;

        USBTRACE2("SetIdle:", hidInterfaces[i].bmInterface);

        rcode = SetIdle(hidInterfaces[i].bmInterface, 0, 0);

        if (rcode && rcode != hrSTALL) goto FailSetIdle;
    }

    USBTRACE("HU configured\r\n");

    //OnInitSuccessful();

    bPollEnable = true;
    return 0;

FailGetDevDescr:
#ifdef DEBUG_USB_HOST
    NotifyFailGetDevDescr();
    goto Fail;
#endif

FailSetDevTblEntry:
#ifdef DEBUG_USB_HOST
    NotifyFailSetDevTblEntry();
    goto Fail;
#endif

FailGetConfDescr:
#ifdef DEBUG_USB_HOST
    NotifyFailGetConfDescr();
    goto Fail;
#endif

FailSetConfDescr:
#ifdef DEBUG_USB_HOST
    NotifyFailSetConfDescr();
    goto Fail;
#endif

FailSetIdle:
#ifdef DEBUG_USB_HOST
    USBTRACE("SetIdle:");
#endif

#ifdef DEBUG_USB_HOST
Fail:
    NotifyFail(rcode);
#endif
    Release();
    return rcode;
}

HidGeneric::HIDInterface *HidGeneric::FindInterface(uint8_t iface, uint8_t alt, uint8_t proto) {
    for (uint8_t i = 0; i < bNumIface && i < maxHidInterfaces; i++)
        if (hidInterfaces[i].bmInterface == iface && hidInterfaces[i].bmAltSet == alt && hidInterfaces[i].bmProtocol == proto) return hidInterfaces + i;
    return NULL;
}

void HidGeneric::EndpointXtract(uint8_t conf, uint8_t iface, uint8_t alt, uint8_t proto, const USB_ENDPOINT_DESCRIPTOR *pep) {
    // ErrorMessage<uint8_t>(PSTR("\r\nConf.Val"), conf);
    // ErrorMessage<uint8_t>(PSTR("Iface Num"), iface);
    // ErrorMessage<uint8_t>(PSTR("Alt.Set"), alt);

    bConfNum = conf;

    uint8_t       index  = 0;
    HIDInterface *piface = FindInterface(iface, alt, proto);

    // Fill in interface structure in case of new interface
    if (!piface) {
        piface              = hidInterfaces + bNumIface;
        piface->bmInterface = iface;
        piface->bmAltSet    = alt;
        piface->bmProtocol  = proto;
        bNumIface++;
    }

    if ((pep->bmAttributes & bmUSB_TRANSFER_TYPE) == USB_TRANSFER_TYPE_INTERRUPT) index = (pep->bEndpointAddress & 0x80) == 0x80 ? epInterruptInIndex : epInterruptOutIndex;

    if (!SelectInterface(iface, proto)) index = 0;

    if (index) {
        // Fill in the endpoint info structure
        epInfo[bNumEP].epAddr      = (pep->bEndpointAddress & 0x0F);
        epInfo[bNumEP].maxPktSize  = (uint8_t)pep->wMaxPacketSize;
        epInfo[bNumEP].bmSndToggle = 0;
        epInfo[bNumEP].bmRcvToggle = 0;
        epInfo[bNumEP].bmNakPower  = USB_NAK_NOWAIT;

        // Fill in the endpoint index list
        piface->epIndex[index] = bNumEP;  //(pep->bEndpointAddress & 0x0F);

        if (pollInterval < pep->bInterval)  // Set the polling interval as the largest polling interval obtained from endpoints
            pollInterval = pep->bInterval;

        bNumEP++;
    }
}

uint8_t HidGeneric::Release() {
    pUsb->GetAddressPool().FreeAddress(bAddress);

    bNumEP        = 1;
    bAddress      = 0;
    qNextPollTime = 0;
    bPollEnable   = false;
    return 0;
}

void HidGeneric::ZeroMemory(uint8_t len, uint8_t *buf) {
    for (uint8_t i = 0; i < len; i++) buf[i] = 0;
}

uint8_t HidGeneric::Poll() {
    uint8_t rcode = 0;

    if (!bPollEnable) return 0;

    if ((int32_t)((uint32_t)millis() - qNextPollTime) >= 0L) {
        qNextPollTime = (uint32_t)millis() + pollInterval;

        uint8_t buf[constBuffLen];

        for (uint8_t i = 0; i < bNumIface; i++) {
            uint8_t index = hidInterfaces[i].epIndex[epInterruptInIndex];

            if (index == 0) continue;

            uint16_t read = (uint16_t)epInfo[index].maxPktSize;

            ZeroMemory(constBuffLen, buf);

            uint8_t rcode = pUsb->inTransfer(bAddress, epInfo[index].epAddr, &read, buf);

            if (rcode) {
                if (rcode != hrNAK) USBTRACE3("(HidGeneric.h) Poll:", rcode, 0x81);
                continue;
            }

            if (read == 0) continue;

            if (read > constBuffLen) read = constBuffLen;

#if 0
                        Notify(PSTR("\r\nBuf: "), 0x80);

                        for(uint8_t i = 0; i < read; i++) {
                                D_PrintHex<uint8_t > (buf[i], 0x80);
                                Notify(PSTR(" "), 0x80);
                        }

                        Notify(PSTR("\r\n"), 0x80);
#endif
            //ParseHIDData(this, epInfo[index].epAddr, bHasReportId, (uint8_t)read, buf);

            //HIDReportParser *prs = GetReportParser(((bHasReportId) ? *buf : 0));

            //if (prs) prs->Parse(this, bHasReportId, (uint8_t)read, buf);

            _reportParser->Parse(VID, PID, i, epInfo[index].epAddr, (uint8_t)read, buf);
        }
    }
    return rcode;
}

// Send a report to interrupt out endpoint. This is NOT SetReport() request!
uint8_t HidGeneric::SndRpt(uint16_t nbytes, uint8_t *dataptr) { return pUsb->outTransfer(bAddress, epInfo[epInterruptOutIndex].epAddr, nbytes, dataptr); }

bool HidGeneric::SelectInterface(uint8_t iface, uint8_t proto) {
    xprintf("iface %d, proto %d\n\r", iface, proto);
    return true;
}
//
//void HidGeneric::ParseHIDData(USBHID *hid, uint8_t ep, bool is_rpt_id, uint8_t len, uint8_t *buf) {
//    if (len && buf) {
//        xprintf("ep: %d ", ep, is_rpt_id);
//        for (uint8_t i = 0; i < len; i++) {
//            xprintf("%02X ", buf[i]);
//        }
//        print("\n\r");
//    }
//}
