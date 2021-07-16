#include <debug.h>

#include "distance_trigger.h"
#include "VL53L0X.h"
#include "quantum.h"

static VL53L0X _sensor;

extern "C" {

__attribute__((weak)) void dt_on_triggered_keymap(void) {}
__attribute__((weak)) void dt_on_get_distance_keymap(uint16_t distance_mm) {}

void dt_init(void) {
    _sensor.init();
    _sensor.startContinuous();

    setPinInputHigh(D5);
}

void dt_on_triggered_user(void) {
    dprintln("triggered!");
    dt_on_triggered_keymap();
}

void dt_get_distance(void) {

    if (readPin(D5) == 0) {
        // from readRangeContinuousMillimeters
        uint16_t mm = _sensor.readReg16Bit(_sensor.RESULT_RANGE_STATUS + 10);
        _sensor.writeReg(_sensor.SYSTEM_INTERRUPT_CLEAR, 0x01);
        dt_on_get_distance_keymap(mm);
    }

    /*bool ready = readPin(D5);
    dprintf("ready: %d\n", ready);*/

    /*uint16_t mm = _sensor.readRangeContinuousMillimeters();
    dt_on_get_distance_keymap(mm);
    if (mm < TRIGGER_DISTANCE_MM) {
        dt_on_triggered_user();
    }*/
}
}
