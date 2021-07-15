#include QMK_KEYBOARD_H
#include <debug.h>

extern "C" {

#include "i2c_master.h"

uint8_t _ret2 = 0x99;

uint8_t _address = 0b0101001 << 1; // 0x29
uint8_t _reg     = 0xC0;

void garyng2_init(void) {
    DDRC |= (1 << 5);
    DDRC |= (1 << 6);
    DDRC |= (1 << 7);

    PORTC |= (1 << 5);

    i2c_writeReg(_address, _reg, NULL, 0, 10);
    i2c_readReg(_address, _reg, &_ret2, 1, 10);
    i2c_stop();

    PORTC |= (1 << 7);
    //_sensor.startContinuous();
}

void garyng2_test(void) {
    //uint8_t mm = _sensor.readRangeContinuousMillimeters();
    //dprintf("last status: %d, mm: %d", _sensor.last_status, mm);
    //dprintf("last status: %d, ret: %X\n", _sensor.last_status, _ret2);
    dprintf("ret2: 0x%X\n", _ret2);
}

}
