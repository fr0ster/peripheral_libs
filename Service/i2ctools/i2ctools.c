#include "i2ctools.h"
#ifdef I2CUTILS_ENABLED
#include <stdio.h>
#include <string.h>

void I2C_Scan_Log(I2C_HandleTypeDef *phi2c, UART_HandleTypeDef *phuart1)
{
  HAL_StatusTypeDef res;
  char info[] = "\r\nScanning I2C bus...\r\n";
    HAL_UART_Transmit(phuart1, (uint8_t *)info, strlen(info), 100);
  for (uint16_t i = 0; i < 128; i++)
  {
    res = HAL_I2C_IsDeviceReady(phi2c, i << 1, 1, HAL_MAX_DELAY);
    if (res == HAL_OK)
    {
      char msg[64];
      snprintf(msg, sizeof(msg), "0x%02X", i);
      HAL_UART_Transmit(phuart1, (uint8_t *)msg, strlen(msg), 100);
    }
    else
      HAL_UART_Transmit(phuart1, (uint8_t *)".", 1, 100);
  }
}


uint16_t I2C_Scan(I2C_HandleTypeDef *phi2c)
{
  HAL_StatusTypeDef res;
  for (uint16_t i = 0; i < 128; i++)
  {
    res = HAL_I2C_IsDeviceReady(phi2c, i << 1, 1, HAL_MAX_DELAY);
    if (res == HAL_OK)
    {
      char msg[64];
      snprintf(msg, sizeof(msg), "0x%02X", i);
      return i;
    };
  }
  return 0;
}

#endif /*I2CUTILS_ENABLED*/
