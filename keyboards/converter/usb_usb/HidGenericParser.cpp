#include "HidGenericParser.h"
#include "debug.h"

void HidGenericReportParser::Parse(uint16_t vid, uint16_t pid, uint8_t iface, uint8_t endpoint, uint8_t len, uint8_t *buff) {
    dprintf("vid: %04X pid: %04X", vid, pid);
    dprintf(" iface: %02X endpoint: %02X", iface, endpoint);
    dprint(" buf: ");
    for (uint8_t i = 0; i < len; ++i) {
        dprintf("%02X", buff[i]);
    }
    dprint("\n\r");
}
