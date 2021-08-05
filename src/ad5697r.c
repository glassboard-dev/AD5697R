/*! @file ad5697r.h
 * @brief Driver source for the AD5697R 12-Bit, DAC C driver.
 */

#include <stdio.h>
#include "ad5697r.h"

/*!
 * @brief AD5697R Command Definitions
 */
typedef enum {
    AD5697R_CMD_NO_OP                         = 0x00, /* No operation */
    AD5697R_CMD_W_INPUT_REG_N                 = 0x01, /* Write to Input Register n (Dependent on !LDAC) */
    AD5697R_CMD_UPDATE_DAC_FROM_INPUT_REG_N   = 0x02, /* Update DAC Register n with contents from Input Register n */
    AD5697R_CMD_WRITE_DAC                     = 0x03, /* Write to and update DAC Channel n */
    AD5697R_CMD_POWER_DAC                     = 0x04, /* Power down/power up DAC */
    AD5697R_CMD_HW_LDAC_MASK                  = 0x05, /* Hardware !LDAC mask register */
    AD5697R_CMD_SOFT_RESET                    = 0x06, /* Software reset (power-on reset) */
    AD5697R_CMD_INT_REF_SETUP                 = 0x07, /* Internal reference setup register */
    AD5697R_CMD__MAX__
} AD5697R_CMD_t;

/*!
 * @brief AD5697R Input Shift Register Content
 */
typedef union  {
    struct {
        union {
            struct {
                uint8_t cmd     : 4;    /* Command byte - Command */
                uint8_t ch      : 4;    /* Command byte - DAC Channel */
            } bits;                     /* Command byte - Bit Field */
            uint8_t byte;               /* Command byte - Byte */
        } command;                      /* Command byte */
        uint8_t data_high;              /* Data high byte */
        union {
            struct {
                uint8_t rsvd    : 4;    /* RSVD */
                uint8_t data    : 4;    /* Date low nibble */
            } bits;
            uint8_t byte;           /* Date low byte */
        } data_low;
    } bits;
    uint8_t bytes[3];
} ad5697r_dac_register_t;

/*!
 * @brief AD5697R Input Shift Register Content
 */
typedef union  {
    struct {
        union {
            struct {
                uint8_t cmd     : 4;    /* Command byte - Command */
                uint8_t rsvd    : 4;    /* Command byte - RSVD */
            } bits;                     /* Command byte - Bit Field */
            uint8_t byte;               /* Command byte - Byte */
        } command;                      /* Command byte */
        uint8_t rsvd;                   /* RSVD */
        union {
            struct {
                uint8_t PDB     : 2;    /* Power Mode - CHB */
                uint8_t rsvd    : 4;    /* RSVD */
                uint8_t PDA     : 2;    /* Power Mode - CHA */
            } bits;
        } powerMode;                    /* Date low byte */
    } bits;
    uint8_t bytes[3];
} ad5697r_operation_register_t;

/*!
 * @brief AD5697R Reference Mode Content
 */
typedef union  {
    struct {
        union {
            struct {
                uint8_t rsvd    : 4;    /* Command byte - RSVD */
                uint8_t cmd     : 4;    /* Command byte - Command */
            } bits;                     /* Command byte - Bit Field */
            uint8_t byte;               /* Command byte - Byte */
        } command;                      /* Command byte */
        uint8_t rsvd;                   /* RSVD */
        union {
            struct {
                uint8_t REF_EN  : 1;    /* Internal Reference Setup */
                uint8_t rsvd    : 7;    /* RSVD */
            } bits;
        } reference;                    /* Date low byte */
    } bits;
    uint8_t bytes[3];
} ad5697r_reference_register_t;

/*!
 * @brief This API writes the desired DAC value to the specified channel
 */
ad5697r_return_code_t ad5697r_writeChannel(ad5697r_dev_t *dev, const ad5697r_output_channel_t ch, const uint16_t outputVal) {
    ad5697r_dac_register_t dac_register = {0};

    if( (dev == NULL) || (dev->intf.write == NULL) ) {
        return AD5697R_RET_NULL_PTR;
    }
    else if( (ch >= AD5697R_OUTPUT_CH__MAX__) || (dev->intf.i2c_addr > 0x7F) ) {
        return AD5697R_RET_INV_PARAM;
    }

    // Setup the cmd register
    dac_register.bits.command.bits.ch = ch;
    dac_register.bits.command.bits.cmd = AD5697R_CMD_WRITE_DAC;
    dac_register.bits.data_high = outputVal >> 4;
    dac_register.bits.data_low.bits.data = outputVal;

    // Write the DAC value to our device.
    return dev->intf.write(dev->intf.i2c_addr, (uint8_t *)&dac_register, sizeof(dac_register));
}

/*!
 * @brief This API sets the operation mode for each DAC output
 */
ad5697r_return_code_t ad5697r_setOperatingMode(ad5697r_dev_t *dev, const ad5697r_output_channel_t ch, const ad5697r_operation_mode_t mode) {
    ad5697r_operation_register_t op_register = {0};

    if( (dev == NULL) || (dev->intf.write == NULL) ) {
        return AD5697R_RET_NULL_PTR;
    }
    else if( (mode >= AD5697R_OP_MODE__MAX__) || (dev->intf.i2c_addr > 0x7F)) {
        return AD5697R_RET_INV_PARAM;
    }

    switch( ch ) {
        case AD5697R_OUTPUT_CH_A:
            dev->registers.bits.CHA_mode = mode;
            break;

        case AD5697R_OUTPUT_CH_B:
            dev->registers.bits.CHB_mode = mode;
            break;

        case AD5697R_OUTPUT_CH_A_B:
            dev->registers.bits.CHA_mode = mode;
            dev->registers.bits.CHB_mode = mode;
            break;

        default:
            return AD5697R_RET_INV_PARAM;
            break;
    }

    op_register.bits.command.bits.cmd = AD5697R_CMD_POWER_DAC;
    op_register.bits.powerMode.bits.PDA = dev->registers.bits.CHA_mode;
    op_register.bits.powerMode.bits.PDB = dev->registers.bits.CHB_mode;

    // Write the Operation mode values to our device.
    return dev->intf.write(dev->intf.i2c_addr, (uint8_t *)&op_register, sizeof(op_register));
}

/*!
 * @brief This API sets enables/disables the internal reference
 */
ad5697r_return_code_t ad5697r_setReferenceMode(ad5697r_dev_t *dev, const ad5697r_reference_t refSelect) {
    ad5697r_reference_register_t ref_register = {0};

    if( (dev == NULL) || (dev->intf.write == NULL) ) {
        return AD5697R_RET_NULL_PTR;
    }
    else if( (refSelect >= AD5697R_REF__MAX__) || (dev->intf.i2c_addr > 0x7F)) {
        return AD5697R_RET_INV_PARAM;
    }

    ref_register.bits.command.bits.cmd = AD5697R_CMD_INT_REF_SETUP;
    ref_register.bits.reference.bits.REF_EN = refSelect;

    // Write the Reference select mode values to our device.
    return dev->intf.write(dev->intf.i2c_addr, (uint8_t *)&ref_register, sizeof(ref_register));
}