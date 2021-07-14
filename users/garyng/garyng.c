#include QMK_KEYBOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <print.h>
#include "tap_auto_mod.h"
#include "wrapping_key.h"
#include <debug.h>
#include <host.h>
#include <oled_driver.h>

__attribute__ ((weak))
void keyboard_post_init_keymap(void) {}

__attribute__ ((weak))
void matrix_scan_keymap(void) {}

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__ ((weak))
void oled_task_keymap(void) {}


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

void oled_task_user(void) {
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    oled_write_ln_P(PSTR(""), false);

    tam_render_oled();
    wk_render_oled();
    oled_task_keymap();
}
