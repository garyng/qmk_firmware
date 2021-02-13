#pragma once

// place overrides here

// #define NO_DEBUG
// #define NO_PRINT
#define NO_ACTION_LAYER
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT

#ifdef PRODUCT_ID
#undef PRODUCT_ID
#define PRODUCT_ID 0xBBBB
#endif

#ifdef DEVICE_VER
#undef DEVICE_VER
#define DEVICE_VER 0x0001
#endif

#ifdef PRODUCT
#undef PRODUCT
#define PRODUCT Gary U2U Converter
#endif

#ifdef OLED_DRIVER_ENABLE
  // https://github.com/qmk/qmk_firmware/blob/bedb72b0bc30db906b436e2fc820a4a6559a7520/keyboards/dekunukem/duckypad/config.h#L50-L55
  #define OLED_DISPLAY_ADDRESS 0x3C
  #define OLED_DISPLAY_128X64
  #define OLED_COM_PINS COM_PINS_ALT

  #define OLED_IC OLED_IC_SH1106
  #define OLED_COLUMN_OFFSET 2

//   #define OLED_TIMEOUT 1000
//   #define OLED_SCROLL_TIMEOUT 1000
#endif

#ifdef ENCODER_ENABLE
    #define ENCODERS_PAD_A { D2 }
    #define ENCODERS_PAD_B { D3 }
#endif
