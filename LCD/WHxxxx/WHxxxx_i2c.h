#include "conf.h"
#ifdef WHXXXX_I2C_ENABLED
#ifndef __WHXXXX_I2C_ENABLED_H
#define __WHXXXX_I2C_ENABLED_H

#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"

void I2C_send(
    uint8_t data,
    uint8_t flags,
    I2C_HandleTypeDef *phi2c,
    uint16_t DevAddress,
    uint32_t Delay);

#ifdef __cplusplus
}
#endif

#endif /* __WHXXXX_I2C_ENABLED_H */
#endif /*WHXXXX_I2C_ENABLED*/