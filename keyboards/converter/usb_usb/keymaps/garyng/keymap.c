/*
Copyright 2017 Balz Guenat <balz.guenat@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>
#include <stdlib.h>
#include <print.h>

#define MAX_WK 5

enum Dances {
    TD_HC
};

void td_each(qk_tap_dance_state_t *state, void *user_data) {
   /* register_code(KC_F20);
    if (state->count == 2) {
        register_code(KC_LCTL);
    }
    register_code(KC_HOME);*/
    dprint("td each\n\r");
}

void td_finished(qk_tap_dance_state_t *state, void *user_data) {
    dprint("td finished\n\r");
}


void td_reset(qk_tap_dance_state_t *state, void *user_data) {
   /* unregister_code(KC_HOME);

    if (state->count == 2) {
        unregister_code(KC_LCTL);
    }
     unregister_code(KC_F20);*/
    dprint("td reset\n\r");
}


qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_HC] = ACTION_TAP_DANCE_FN_ADVANCED(td_each, td_finished, td_reset)
};

//qk_tap_dance_action_t tap_dance_actions[] = {
//    [TD_HC] = ACTION_TAP_DANCE_DOUBLE(KC_HOME, C(KC_HOME))
//};


enum Layers {
    LAYER0 = 0,
    LAYER1,
    LAYER2,
    LAYER3,
    LAYER4
};

enum WrappingKeys {
    WK_0 = SAFE_RANGE,
    WK_1,
    WK_2,
    WK_3,
    WK_4
};

