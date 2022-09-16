#include "conf.h"

#ifdef MAX6675_ENABLED
#ifndef _MAX6675_H
#define _MAX6675_H

#include "main.h"

#define MAX6675_SPI     &hspi2

#define MAX6675_CS_SET(MAX6675_CS_GPIO_Port, MAX6675_CS_Pin)   (HAL_GPIO_WritePin(MAX6675_CS_GPIO_Port, MAX6675_CS_Pin, GPIO_PIN_RESET))
#define MAX6675_CS_RESET(MAX6675_CS_GPIO_Port, MAX6675_CS_Pin) (HAL_GPIO_WritePin(MAX6675_CS_GPIO_Port, MAX6675_CS_Pin, GPIO_PIN_SET))

#define MAX6675_OK      1
#define MAX6675_ERROR   0

uint8_t max6675ReadReg(uint16_t *reg, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

float max6675Temp(uint16_t reg);

#endif /* _MAX6675_H */
#endif /*MAX6675_ENABLED*/