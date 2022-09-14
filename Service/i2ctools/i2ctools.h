#ifndef __I2CTOOLS_H
#define __I2CTOOLS_H

#ifdef __cplusplus
extern "C" {
#endif
#include "conf.h"
#include "main.h"

void I2C_Scan_Log(I2C_HandleTypeDef *phi2c, UART_HandleTypeDef *phuart1);
uint16_t I2C_Scan(I2C_HandleTypeDef *phi2c);

void I2C_send(
    uint8_t data,
    uint8_t flags,
    I2C_HandleTypeDef *phi2c,
    uint16_t DevAddress,
    uint32_t Delay);

#ifdef __cplusplus
}
#endif

#endif /* __I2CTOOLS_H */
