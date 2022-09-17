#include "WHxxxx_i2c.h"
#ifdef WHXXXX_I2C_ENABLED
#include <stdio.h>
#include <string.h>

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
#endif /*I2CUTILS_ENABLED*/
