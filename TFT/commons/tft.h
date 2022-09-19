#include "conf.h"
#ifdef TFT_ENABLED
#ifndef __TFT_H
#define __TFT_H
#include "main.h"
#include "common.h"

#ifdef ILI932x_ENABLED
#include "ILI932x.h"
#endif /*ILI932x_ENABLED*/


#ifndef POINT_COLOR
#error "Define point color in POINT_COLOR"
#endif
#ifndef BACK_COLOR
#error "Define back color in BACK_COLOR"
#endif
#ifndef MAX_CHAR_POSX
#error "Define screen width in MAX_CHAR_POSX"
#endif
#ifndef MAX_CHAR_POSY
#error "Define screen high in MAX_CHAR_POSY"
#endif

#if (!defined(TFT_16_ENABLED) && !defined(TFT_08_ENABLED) && (TFT_SPI_ENABLED))
#error "Choose TFT interface by defining TFT_16_ENABLED/TFT_08_ENABLED/TFT_SPI_ENABLED"
#endif

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_Dat);
uint16_t LCD_ReadDat(void);
void LCD_Delay(uint32_t nCount);
uint32_t Num_power(uint8_t m, uint8_t n);
void LCD_ShowString(uint8_t x, uint16_t y, __I uint8_t *p);
void LCD_ShowNum(uint8_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size);
void LCD_Clear(uint16_t Color);
uint16_t WriteOneASCII(uint8_t *pucMsk, uint16_t x0, uint16_t y0, uint16_t color);
uint16_t WriteOneHzChar(uint8_t *pucMsk, uint16_t x0, uint16_t y0, uint16_t color);
void WriteString(uint16_t x0, uint16_t y0, uint8_t *pcStr, uint16_t color);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void Draw_Circle(uint8_t x0, uint16_t y0, uint8_t r);
#endif /*__TFT_H*/
/****************************** End File ********************************/
#endif /*TFT_ENABLED*/