const uint16_t layers_to_kc[MAX_WK] = {
    [LAYER0] = KC_F13,
    [LAYER1] = KC_F14,
    [LAYER2] = KC_F15,
    [LAYER3] = KC_F16,
    [LAYER4] = KC_F17
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: plain Qwerty without layer switching
     *         ,---------------. ,---------------. ,---------------.
     *         |F13|F14|F15|F16| |F17|F18|F19|F20| |F21|F22|F23|F24|
     * ,---.   |---------------| |---------------| |---------------| ,-----------. ,---------------. ,-------.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau| |VDn|VUp|Mut|Pwr| | Help  |
     * `---'   `---------------' `---------------' `---------------' `-----------' `---------------' `-------'
     * ,-----------------------------------------------------------. ,-----------. ,---------------. ,-------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|JPY|Bsp| |Ins|Hom|PgU| |NmL|  /|  *|  -| |Stp|Agn|
     * |-----------------------------------------------------------| |-----------| |---------------| |-------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  | |Del|End|PgD| |  7|  8|  9|  +| |Mnu|Und|
     * |-----------------------------------------------------------| `-----------' |---------------| |-------|
     * |CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  :|  #|Retn|               |  4|  5|  6|KP,| |Sel|Cpy|
     * |-----------------------------------------------------------|     ,---.     |---------------| |-------|
     * |Shft|  <|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /| RO|Shift |     |Up |     |  1|  2|  3|KP=| |Exe|Pst|
     * |-----------------------------------------------------------| ,-----------. |---------------| |-------|
     * |Ctl|Gui|Alt|MHEN|HNJ| Space  |H/E|HENK|KANA|Alt|Gui|App|Ctl| |Lef|Dow|Rig| |   0   |  .|Ent| |Fnd|Cut|
     * `-----------------------------------------------------------' `-----------' `---------------' `-------'
     */

    // numpad layout
    //  ,-----------. ,---------------.
    //  |PrS|xxx|xxx| |Esc|Tab|  =|Bsp|
    //  `-----------' `---------------'
    //  ,-----------. ,---------------.
    //  |NmL|Hom|PgU| | 00|  /|  *|  -|
    //  |-----------| |---------------|
    //  |Del|End|PgD| |  7|  8|  9|   |
    //  `-----------' |-----------|  +|
    //                |  4|  5|  6|   |
    //      ,---.     |---------------|
    //      |Up |     |  1|  2|  3|   |
    //  ,-----------. |-----------|Ent|
    //  |Lef|Dow|Rig| |   0   |  .|   |
    //  `-----------' `---------------'
    [0] = LAYOUT_all(
                      KC_F13,  KC_F14,  KC_F15,  KC_F16, KC_F17, KC_F18, KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,
    WK_3,             KC_F1,   KC_F2,   KC_F3,   KC_F4,  KC_F5,  KC_F6,  KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,               KC_PSCR, KC_SLCK, KC_PAUS,    KC_VOLD, KC_VOLU, KC_MUTE, KC_PWR,     KC_HELP,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,   KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, WK_1,    KC_JYEN, WK_0,        KC_INS,  KC_HOME, KC_PGUP,    KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS,    KC_STOP, KC_AGIN,
    WK_2,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,   KC_U,   KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_BSLS,     KC_DEL,  TD(TD_HC),  KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PPLS,    KC_MENU, KC_UNDO,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_NUHS, KC_ENT,                                    KC_P4,   KC_P5,   KC_P6,   KC_PCMM,    KC_SLCT, KC_COPY,
    KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RO,   KC_RSFT,              KC_UP,               KC_P1,   KC_P2,   KC_P3,   KC_PEQL,    KC_EXEC, KC_PSTE,
    KC_LCTL, KC_LGUI, KC_LALT, KC_MHEN, KC_HANJ,         KC_SPC,         KC_HAEN, KC_HENK, KC_KANA, KC_RALT, KC_RGUI, KC_APP,  KC_RCTL,     KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,            KC_PDOT, KC_PENT,    KC_FIND, KC_CUT,
    KC_CALCULATOR, KC_WWW_SEARCH
    ),
    /*[LAYER1] = LAYOUT_all(
                      ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______, ______, ______,
    ______,           ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______, ______, ______,             ______,______,______,    ______,______,______,______,    ______,
    ______,  ______,  ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______, ______, ______, ______,     ______,______,______,    ______,______,______,______,    ______,______,
    ______,  ______,  ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______, ______,         ______,     ______,______,______,    ______,______,______,______,    ______,______,
    ______,  ______,  ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______,         ______, ______,                              ______,______,______,______,    ______,______,
    ______,  ______,  ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______,         ______, ______,            ______,           ______,______,______,______,    ______,______,
    ______,  ______,  ______,  ______,  ______,         ______,           ______, ______,  ______, ______, ______, ______, ______,     ______,______,______,    ______,       ______,______,    ______,______,
    ______,  ______
    ),*/
    // [LAYER2] = LAYOUT_all(
    //                   ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______, ______, ______,
    // ______,           ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______, ______, ______,             ______,______,______,    ______,______,______,______,    ______,
    // ______,  ______,  ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______, ______, ______, ______,     ______,______,______,    ______,______,______,______,    ______,______,
    // ______,  ______,  ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______, ______,         ______,     ______,______,______,    ______,______,______,______,    ______,______,
    // ______,  ______,  ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______,         ______, ______,                              ______,______,______,______,    ______,______,
    // ______,  ______,  ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______,         ______, ______,            ______,           ______,______,______,______,    ______,______,
    // ______,  ______,  ______,  ______,  ______,         ______,           ______, ______,  ______, ______, ______, ______, ______,     ______,______,______,    ______,       ______,______,    ______,______
    // ),
    // [LAYER3] = LAYOUT_all(
    //                   ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______, ______, ______,
    // ______,           ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______, ______, ______,             ______,______,______,    ______,______,______,______,    ______,
    // ______,  ______,  ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______, ______, ______, ______,     ______,______,______,    ______,______,______,______,    ______,______,
    // ______,  ______,  ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______, ______,         ______,     ______,______,______,    ______,______,______,______,    ______,______,
    // ______,  ______,  ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______,         ______, ______,                              ______,______,______,______,    ______,______,
    // ______,  ______,  ______,  ______,  ______, ______, ______,  ______,  ______, ______,  ______, ______,         ______, ______,            ______,           ______,______,______,______,    ______,______,
    // ______,  ______,  ______,  ______,  ______,         ______,           ______, ______,  ______, ______, ______, ______, ______,     ______,______,______,    ______,       ______,______,    ______,______
    // )
};


