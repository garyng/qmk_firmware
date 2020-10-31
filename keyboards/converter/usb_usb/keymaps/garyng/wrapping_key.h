#pragma once
#include <action.h>
#include <stdint.h>

// todo: this will conflict with STENO_ENABLE
#define QK_WRAPPING_KEY 0x5A00
#define WK(index) (QK_WRAPPING_KEY | ((index)&0xFF))

extern const uint16_t wki_to_wk[];
extern const uint16_t wki_to_kc[];

bool process_wk_user(uint16_t keycode, keyrecord_t *record);
