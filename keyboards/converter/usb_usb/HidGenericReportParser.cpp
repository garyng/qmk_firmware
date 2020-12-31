#include "HidGenericReportParser.h"
#include "usbhid.h"

#include "debug.h"

typedef struct {
    uint8_t reportId;  // Report ID = 0x03 (3)
    // Collection: CA:ConsumerControl
    uint8_t ScanNextTrack : 1;                   // Usage 0x000C00B5: Scan Next Track, Value = 0 to 1, Physical = Value
    uint8_t ScanPreviousTrack : 1;               // Usage 0x000C00B6: Scan Previous Track, Value = 0 to 1, Physical = Value
    uint8_t Stop : 1;                            // Usage 0x000C00B7: Stop, Value = 0 to 1, Physical = Value
    uint8_t PlayPause : 1;                       // Usage 0x000C00CD: Play/Pause, Value = 0 to 1, Physical = Value
    uint8_t Mute : 1;                            // Usage 0x000C00E2: Mute, Value = 0 to 1, Physical = Value
    uint8_t Daily : 1;                           // Usage 0x000C00A2: Daily, Value = 0 to 1, Physical = Value
    uint8_t VolumeIncrement : 1;                 // Usage 0x000C00E9: Volume Increment, Value = 0 to 1, Physical = Value
    uint8_t VolumeDecrement : 1;                 // Usage 0x000C00EA: Volume Decrement, Value = 0 to 1, Physical = Value
    uint8_t AlConsumerControlConfiguration : 1;  // Usage 0x000C0183: AL Consumer Control Configuration, Value = 0 to 1, Physical = Value
    uint8_t AlLocalMachineBrowser : 1;           // Usage 0x000C0194: AL Local Machine Browser, Value = 0 to 1, Physical = Value
    uint8_t AlSpreadsheet : 1;                   // Usage 0x000C0186: AL Spreadsheet, Value = 0 to 1, Physical = Value
    uint8_t AlPresentationApp : 1;               // Usage 0x000C0188: AL Presentation App, Value = 0 to 1, Physical = Value
    uint8_t AlEmailReader : 1;                   // Usage 0x000C018A: AL Email Reader, Value = 0 to 1, Physical = Value
    uint8_t DisplayBrightnessIncrement : 1;      // Usage 0x000C006F: Display Brightness Increment, Value = 0 to 1, Physical = Value
    uint8_t DisplayBrightnessDecrement : 1;      // Usage 0x000C0070: Display Brightness Decrement, Value = 0 to 1, Physical = Value
    uint8_t AlInternetBrowser : 1;               // Usage 0x000C0196: AL Internet Browser, Value = 0 to 1, Physical = Value
    uint8_t AcSearch : 1;                        // Usage 0x000C0221: AC Search, Value = 0 to 1, Physical = Value
    uint8_t AcHome : 1;                          // Usage 0x000C0223: AC Home, Value = 0 to 1, Physical = Value
    uint8_t AcBack : 1;                          // Usage 0x000C0224: AC Back, Value = 0 to 1, Physical = Value
    uint8_t AcForward : 1;                       // Usage 0x000C0225: AC Forward, Value = 0 to 1, Physical = Value
    uint8_t AlCalculator : 1;                    // Usage 0x000C0192: AL Calculator, Value = 0 to 1, Physical = Value
    uint8_t AcRefresh : 1;                       // Usage 0x000C0227: AC Refresh, Value = 0 to 1, Physical = Value
    uint8_t AcBookmarks : 1;                     // Usage 0x000C022A: AC Bookmarks, Value = 0 to 1, Physical = Value
    uint8_t Power : 1;                           // Usage 0x000C0030: Power, Value = 0 to 1, Physical = Value
} __attribute__((packed)) numpad_32keys_media_keys_t;

void HidGenericReportParser::Parse(uint16_t vid, uint16_t pid, uint8_t iface, uint8_t endpoint, uint8_t len, uint8_t *buff) {
    dprintf("\nvid: %04X pid: %04X", vid, pid);
    dprintf(" iface: %02X endpoint: %02X", iface, endpoint);
    dprint(" buf: ");
    for (uint8_t i = 0; i < len; ++i) {
        dprintf("%02X", buff[i]);
    }
    dprint("\n");

    time_stamp = millis();

    // try parse report id, as it is usually the first byte
    uint8_t reportId = (uint8_t)*buff;

    if (vid == 0x258A && pid == 0x0131) {
        // 34 keys numpad

        if (reportId == 3) {
            // media keys

            numpad_32keys_media_keys_t mediaKeysReport = {};
            ::memcpy(&mediaKeysReport, buff, sizeof(numpad_32keys_media_keys_t));

            report = {};
            if (mediaKeysReport.AcSearch == 1) {
                report.keys[0] = KC_WWW_SEARCH;
            }
            if (mediaKeysReport.AlCalculator == 1) {
                report.keys[1] = KC_CALCULATOR;
            }
        }
    }

    if (vid == 0x046D && pid == 0xC52B) {
        // logitech unifying receiver
    }

    if (iface == 0 && endpoint == 1) {
        // seems like most keyboards send normal keys via this endpoint
        ::memcpy(&report, buff, sizeof(report_keyboard_t));
    }
}
