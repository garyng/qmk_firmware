#include "tap_auto_mod.h"
#include "quantum.h"
#include "debug.h"
#include "action_tapping.h"


#ifndef MAX_TAM_TAPS
#define MAX_TAM_TAPS 3
const uint16_t tam_mod_maps[MAX_TAM_TAPS + 1] = {
    [2] = KC_LCTL,  // 2 taps
    [3] = KC_LALT,  // 3 taps
};
#endif

static tap_auto_mod_state_t tam_state;

void tam_on_each(tap_auto_mod_state_t *state) {
    uint8_t count = state->count;
    dprintf("on each tap, count: %d\n\r", count);

    if (state->count == MAX_TAM_TAPS) {
        pre_register_key(state);
        register_code16(tam_mod_maps[count]);
        register_code16(state->keycode);
        state->finished = true;
    }
}

void tam_finished(tap_auto_mod_state_t *state) {
    if (state->finished) return;
    state->finished = true;
    dprint("tam finished\n\r");

    uint8_t count = state->count;

    pre_register_key(state);
    if (count > 1) {
        register_code16(tam_mod_maps[count]);
    }
    register_code16(state->keycode);
}

void tam_reset(tap_auto_mod_state_t *state) {
    if (state->pressed) return;
    dprint("tam reset\n\r");
    uint8_t count = state->count;

    unregister_code16(state->keycode);
    if (count > 1) {
        unregister_code16(tam_mod_maps[count]);
    }
    post_unregister_key(state);

    state->count    = 0;
    state->timer    = 0;
    state->finished = false;
    state->keycode  = 0;
}

void tam_handle_interruption(uint16_t keycode, keyrecord_t *record, tap_auto_mod_state_t *state) {
    // if is key down
    if (!record->event.pressed) return;

    // if there is in flight key
    if (state->count == 0) return;

    // if the key is different
    if (keycode == state->keycode) return;

    dprintf("interrupted by %04X\r\n", keycode);

    tam_finished(state);
    // set it to key up otherwise reset won't run
    state->pressed = false;
    tam_reset(state);
}

void process_tam_user(uint16_t keycode, keyrecord_t *record) {
    tam_handle_interruption(keycode, record, &tam_state);

    tam_state.pressed = record->event.pressed;
    if (record->event.pressed) {
        tam_state.count++;
        tam_state.timer   = timer_read();
        tam_state.keycode = keycode;

        tam_on_each(&tam_state);

    } else {
        if (tam_state.count > 0 && tam_state.finished) {
            tam_reset(&tam_state);
        }
    }
}

void matrix_scan_tam_user(void) {
    if (tam_state.count > 0 && timer_elapsed(tam_state.timer) > get_tapping_term(tam_state.keycode, NULL)) {
        tam_finished(&tam_state);
        tam_reset(&tam_state);
    }
}
