#pragma once
#define TAPPING_TERM 150
#define MAX_TAM_TAPS 3
#define MAX_WK 5
#define WK_TIMEOUT 2500

// #define DEBUG_MATRIX_SCAN_RATE

#ifdef OLED_DRIVER_ENABLE
//#    define OLED_TIMEOUT 1000
//#    define OLED_SCROLL_TIMEOUT 1000
#    ifdef USE_SSD1306_128X32
// defaults are sufficient
#    endif

#    ifdef USE_SSD1306_128X64
#        define OLED_DISPLAY_128X64
#    endif

#    ifdef USE_SH1106_128X64
//    https://github.com/qmk/qmk_firmware/blob/bedb72b0bc30db906b436e2fc820a4a6559a7520/keyboards/dekunukem/duckypad/config.h#L50-L55
#        define OLED_IC OLED_IC_SH1106
#        define OLED_COLUMN_OFFSET 2
#        define OLED_DISPLAY_ADDRESS 0x3C
#        define OLED_COM_PINS COM_PINS_ALT
#        define OLED_DISPLAY_128X64
#    endif
#endif

#define TRIGGER_DISTANCE_MM 70
#define VL53L0X_INTERRUPT_PIN D5
