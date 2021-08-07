#include QMK_KEYBOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <print.h>
#include <debug.h>
#include <eeconfig.h>
#include <host.h>
#include "distance_trigger.h"
#include "tap_auto_mod.h"
#include "user_config.h"
#include "wrapping_key.h"

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

__attribute__((weak)) void matrix_scan_keymap(void) {}

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }


/**
 * Callback for oled.c when wk is changed
 */
__attribute__((weak)) void wk_on_changed_user_oled(uint8_t old_wki, uint16_t old_wk, uint8_t new_wki, uint16_t new_wk) {}

/**
 * Callback for user_config.c when wk is changed
 */
__attribute__((weak)) void wk_on_changed_user_config(uint8_t old_wki, uint16_t old_wk, uint8_t new_wki, uint16_t new_wk) {}

void keyboard_post_init_user(void) {
    debug_enable = true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;

    keyboard_post_init_keymap();

#ifdef DISTANCE_TRIGGER_ENABLE
    dt_init();
#endif
    read_user_config();
}

// todo: reset if layer is changed but trackers aren't clear
// todo: tap dance to RESET

void matrix_scan_user(void) {
#ifdef DISTANCE_TRIGGER_ENABLE
    dt_get_distance();
#endif

    matrix_scan_wk_user();
    matrix_scan_tam_user();

    matrix_scan_keymap();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keymap(keycode, record)) {
        return false;
    }

    dprintf("keycode: 0x%02X\n", keycode);
    return process_wk_user(keycode, record);
}

void wk_on_changed_user(uint8_t old_wki, uint16_t old_wk, uint8_t new_wki, uint16_t new_wk) {
    wk_on_changed_user_oled(old_wki, old_wk, new_wki, new_wk);
    wk_on_changed_user_config(old_wki, old_wk, new_wki, new_wk);
}
