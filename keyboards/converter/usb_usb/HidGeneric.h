#pragma once
#include <usbhid.h>
#include "HidGenericReportParser.h"

// Modified from hidcomposite
class HidGeneric : public USBHID {
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

    uint8_t  bConfNum;      // configuration number
    uint8_t  bNumIface;     // number of interfaces in the configuration
    uint8_t  bNumEP;        // total number of EP in the configuration
    uint32_t qNextPollTime; // next poll time
    uint8_t  pollInterval;
    bool     bPollEnable; // poll enable flag

    static const uint16_t constBuffLen = 64; // event buffer length

    void          Initialize();
    HIDInterface *FindInterface(uint8_t iface, uint8_t alt, uint8_t proto);

    void ZeroMemory(uint8_t len, uint8_t *buf);

protected:
    EpInfo       epInfo[totalEndpoints];
    HIDInterface hidInterfaces[maxHidInterfaces];

    bool bHasReportId;

    uint16_t PID, VID; // PID and VID of connected device

public:
    HidGeneric(USB *p);

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

    void SetReportParser(HidGenericReportParser *parser) {
        _reportParser = parser;
    }
};
