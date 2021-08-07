#pragma once

// place overrides here

// #define NO_DEBUG
// #define NO_PRINT
#define NO_ACTION_LAYER
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT

#ifdef PRODUCT_ID
#    undef PRODUCT_ID
#    define PRODUCT_ID 0xBBBB
#endif

#ifdef DEVICE_VER
#    undef DEVICE_VER
#    define DEVICE_VER 0x0001
#endif

#ifdef PRODUCT
#    undef PRODUCT
#    define PRODUCT Gary U2U Converter
#endif

#ifdef WK_TIMEOUT
#    undef WK_TIMEOUT
#endif

#ifdef ENCODER_ENABLE
#   define ENCODERS_PAD_A { D2, C0 }
#   define ENCODERS_PAD_B { D3, C1 }
#   define DIP_SWITCH_PINS { D4, C2 }
#endif
