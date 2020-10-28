#pragma once
#include <stdint.h>

class HidGenericReportParser {
   public:
    virtual void Parse(uint16_t vid, uint16_t pid, uint8_t iface, uint8_t endpoint, uint8_t len, uint8_t *buff);
};
