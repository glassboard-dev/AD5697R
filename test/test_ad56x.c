#include "unity.h"
#include "ad56x.h"

static ad56x_dev_t ad56x_device = {0};
static ad56x_return_code_t desired_read_ret = AD56x_RET_OK;

int8_t usr_i2c_write(const uint8_t busAddr, const uint8_t *data, const uint32_t len);
int8_t usr_i2c_read(const uint8_t busAddr, uint8_t *data, const uint32_t len);
void usr_delay_us(uint32_t period);

void setUp(void)
{
    ad56x_device.intf.delay_us = usr_delay_us;
    ad56x_device.intf.read = usr_i2c_read;
    ad56x_device.intf.write = usr_i2c_write;
    ad56x_device.intf.i2c_addr = 0x01;
}

void tearDown(void)
{
}

int8_t usr_i2c_write(const uint8_t busAddr, const uint8_t *data, const uint32_t len) {
    ad56x_return_code_t ret = AD56x_RET_OK;

    // Transmit the data to the specified device from the provided
    // data buffer.

    return ret;
}

int8_t usr_i2c_read(const uint8_t busAddr, uint8_t *data, const uint32_t len) {
    ad56x_return_code_t ret = AD56x_RET_OK;

    switch( desired_read_ret ) {
        case AD56x_RET_OK:
            ret = AD56x_RET_OK;
            break;

        case AD56x_RET_TIMEOUT:
            ret = AD56x_RET_OK;
            break;

        case AD56x_RET_ERROR:
            ret = AD56x_RET_ERROR;
            break;

        default:
            break;
    }

    return ret;
}

void usr_delay_us(uint32_t period) {
    // Delay for the requested period
}

/****************************** writeChannel ******************************/
void test_ad56x_writeChannel_AllValid(void) {
    // Execute the function under test
    ad56x_return_code_t ret = ad56x_writeChannel(&ad56x_device, AD56x_OUTPUT_CH_A, 0x0000);
    TEST_ASSERT_EQUAL_INT(AD56x_RET_OK, ret);

    ret = ad56x_writeChannel(&ad56x_device, AD56x_OUTPUT_CH_B, 0x0000);
    TEST_ASSERT_EQUAL_INT(AD56x_RET_OK, ret);

    ret = ad56x_writeChannel(&ad56x_device, AD56x_OUTPUT_CH_A_B, 0x0000);
    TEST_ASSERT_EQUAL_INT(AD56x_RET_OK, ret);
}

void test_ad56x_writeChannel_NullDevice(void) {
    // Execute the function under test
    ad56x_return_code_t ret = ad56x_writeChannel(NULL, AD56x_OUTPUT_CH_A, 0x0000);

    TEST_ASSERT_EQUAL_INT(AD56x_RET_NULL_PTR, ret);
}

void test_ad56x_writeChannel_NullWriteIntf(void) {
    // Remove our write interface
    ad56x_device.intf.write = NULL;

    // Execute the function under test
    ad56x_return_code_t ret = ad56x_writeChannel(&ad56x_device, AD56x_OUTPUT_CH_A, 0x0000);

    TEST_ASSERT_EQUAL_INT(AD56x_RET_NULL_PTR, ret);
}

void test_ad56x_writeChannel_InvalidSlaveAddress(void) {
    // Set the slave adddress to an invalid value
    ad56x_device.intf.i2c_addr = 0x80;

    // Execute the function under test
    ad56x_return_code_t ret = ad56x_writeChannel(&ad56x_device, AD56x_OUTPUT_CH_A, 0x0000);

    TEST_ASSERT_EQUAL_INT(AD56x_RET_INV_PARAM, ret);
}

void test_ad56x_writeChannel_InvalidChannel(void) {
    // Execute the function under test
    ad56x_return_code_t ret = ad56x_writeChannel(&ad56x_device, AD56x_OUTPUT_CH__MAX__, 0x0000);

    TEST_ASSERT_EQUAL_INT(AD56x_RET_INV_PARAM, ret);
}

/****************************** setOperatingMode ******************************/
void test_ad56x_setOperatingMode_AllValid(void) {
    // Execute the function under test
    ad56x_return_code_t ret = ad56x_setOperatingMode(&ad56x_device, AD56x_OUTPUT_CH_A, AD56x_OP_MODE_NORMAL);
    TEST_ASSERT_EQUAL_INT(AD56x_RET_OK, ret);

    // Execute the function under test
    ret = ad56x_setOperatingMode(&ad56x_device, AD56x_OUTPUT_CH_A, AD56x_OP_MODE_1K_TO_GND);
    TEST_ASSERT_EQUAL_INT(AD56x_RET_OK, ret);

    // Execute the function under test
    ret = ad56x_setOperatingMode(&ad56x_device, AD56x_OUTPUT_CH_A, AD56x_OP_MODE_10k_TO_GND);
    TEST_ASSERT_EQUAL_INT(AD56x_RET_OK, ret);

    // Execute the function under test
    ret = ad56x_setOperatingMode(&ad56x_device, AD56x_OUTPUT_CH_A, AD56x_OP_MODE_TRI_STATE);
    TEST_ASSERT_EQUAL_INT(AD56x_RET_OK, ret);

    // Execute the function under test
    ret = ad56x_setOperatingMode(&ad56x_device, AD56x_OUTPUT_CH_B, AD56x_OP_MODE_1K_TO_GND);
    TEST_ASSERT_EQUAL_INT(AD56x_RET_OK, ret);

    // Execute the function under test
    ret = ad56x_setOperatingMode(&ad56x_device, AD56x_OUTPUT_CH_B, AD56x_OP_MODE_10k_TO_GND);
    TEST_ASSERT_EQUAL_INT(AD56x_RET_OK, ret);

    // Execute the function under test
    ret = ad56x_setOperatingMode(&ad56x_device, AD56x_OUTPUT_CH_A_B, AD56x_OP_MODE_TRI_STATE);
    TEST_ASSERT_EQUAL_INT(AD56x_RET_OK, ret);

    // Execute the function under test
    ret = ad56x_setOperatingMode(&ad56x_device, AD56x_OUTPUT_CH_A_B, AD56x_OP_MODE_1K_TO_GND);
    TEST_ASSERT_EQUAL_INT(AD56x_RET_OK, ret);

    // Execute the function under test
    ret = ad56x_setOperatingMode(&ad56x_device, AD56x_OUTPUT_CH_A_B, AD56x_OP_MODE_10k_TO_GND);
    TEST_ASSERT_EQUAL_INT(AD56x_RET_OK, ret);

    // Execute the function under test
    ret = ad56x_setOperatingMode(&ad56x_device, AD56x_OUTPUT_CH_A_B, AD56x_OP_MODE_TRI_STATE);
    TEST_ASSERT_EQUAL_INT(AD56x_RET_OK, ret);
}

