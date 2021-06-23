#ifndef _AD56X_H_
#define _AD56X_H_

#define AD56x_VERSION_MAJOR 0
#define AD56x_VERSION_MINOR 1
#define AD56x_VERSION_PATCH 0

typedef enum {
    AD56x_RET_OK          = 0,    /* OK */
    AD56x_RET_ERROR       = -1,   /* Error */
    AD56x_RET_BUSY        = -2,   /* Interface Busy */
    AD56x_RET_TIMEOUT     = -3,   /* Timeout */
    AD56x_RET_INV_PARAM   = -4,   /* Invalid Parameter */
    AD56x_RET_NULL_PTR    = -5,   /* NULL Pointer */
} ad56x_return_code_t;

#endif // _AD56X_H_