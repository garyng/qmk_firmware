#include <debug.h>

#include "distance_trigger.h"
#include "VL53L0X.h"

static VL53L0X _sensor;

extern "C" {

__attribute__((weak)) void dt_on_triggered_keymap(void) {}
__attribute__((weak)) void dt_on_get_distance_keymap(uint16_t distance_mm) {}

void dt_init(void) {
    _sensor.init();
    _sensor.startContinuous();
}

void dt_on_triggered_user(void) {
    dprintln("triggered!");
    dt_on_triggered_keymap();
}

void dt_get_distance(void) {
    uint16_t mm = _sensor.readRangeContinuousMillimeters();
    dt_on_get_distance_keymap(mm);
    if (mm < TRIGGER_DISTANCE_MM) {
        dt_on_triggered_user();
    }
}
}
