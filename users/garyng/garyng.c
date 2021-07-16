#include QMK_KEYBOARD_H

#include <stdio.h>
#include <stdlib.h>
#include <print.h>
#include <debug.h>
#include <host.h>
#include <oled_driver.h>
#include "distance_trigger.h"
#include "tap_auto_mod.h"
#include "wrapping_key.h"

__attribute__((weak)) void keyboard_post_init_keymap(void) {}

__attribute__((weak)) void matrix_scan_keymap(void) {}

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

__attribute__((weak)) void oled_task_keymap(void) {}

void keyboard_post_init_user(void) {
    debug_enable = true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;

    keyboard_post_init_keymap();

#ifdef DISTANCE_TRIGGER_ENABLE
    dt_init();
#endif
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

void render_matrix_scan_rate(void) {
#ifdef DEBUG_MATRIX_SCAN_RATE
    char str[10];
    sprintf(str, "%lu Hz", get_matrix_scan_rate());
    oled_write_ln_P(PSTR(""), false);
    oled_write(str, false);
#endif
}

void oled_task_user(void) {
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
    oled_write_ln_P(PSTR(""), false);

    wk_render_oled_user();
    tam_render_oled_user();

    render_matrix_scan_rate();
#ifdef DISTANCE_TRIGGER_ENABLE
    dt_render_oled_user();
#endif
    oled_task_keymap();
}

