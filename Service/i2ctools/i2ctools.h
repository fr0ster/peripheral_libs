#include "conf.h"
#ifdef I2CUTILS_ENABLED
#ifndef __I2CTOOLS_H
#define __I2CTOOLS_H

#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"

void I2C_Scan_Log(I2C_HandleTypeDef *phi2c, UART_HandleTypeDef *phuart1);
uint16_t I2C_Scan(I2C_HandleTypeDef *phi2c);

#ifdef __cplusplus
}
#endif

#endif /* __I2CTOOLS_H */
#endif /*I2CUTILS_ENABLED*/