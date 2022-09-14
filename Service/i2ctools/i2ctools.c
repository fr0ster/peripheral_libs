#include "i2ctools.h"
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

void I2C_send(uint8_t data,
              uint8_t flags,
              I2C_HandleTypeDef *phi2c,
              uint16_t DevAddress,
              uint32_t Delay)
{
  HAL_StatusTypeDef res;
  for (;;)
  {
    res = HAL_I2C_IsDeviceReady(phi2c, DevAddress, 1, HAL_MAX_DELAY);
    if (res == HAL_OK)
      break;
  }
  uint8_t up = data & 0xF0;
  uint8_t lo = (data << 4) & 0xF0;

  uint8_t data_arr[4];
  data_arr[0] = up | flags | BACKLIGHT | PIN_EN;
  data_arr[1] = up | flags | BACKLIGHT;
  data_arr[2] = lo | flags | BACKLIGHT | PIN_EN;
  data_arr[3] = lo | flags | BACKLIGHT;

  HAL_I2C_Master_Transmit(phi2c, DevAddress, data_arr, sizeof(data_arr), HAL_MAX_DELAY);
  HAL_Delay(Delay);
}
