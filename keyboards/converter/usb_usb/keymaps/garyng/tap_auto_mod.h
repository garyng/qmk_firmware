#pragma once
#include <action.h>

typedef struct {
    uint8_t  count;
    uint16_t timer;
    bool     finished;
    bool     pressed;
    uint16_t keycode;
} tap_auto_mod_state_t;

#ifdef MAX_TAM_TAPS
extern const uint16_t tam_mod_maps[];
#endif

__attribute__((weak)) void pre_register_key(tap_auto_mod_state_t *state);
__attribute__((weak)) void post_unregister_key(tap_auto_mod_state_t *state);


void tam_on_each(tap_auto_mod_state_t *state);
void tam_finished(tap_auto_mod_state_t *state);
void tam_reset(tap_auto_mod_state_t *state);
void process_tam_user(uint16_t keycode, keyrecord_t *record);
void matrix_scan_tam_user(void);

