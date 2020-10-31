#pragma once
#include <report.h>
#include <stdint.h>

class HidGenericReportParser {
   public:
    report_keyboard_t report;
    uint16_t time_stamp;
    virtual void Parse(uint16_t vid, uint16_t pid, uint8_t iface, uint8_t endpoint, uint8_t len, uint8_t *buff);
};
