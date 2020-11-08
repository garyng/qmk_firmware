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

#ifndef NO_WK_TIMEOUT

#    ifndef WK_TIMEOUT
#        define WK_TIMEOUT 2000
#    endif

static uint16_t timeout_timer = 0;

#endif

static uint8_t current_wki = 0;
static uint8_t wk_keys_tracker[MAX_WK];

void update_timeout_timer(void) {
#ifndef NO_WK_TIMEOUT
    if (current_wki != default_wki) {
        timeout_timer = timer_read();
    }
    dprintf("elapsed: %d\n", timeout_timer);
#endif
}

bool process_wk_user(uint16_t keycode, keyrecord_t *record) {
    uint16_t current_wk = wki_to_wk[current_wki];

    dprintf("wki: %d wk: %X kc: 0x%X tracker: %d\n", current_wki, current_wk, wki_to_kc[current_wki], wk_keys_tracker[current_wki]);

    if ((keycode & QK_WRAPPING_KEY) == QK_WRAPPING_KEY) {
        current_wki = keycode - QK_WRAPPING_KEY;
        process_tam_user(wki_to_kc[current_wki], record);
        update_timeout_timer();
        return false;
    }
    if (keycode != current_wk) {
        process_tam_user(keycode, record);
        update_timeout_timer();
        return false;
    }

    return true;
}

void tap_wk_kc(void) {
    uint16_t current_wk = wki_to_wk[current_wki];
    uint16_t current_kc = wki_to_kc[current_wki];

    register_code(current_wk);
    register_code16(current_kc);

    unregister_code(current_wk);
    unregister_code16(current_kc);
}

void matrix_scan_wk_user(void) {
#ifndef NO_WK_TIMEOUT
    // todo: per key timeout?
    if (current_wki != default_wki && timer_elapsed(timeout_timer) > WK_TIMEOUT) {
        dprintf("wki reset to %d", default_wki);
        current_wki   = default_wki;
        timeout_timer = 0;
        tap_wk_kc();
    }
#endif
}

void pre_register_key(tap_auto_mod_state_t *state) {
    uint16_t current_wk = wki_to_wk[current_wki];

    if (wk_keys_tracker[current_wki] == 0) {
        register_code(current_wk);
    }
    wk_keys_tracker[current_wki]++;
}

void post_unregister_key(tap_auto_mod_state_t *state) {
    uint16_t current_wk = wki_to_wk[current_wki];

    wk_keys_tracker[current_wki]--;
    if (wk_keys_tracker[current_wki] == 0) {
        unregister_code(current_wk);
    }
}