void test_ad56x_setOperatingMode_NullDevice(void) {
    // Execute the function under test
    ad56x_return_code_t ret = ad56x_setOperatingMode(NULL, AD56x_OUTPUT_CH_A, AD56x_OP_MODE_NORMAL);

    TEST_ASSERT_EQUAL_INT(AD56x_RET_NULL_PTR, ret);
}

void test_ad56x_setOperatingMode_NullWriteIntf(void) {
    // Remove our write interface
    ad56x_device.intf.write = NULL;

    // Execute the function under test
    ad56x_return_code_t ret = ad56x_setOperatingMode(&ad56x_device, AD56x_OUTPUT_CH_A, AD56x_OP_MODE_NORMAL);

    TEST_ASSERT_EQUAL_INT(AD56x_RET_NULL_PTR, ret);
}

void test_ad56x_setOperatingMode_InvalidSlaveAddress(void) {
    // Set the slave adddress to an invalid value
    ad56x_device.intf.i2c_addr = 0x80;

    // Execute the function under test
    ad56x_return_code_t ret = ad56x_setOperatingMode(&ad56x_device, AD56x_OUTPUT_CH_A, AD56x_OP_MODE_NORMAL);

    TEST_ASSERT_EQUAL_INT(AD56x_RET_INV_PARAM, ret);
}

void test_ad56x_setOperatingMode_InvalidChannel(void) {
    // Execute the function under test
    ad56x_return_code_t ret = ad56x_setOperatingMode(&ad56x_device, AD56x_OUTPUT_CH__MAX__, AD56x_OP_MODE_NORMAL);

    TEST_ASSERT_EQUAL_INT(AD56x_RET_INV_PARAM, ret);
}

void test_ad56x_setOperatingMode_InvalidMode(void) {
    // Execute the function under test
    ad56x_return_code_t ret = ad56x_setOperatingMode(&ad56x_device, AD56x_OUTPUT_CH_A, AD56x_OP_MODE__MAX__);

    TEST_ASSERT_EQUAL_INT(AD56x_RET_INV_PARAM, ret);
}

/****************************** setReferenceMode ******************************/
void test_ad56x_setReferenceMode_AllValid(void) {
    // Execute the function under test
    ad56x_return_code_t ret = ad56x_setReferenceMode(&ad56x_device, AD56x_REF_ON);
    TEST_ASSERT_EQUAL_INT(AD56x_RET_OK, ret);

    ret = ad56x_setReferenceMode(&ad56x_device, AD56x_REF_OFF);
    TEST_ASSERT_EQUAL_INT(AD56x_RET_OK, ret);
}

void test_ad56x_setReferenceMode_NullDevice(void) {
    // Execute the function under test
    ad56x_return_code_t ret = ad56x_setReferenceMode(NULL, AD56x_REF_ON);

    TEST_ASSERT_EQUAL_INT(AD56x_RET_NULL_PTR, ret);
}

void test_ad56x_setReferenceMode_NullWriteIntf(void) {
    // Remove our write interface
    ad56x_device.intf.write = NULL;

    // Execute the function under test
    ad56x_return_code_t ret = ad56x_setReferenceMode(&ad56x_device, AD56x_REF_ON);

    TEST_ASSERT_EQUAL_INT(AD56x_RET_NULL_PTR, ret);
}

void test_ad56x_setReferenceMode_InvalidSlaveAddress(void) {
    // Set the slave adddress to an invalid value
    ad56x_device.intf.i2c_addr = 0x80;

    // Execute the function under test
    ad56x_return_code_t ret = ad56x_setReferenceMode(&ad56x_device, AD56x_REF_ON);

    TEST_ASSERT_EQUAL_INT(AD56x_RET_INV_PARAM, ret);
}

void test_ad56x_setReferenceMode_InvalidRefMode(void) {
    // Execute the function under test
    ad56x_return_code_t ret = ad56x_setReferenceMode(&ad56x_device, AD56x_REF__MAX__);

    TEST_ASSERT_EQUAL_INT(AD56x_RET_INV_PARAM, ret);
}
