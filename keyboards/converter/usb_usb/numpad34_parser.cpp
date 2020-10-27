#include "numpad34_parser.h"
#include "usb_hid.h"

#include "debug.h"


void Numpad34ReportParser::Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf)
{
    // ::memcpy(&report, buf, sizeof(report_keyboard_t));
    // uprintf("#%2 buf: ", hid->GetAddress());
    // for (int i = 0; i < len; i++)
    // {
    //     uprintf("%02X", buf[i]);
    // }
    // uprintf("\r\n");

    // time_stamp = millis();

    // dprintf("input %d:", hid->GetAddress(), report.mods, report.reserved);
    // for (uint8_t i = 0; i < KEYBOARD_REPORT_KEYS; i++) {
    //     dprintf(" %02X", report.keys[i]);
    // }
    // dprint("\r\n");

    time_stamp = millis();

    xprintf("input %d: %d %d", hid->GetAddress(), len, is_rpt_id);
    for (uint8_t i = 0; i < len; i++) {
        xprintf(" %02X", buf[i]);
    }
    print("\n");
}
