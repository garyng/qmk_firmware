#include "wrapping_key.h"

#include <quantum.h>
#include <timer.h>
#include "tap_auto_mod.h"
#include "debug.h"

#ifndef MAX_WK
#    define MAX_WK 1

const uint16_t wki_to_wk[MAX_WK] = {
    [0] = KC_F13,
};

const uint16_t wki_to_kc[MAX_WK] = {
    [0] = KC_NO,
};

#endif

#ifdef WK_TIMEOUT
static uint16_t timeout_timer = 0;
#endif

static uint8_t current_wki = 0;
static uint8_t wk_keys_tracker[MAX_WK];
static bool    _tapped_current_wk_on_init = false;

/**
 * Called when the current wk is changed
 */
__attribute__((weak)) void wk_on_changed_user(uint8_t old_wki, uint16_t old_wk, uint8_t new_wki, uint16_t new_wk) {}

void wk_on_changed(uint8_t old_wki, uint8_t new_wki) {
    if (old_wki == new_wki) return;

    dprintf("old wki: %d, new wki: %d\n", old_wki, new_wki);
    wk_on_changed_user(old_wki, wki_to_wk[old_wki], new_wki, wki_to_wk[new_wki]);
}

/**
 * Tap the current wk on startup
 */
void tap_current_wk_on_init(void) {
    if (_tapped_current_wk_on_init) return;

    // delay a few seconds before tapping the key
    // immediately tapping it on keyboard_post_init_user and matrix_scan_user
    // cant guarantee the host will receive it
    if (timer_read() < 1000) return;

    wk_tap_current();
    _tapped_current_wk_on_init = true;
    dprintln("tapped current");
}

void update_timeout_timer(void) {
#ifdef WK_TIMEOUT
    if (current_wki != default_wki) {
        timeout_timer = timer_read();
    }
    dprintf("elapsed: %d\n", timeout_timer);
#endif
}

bool process_wk_user(uint16_t keycode, keyrecord_t *record) {
    uint16_t current_wk = wki_to_wk[current_wki];

    dprintf("wki: %d wk: %X kc: 0x%X tracker: %d\n", current_wki, current_wk, wki_to_kc[current_wki], wk_keys_tracker[current_wki]);

    // if it's a wrapping key
    if ((keycode & QK_WRAPPING_KEY) == QK_WRAPPING_KEY) {
        uint8_t old_wki = current_wki;
        current_wki = keycode - QK_WRAPPING_KEY;
        process_tam_user(wki_to_kc[current_wki], record);
        update_timeout_timer();
        wk_on_changed(old_wki, current_wki);
        return false;
    }
    // if it's a normal key
    if (keycode != current_wk) {
        process_tam_user(keycode, record);
        update_timeout_timer();
        return false;
    }

    return true;
}

void wk_tap_current(void) {
    uint16_t current_wk = wki_to_wk[current_wki];
    uint16_t current_kc = wki_to_kc[current_wki];

    register_code16(current_wk);
    register_code16(current_kc);

    unregister_code16(current_kc);
    unregister_code16(current_wk);
}

void matrix_scan_wk_user(void) {
    tap_current_wk_on_init();
 #ifdef WK_TIMEOUT
    if (current_wki != default_wki && timer_elapsed(timeout_timer) > WK_TIMEOUT) {
        dprintf("wki reset to %d", default_wki);
        current_wki = default_wki;
        timeout_timer = 0;
        wk_tap_current();
    }
 #endif
}

void pre_register_key(tap_auto_mod_state_t *state) {
    uint16_t current_wk = wki_to_wk[current_wki];

    if (wk_keys_tracker[current_wki] == 0) {
        register_code16(current_wk);
    }
    wk_keys_tracker[current_wki]++;
}

void post_unregister_key(tap_auto_mod_state_t *state) {
    uint16_t current_wk = wki_to_wk[current_wki];

    wk_keys_tracker[current_wki]--;
    if (wk_keys_tracker[current_wki] == 0) {
        unregister_code16(current_wk);
    }
}

uint16_t get_current_wk(void) {
    return wki_to_wk[current_wki];   
}

void set_current_wki(uint8_t wki) {
    current_wki = wki;
}

/**
 * Tap the code with the current wrapping key
 */
void wk_tap_code(uint16_t code) {
    // todo: how about tam?
    uint16_t current_wk = wki_to_wk[current_wki];

    register_code(current_wk);
    register_code16(code);

    unregister_code16(code);
    unregister_code(current_wk);
}

__attribute__((weak)) void wk_render_oled_default_impl(uint8_t current_wki) {
    // default implementation is in oled.c
}

__attribute__((weak)) void wk_render_oled_keymap(uint8_t current_wki) {
    wk_render_oled_default_impl(current_wki);
}

void wk_render_oled_user(void) {
    wk_render_oled_keymap(current_wki);
}
