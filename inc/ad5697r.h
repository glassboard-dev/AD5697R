/*! @file ad5697r.h
 * @brief Public header file for the ad5697r 12-Bit, DAC C driver.
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _ad5697r_H_
#define _ad5697r_H_

#include <stdint.h>
#include <stdbool.h>

#define ad5697r_VERSION_MAJOR 0 /*! @brief VERSION MAJOR */
#define ad5697r_VERSION_MINOR 1 /*! @brief VERSION MINOR */
#define ad5697r_VERSION_PATCH 0 /*! @brief VERSION PATH */

/*!
 * @brief This function pointer API reads I2C data from the specified
 * device on the bus.
 *
 * @param[in] busAddr: Address of the device to be read from
 * @param[out] *data: Pointer to the where we should store the read data
 * @param[in] len: Length of data to be read
 *
 * @return The result of reading I2C data
 */
typedef int8_t(*ad5697r_read_fptr_t)(const uint8_t busAddr, uint8_t *data, const uint32_t len);

/*!
 * @brief This function pointer API writes I2C data to the specified
 * device on the bus.
 *
 * @param[in] busAddr: Address of the device to be written to
 * @param[in] *data: Pointer to the data to be written
 * @param[in] len: Length of data to be written
 *
 * @return The result of writing I2C data
 */
typedef int8_t(*ad5697r_write_fptr_t)(const uint8_t busAddr, const uint8_t *data, const uint32_t len);

/*!
 * @brief This function pointer API delays for the specified time in microseconds.
 *
 * @param[in] period: Duration to be delayed in micro-seconds
 */
typedef void(*ad5697r_delay_us_fptr_t)(uint32_t period);

/*!
 * @brief ad5697r Return codes for the driver API
 */
typedef enum {
    AD5697R_RET_OK            = 0,    /* OK */
    AD5697R_RET_ERROR         = -1,   /* Error */
    AD5697R_RET_BUSY          = -2,   /* Interface Busy */
    AD5697R_RET_TIMEOUT       = -3,   /* Timeout */
    AD5697R_RET_INV_PARAM     = -4,   /* Invalid Parameter */
    AD5697R_RET_NULL_PTR      = -5,   /* NULL Pointer */
} ad5697r_return_code_t;

/*!
 * @brief ad5697r Output Channels
 */
typedef enum {
    AD5697R_OUTPUT_CH_A      = 0x01,      /* DAC Output CH A */
    AD5697R_OUTPUT_CH_B      = 0x08,      /* DAC Output CH B */
    AD5697R_OUTPUT_CH_A_B    = 0x09,      /* DAC Output CH A and B */
    AD5697R_OUTPUT_CH__MAX__
} ad5697r_output_channel_t;

/*!
 * @brief ad5697r Operating Mode
 */
typedef enum {
    AD5697R_OP_MODE_NORMAL        = 0x00, /* Normal Operation*/
    AD5697R_OP_MODE_1K_TO_GND     = 0x01, /* Power-Down - 1kOhm to GND */
    AD5697R_OP_MODE_10K_TO_GND    = 0x02, /* Power-Down - 10kOhm to GND */
    AD5697R_OP_MODE_TRI_STATE     = 0x03, /* Power-Down - Tri-State */
    AD5697R_OP_MODE__MAX__
} ad5697r_operation_mode_t;

/*!
 * @brief AD56x Reference Mode
 */
typedef enum {
    AD5697R_REF_ON                = 0x00, /* Reference on */
    AD5697R_REF_OFF               = 0x01, /* Reference off */
    AD5697R_REF__MAX__
} ad5697r_reference_t;

/*!
 * @brief ad5697r Device Registers
 */
typedef union
{
    struct
    {
        uint8_t CHA_mode;   /* Channel A operating mode */
        uint8_t CHB_mode;   /* Channel B operating mode */
    } bits;
    uint8_t bytes[1];
} ad5697r_registers_t;

/*!
 * @brief ad5697r HW Interface
 */
typedef struct {
    uint8_t i2c_addr;                 /* Device I2C Address */
    ad5697r_read_fptr_t read;           /* User I2C Read Function Pointer */
    ad5697r_write_fptr_t write;         /* User I2C Write Function Pointer */
    ad5697r_delay_us_fptr_t delay_us;   /* User Micro-Second Delay Function Pointer */
} ad5697r_dev_intf_t;

/*!
 * @brief ad5697r Device Instance
 */
typedef struct
{
    ad5697r_dev_intf_t intf;                        /* Device Hardware Interface */
    ad5697r_registers_t registers;                  /* Device Registers */
} ad5697r_dev_t;

/*!
 * @brief This function pointer API writes the desired DAC channel with the provided
 * value.
 *
 * @param[in] *dev: Pointer to your ad5697r device
 * @param[in] ch: DAC output channel to be written to
 * @param[in] outputVal: 16bit value to write the DAC channel
 *
 * @return The result of writing the DAC channel
 */
ad5697r_return_code_t ad5697r_writeChannel(ad5697r_dev_t *dev, const ad5697r_output_channel_t ch, const uint16_t outputVal);

/*!
 * @brief This API sets the operation mode for each DAC output
 *
 * @param[in] *dev: Pointer to your ad5697r device
 * @param[in] ch: DAC output channel to be written to
 * @param[in] mode: DAC Channel operation mode
 *
 * @return The result of writing the DAC channel
 */
ad5697r_return_code_t ad5697r_setOperatingMode(ad5697r_dev_t *dev, const ad5697r_output_channel_t ch, const ad5697r_operation_mode_t mode);

/*!
 * @brief This API sets enables/disables the internal reference
 *
 * @param[in] *dev: Pointer to your ad56x device
 * @param[in] refSelect: Sets the state of the internal reference (on/off)
 *
 * @return The result of writing the DAC channel
 */
ad5697r_return_code_t ad5697r_setReferenceMode(ad5697r_dev_t *dev, const ad5697r_reference_t refSelect);

#endif // _ad5697r_H_

#ifdef __cplusplus
}
#endif