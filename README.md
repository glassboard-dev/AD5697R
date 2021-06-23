# Dual, 12-Bit nanoDAC+ with 2 ppm/°C Reference, I2C Interface
[![codecov](https://codecov.io/gh/glassboard-dev/AD56x/branch/main/graph/badge.svg?token=BG7A0OFND7)](https://codecov.io/gh/glassboard-dev/AD56x)

C Driver for the Analog Devices AD56x series of 12bit, dual output, nanoDAC+ ICs. This driver can be included directly into a developers source or a static library can be created and then linked against. Development is done on the **develop** branch, and official releases can be found on the **main** branch.

## Retrieving the Source
The source is located on Github and can be either downloaded and included directly into a developers source OR the developer can add this repo as a submodule into their project directory (The latter is the preferred method).

To include the driver as a git submodule
```bash
$ cd ./${DIR_WHERE_YOU_WANT_TO_ADD_THE_MODULE}
$ git submodule add https://github.com/glassboard-dev/AD56x.git
```

## Integration
#### Creating & Linking against a static library
To create a static library to link against, you must first source your build environment and ensure the **CC** environment variable is set to your desired toolchain.

Once your cross-compiler is properly setup. Execute the following commands:
```bash
$ mkdir build && cd build
$ cmake ..
$ make
```
The output library (libad56x.a) can be found in the **lib/** folder. Link against this file, and include the ad56x.h header file into your source include directories.
```c
#include "ad56x.h"
```

#### Adding to your own source/project
The other option for integrating the source into your project, is to include everything directly into your project
* Set your include directories to include the driver inc/ folder.
* Add the ad56x.c to your source list to be compiled.
* Include the API header file wherever you intended to implement the driver source.
```c
#include "ad56x.h"
```

## Implementing the driver
After following the integration steps above, you are ready to implement the driver and start retrieving ADC data. An example [***main.c***](./template/main.c) can be found in the templates folder that shows how to implement the settings, and data retrieval API. Note that you will need to fill out your own ***usr_*** functions for reading, writing, and a uS delay. You can build the example ***main.c*** by first compiling the static lib following the steps in the ***"Creating & Linking against a static library"*** and then executing the following commands.
```bash
$ cd template
$ mkdir build && cd build
$ cmake ..
$ make
```

## Testing
To test the source this submodule uses Ceedling, Unity and Gcov to run unit tests and generate HTML reports. You will need to install the following to run Unit Tests.
- [Ruby](https://www.ruby-lang.org/en/)
- [Ceedling](http://www.throwtheswitch.org/ceedling)
- [Gcovr](https://gcovr.com/en/stable/installation.html)

To execute the tests:
```bash
$ mkdir build && cd build
$ cmake ..
$ make tests
```

## Example application
Example application and main can be found below:
```C
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
    ad56x_return_code_t ret = AD56x_RET_OK;

    // Create an instance of our AD56x device
    ad56x_dev_t dev;

    // Provide the hardware abstraction functions for
    // I2c Read/Write and a micro-second delay function
    dev.intf.i2c_addr = AD56x_ADDR;
    dev.intf.write = usr_i2c_write;
    dev.intf.read = usr_i2c_read;
    dev.intf.delay_us = usr_delay_us;

    // Set the desired operation mode for our DAC outputs
    // Enable channel A to run in normal operation
    ret = ad56x_setOperatingMode(&dev, AD56x_OUTPUT_CH_A, AD56x_OP_MODE_NORMAL);

    // Disable channel B and put a 1K resistance to ground on the output
    if( ret == AD56x_RET_OK )
        ret = ad56x_setOperatingMode(&dev, AD56x_OUTPUT_CH_B, AD56x_OP_MODE_1K_TO_GND);

    // Set the DAC output value to 50% of the reference voltage
    if( ret == AD56x_RET_OK )
        ret = ad56x_writeChannel(&dev, AD56x_OUTPUT_CH_A, 0x00FF);

    return ret;
}
```
