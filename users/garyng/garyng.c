#include QMK_KEYBOARD_H
#include <stdio.h>
#include <stdlib.h>
#include <print.h>
#include "tap_auto_mod.h"
#include "wrapping_key.h"

__attribute__ ((weak))
void keyboard_post_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }


void keyboard_post_init_user(void) {
    debug_enable=true;
    //debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;

    keyboard_post_init_keymap();
}

// todo: reset if layer is changed but trackers aren't clear
// todo: tap dance to RESET

void matrix_scan_user(void) {
    matrix_scan_wk_user();
    matrix_scan_tam_user();

    matrix_scan_keymap();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (!process_record_keymap(keycode, record))
    {
        return false;
    }

    dprintf("keycode: 0x%02X\n", keycode);
    return process_wk_user(keycode, record);
}
