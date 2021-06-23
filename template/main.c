#include <stdint.h>
#include <stdio.h>
#include "ad56x.h"

#define AD56x_ADDR    (0x6E)

int8_t usr_i2c_write(const uint8_t busAddr, const uint8_t *data, const uint32_t len) {
    ad56x_return_code_t ret = AD56x_RET_OK;

    // Transmit the data to the specified device from the provided
    // data buffer.

    return ret;
}

int8_t usr_i2c_read(const uint8_t busAddr, uint8_t *data, const uint32_t len) {
    ad56x_return_code_t ret = AD56x_RET_OK;

    // Received the specified amount of data from the device and store it
    // in the data buffer

    return ret;
}

void usr_delay_us(uint32_t period) {
    // Delay for the requested period
}

int main(void) {

    while(1) {
        printf("Hello world.\n\r");
    }

    return 0;
}