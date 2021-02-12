#pragma once

// place overrides here

// #define NO_DEBUG
// #define NO_PRINT
#define NO_ACTION_LAYER
#define NO_ACTION_TAPPING
#define NO_ACTION_ONESHOT

#ifdef PRODUCT_ID
#undef PRODUCT_ID
#define PRODUCT_ID      0xBBBB
#endif

#ifdef DEVICE_VER
#undef DEVICE_VER
#define DEVICE_VER      0x0001
#endif

#ifdef PRODUCT
#undef PRODUCT
#define PRODUCT         Gary U2U Converter
#endif

