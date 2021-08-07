#include <stdio.h>
#include <host.h>
#include <oled_driver.h>

#include "distance_trigger.h"
#include "tap_auto_mod.h"
#include "wrapping_key.h"

__attribute__((weak)) void oled_task_keymap(void) {}

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
    //dt_render_oled_user();
#endif

    oled_task_keymap();
}

void wk_render_oled_default_impl(uint8_t current_wki) {
    oled_write_P(PSTR("WK: "), false);
    oled_write_char('1' + current_wki, false);
    oled_write_ln_P(PSTR(""), false);
}

void tam_render_oled_default_impl(tap_auto_mod_state_t *state) {
    oled_write_P(PSTR("TAM: "), false);
    oled_write_char('0' + state->count, false);
    oled_write_ln_P(PSTR(""), false);
}

void wk_on_changed_user_oled(uint8_t old_wki, uint16_t old_wk, uint8_t new_wki, uint16_t new_wk) {
    // turn on oled whenever wk is changed
    oled_on();
}
