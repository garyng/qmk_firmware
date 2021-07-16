#include <debug.h>

#include "distance_trigger.h"
#include "VL53L0X.h"
#include "quantum.h"

static VL53L0X  _sensor;
static uint16_t _mm = UINT16_MAX;

extern "C" {

__attribute__((weak)) void dt_on_triggered_keymap(void) {}
__attribute__((weak)) void dt_on_get_distance_keymap(uint16_t distance_mm) {}

void dt_init(void) {
    _sensor.init();
    _sensor.startContinuous();

    setPinInputHigh(VL53L0X_INTERRUPT_PIN);
}

void dt_on_triggered_user(void) {
    dprintln("triggered!");
    dt_on_triggered_keymap();
}

void dt_get_distance(void) {
    if (readPin(VL53L0X_INTERRUPT_PIN) == 0) {
        // from VL53L0X::readRangeContinuousMillimeters
        _mm = _sensor.readReg16Bit(_sensor.RESULT_RANGE_STATUS + 10);
        _sensor.writeReg(_sensor.SYSTEM_INTERRUPT_CLEAR, 0x01);
        dt_on_get_distance_keymap(_mm);
    }

    if (_mm < TRIGGER_DISTANCE_MM) {
        dt_on_triggered_user();
    }
}
}
