#include <eeconfig.h>
#include "user_config.h"
#include "wrapping_key.h"

typedef union {
    uint32_t raw;

    struct {
        uint8_t current_wki;
    };
} user_config_t;

user_config_t user_config;

void read_user_config(void) {
    user_config.raw = eeconfig_read_user();
#ifndef WK_TIMEOUT
    set_current_wki(user_config.current_wki);
#endif

}

#ifndef WK_TIMEOUT
void wk_on_changed_user_config(uint8_t old_wki, uint16_t old_wk, uint8_t new_wki, uint16_t new_wk) {
    user_config.current_wki = new_wki;
    eeconfig_update_user(user_config.raw);
}
#endif
