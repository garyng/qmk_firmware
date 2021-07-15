#include QMK_KEYBOARD_H
#include <debug.h>

extern "C" {

#include "i2c_master.h"

uint8_t _ret2 = 0x99;

uint8_t _address = 0b0101001 << 1; // 0x29
uint8_t _reg     = 0xC0;

/*
@drashna
but I recently converted some arduino code using the same, so let me dig that out for you
wire code:

void RAP_ReadBytes(uint8_t address, uint8_t * data, uint8_t count)
{
  uint8_t cmdByte = READ_MASK | address;   // Form the READ command byte
  uint8_t i = 0;

  Wire.beginTransmission(SLAVE_ADDR);   // Set up an I2C-write to the I2C slave (Pinnacle)
  Wire.write(cmdByte);                  // Signal a RAP-read operation starting at <address>
  Wire.endTransmission(true);           // I2C stop condition

  Wire.requestFrom((uint8_t)SLAVE_ADDR, count, (uint8_t)true);  // Read <count> bytes from I2C slave
  while(Wire.available())
  {
    data[i++] = Wire.read();
  }
}

// Writes single-byte <data> to <address>
void RAP_Write(uint8_t address, uint8_t data)
{
  uint8_t cmdByte = WRITE_MASK | address;  // Form the WRITE command byte

  Wire.beginTransmission(SLAVE_ADDR);   // Set up an I2C-write to the I2C slave (Pinnacle)
  Wire.send(cmdByte);                   // Signal a RAP-write operation at <address>
  Wire.send(data);                      // Write <data> to I2C slave
  Wire.endTransmission(true);           // I2C stop condition
}


C + QMK i2c master code :

void RAP_ReadBytes(uint8_t address, uint8_t* data, uint8_t count) {
    uint8_t cmdByte = READ_MASK | address;  // Form the READ command byte
        i2c_writeReg(SLAVE_ADDR << 1, cmdByte, NULL, 0, I2C_TIMEOUT);
        if (i2c_readReg(SLAVE_ADDR << 1, cmdByte, data, count, I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
            dprintf("error right touchpad\n");
            touchpad_init[0] = false;
        }
        i2c_stop();
}

// Writes single-byte <data> to <address>
void RAP_Write(uint8_t address, uint8_t data) {
    uint8_t cmdByte = WRITE_MASK | address;  // Form the WRITE command byte
        if (i2c_writeReg(SLAVE_ADDR << 1, cmdByte, &data, sizeof(data), I2C_TIMEOUT) != I2C_STATUS_SUCCESS) {
            dprintf("error right touchpad\n");
            touchpad_init[0] = false;
        }
        i2c_stop();
}
 */

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