void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable=true;
    //debug_matrix=true;
    //debug_keyboard=true;
    //debug_mouse=true;
}

static uint8_t current_layer = LAYER0;
static uint8_t keys_tracker[MAX_WK];  // todo: need initialization?


// todo: reset if layer is changed but trackers aren't clear
// todo: tap dance to RESET
// todo: will key wrapping messes up with tap dance?

#define MAX_TAM_TAPS 3
const uint16_t tam_mod_maps[MAX_TAM_TAPS+1] = {
    [2] = KC_LCTL, // 2 taps
    [3] = KC_LALT,  // 3 taps
};

typedef struct {
    uint8_t count;
    uint16_t timer;
    bool finished;
    bool pressed;
    uint16_t keycode;
} tap_auto_mod_state_t;


static tap_auto_mod_state_t tam_state;

const uint16_t term = 300;

void tam_on_each(tap_auto_mod_state_t *state) {
    uint8_t count = state->count;
    dprintf("on each tap, count: %d\n\r", count);

    if (state->count == MAX_TAM_TAPS) {
        register_code16(tam_mod_maps[count]);
        register_code16(state->keycode);
        state->finished = true;
    }
}

void tam_finished(tap_auto_mod_state_t *state) {
    if (state->finished) return;
    state->finished = true;
    dprint("matrix_scan_tap_dance_user: tam finished\n\r");

    uint8_t count = state->count;

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
        unregister_code16(state->keycode);
        unregister_code16(tam_mod_maps[count]);
    }

    state->count    = 0;
    state->timer    = 0;
    state->finished = false;
    state->keycode  = 0;
}

bool process_tap_dance_user(uint16_t keycode, keyrecord_t *record) {
    tam_state.pressed = record->event.pressed;
    if (record->event.pressed) {
        tam_state.count++;
        tam_state.timer = timer_read();
        tam_state.keycode = keycode;

        tam_on_each(&tam_state);

    } else {
        if (tam_state.count > 0 && tam_state.finished) {
            tam_reset(&tam_state);
        }
    }
    return true;
}

void matrix_scan_tap_dance_user(void) {
    if (tam_state.count > 0 && timer_elapsed(tam_state.timer) > term) {

        tam_finished(&tam_state);
        tam_reset(&tam_state);
    }
}

void matrix_scan_user(void) {
    matrix_scan_tap_dance_user();
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    process_tap_dance_user(keycode, record);
    return false;

    uint16_t current_wk = layers_to_kc[current_layer];

    if (WK_0 <= keycode && keycode <= WK_4) {
        current_layer = keycode - WK_0;
        // return false;
        // todo: tap a key?
    } else if (KC_A <= keycode
        && keycode <= KC_EXSEL
        && keycode != current_wk) {

        if (record->event.pressed) {
            if (keys_tracker[current_layer] == 0) {
                // register_code(current_wk);
            }
            keys_tracker[current_layer]++;
            // register_code(keycode);
        } else {
            // unregister_code(keycode);
            keys_tracker[current_layer]--;
            if (keys_tracker[current_layer] == 0) {
                // unregister_code(current_wk);
            }
        }

        dprintf("layer %d | wk: %X | tracker: %d | keycode: 0x%02X\n\r\n\r", current_layer, current_wk, keys_tracker[current_layer], keycode);
        // return false;
    }

    dprintf("layer %d | wk: %X | tracker: %d | keycode: 0x%02X\n\r\n\r", current_layer, current_wk, keys_tracker[current_layer], keycode);
    return true;
}

