#include <stdint.h>
#include <stdio.h>
#include "ad5697r.h"

#define ad5697r_ADDR    (0x6E)

int8_t usr_i2c_write(const uint8_t busAddr, const uint8_t *data, const uint32_t len) {
    ad5697r_return_code_t ret = AD5697R_RET_OK;

    // Transmit the data to the specified device from the provided
    // data buffer.

    return ret;
}

int8_t usr_i2c_read(const uint8_t busAddr, uint8_t *data, const uint32_t len) {
    ad5697r_return_code_t ret = AD5697R_RET_OK;

    // Received the specified amount of data from the device and store it
    // in the data buffer

    return ret;
}

void usr_delay_us(uint32_t period) {
    // Delay for the requested period
}

int main(void) {
    ad5697r_return_code_t ret = AD5697R_RET_OK;

    // Create an instance of our ad5697r device
    ad5697r_dev_t dev;

    // Provide the hardware abstraction functions for
    // I2c Read/Write and a micro-second delay function
    dev.intf.i2c_addr = ad5697r_ADDR;
    dev.intf.write = usr_i2c_write;
    dev.intf.read = usr_i2c_read;
    dev.intf.delay_us = usr_delay_us;

    // Set the desired operation mode for our DAC outputs
    // Enable channel A to run in normal operation
    ret = ad5697r_setOperatingMode(&dev, AD5697R_OUTPUT_CH_A, AD5697R_OP_MODE_NORMAL);

    // Disable channel B and put a 1K resistance to ground on the output
    if( ret == AD5697R_RET_OK )
        ret = ad5697r_setOperatingMode(&dev, AD5697R_OUTPUT_CH_B, AD5697R_OP_MODE_1K_TO_GND);

    // Set the DAC output value to 50% of the reference voltage
    if( ret == AD5697R_RET_OK )
        ret = ad5697r_writeChannel(&dev, AD5697R_OUTPUT_CH_A, 0x00FF);

    return ret;
}