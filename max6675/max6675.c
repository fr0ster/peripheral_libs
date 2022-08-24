#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "spi.h"
#include "max6675.h"

uint8_t max6675ReadReg(uint16_t *reg, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  HAL_StatusTypeDef hal_answer = HAL_ERROR;
  
  uint8_t temp[2] = {0};
  
  MAX6675_CS_SET(GPIOx, GPIO_Pin);
  
  hal_answer = HAL_SPI_Receive(MAX6675_SPI, temp, 2, 100);

  MAX6675_CS_RESET(GPIOx, GPIO_Pin);
  
  if(hal_answer == HAL_OK)
  {
    if(temp[1] & 0x04) return MAX6675_ERROR;
    
    *reg = (uint16_t)(temp[1] >> 3);
    *reg |= (uint16_t)(temp[0] << 5);
    
    return MAX6675_OK;
  }
  
  return MAX6675_ERROR;
}

float max6675Temp(uint16_t reg)
{
  return reg * 0.25;
}

float max6675TempFiltered(uint16_t reg)
{
  #define KOEF 0.5
  float celsius;
  celsius = reg * 0.25;
  static float celsius_filtered;
  celsius_filtered = (1 - KOEF)*celsius_filtered + KOEF * celsius;
  return celsius_filtered;
}
