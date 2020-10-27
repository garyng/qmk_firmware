#ifndef NUMPAD43_PARSER_H
#define NUMPAD43_PARSER_H

#include "usbhid.h"
#include "report.h"

class Numpad34ReportParser : public HIDReportParser
{
public:
    uint16_t time_stamp;
    virtual void Parse(USBHID *hid, bool is_rpt_id, uint8_t len, uint8_t *buf);
};

#endif
