#include "tft.h"
#ifdef TFT_ENABLED

/*****************************************************************************
*****************************************************************************/
void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_Dat)
{
	Write_Cmd(LCD_Reg);
	Write_Dat(LCD_Dat);
}
/*****************************************************************************
/*****************************************************************************
*****************************************************************************/
void LCD_ShowString(uint8_t x, uint16_t y, __I uint8_t *p)
{
	while (*p != '\0')
	{
		if (x > MAX_CHAR_POSX)
		{
			x = 0;
			y += 16;
		}
		if (y > MAX_CHAR_POSY)
		{
			y = x = 0;
			LCD_Clear(WHITE);
		}
		LCD_ShowChar(x, y, *p, 16, 0);
		x += 8;
		p++;
	}
}
/*****************************************************************************
*****************************************************************************/
void LCD_Clear(uint16_t Color)
{
	uint32_t index = 0;
	LCD_SetCursor(0x00, 0x0000);
	LCD_WriteRAM_Prepare();
	for (index = 0; index < 76800; index++)
	{
		Write_Dat(Color);
	}
}
/*****************************************************************************
*****************************************************************************/
void WriteString(uint16_t x0, uint16_t y0, uint8_t *pcStr, uint16_t color)
{
	uint16_t usWidth = 0;

	while (1)
	{
		if (*pcStr == 0)
		{
			break;
		}
		x0 = x0 + (usWidth);
		if (*pcStr <= 0x80)
		{
			if (*pcStr == '\r')
			{
				y0 = y0 + 16;
				if (y0 > LCD_H)
				{
					y0 = 0;
				}
				pcStr++;
				usWidth = 0;
				continue;
			}
			else if (*pcStr == '\n')
			{
				x0 = 0;
				pcStr++;
				usWidth = 0;
				continue;
			}
			else
			{
				if ((x0 + 8) > LCD_W)
				{
					x0 = 0;
					y0 = y0 + 16;
					if (y0 > LCD_H)
					{
						y0 = 0;
					}
				}
				usWidth = WriteOneASCII((uint8_t *)&ASCII_1608[(*pcStr - 0x20)][0], x0, y0, color);
				pcStr += 1;
			}
		}
	}
}
/*****************************************************************************
*****************************************************************************/
uint16_t WriteOneHzChar(uint8_t *pucMsk, uint16_t x0, uint16_t y0, uint16_t color)
{
	uint16_t i, j;
	uint16_t mod[16];
	uint16_t *pusMsk;
	uint16_t y;

	pusMsk = (uint16_t *)pucMsk;
	for (i = 0; i < 16; i++)
	{
		mod[i] = *pusMsk++;
		mod[i] = ((mod[i] & 0xff00) >> 8) | ((mod[i] & 0x00ff) << 8);
	}
	y = y0;
	for (i = 0; i < 16; i++)
	{
#ifdef __DISPLAY_BUFFER
		for (j = 0; j < 16; j++)
		{
			if ((mod[i] << j) & 0x8000)
			{
				DispBuf[240 * (y0 + i) + x0 + j] = color;
			}
		}
#else

		LCD_SetCursor(x0, y);
		LCD_WriteRAM_Prepare();
		for (j = 0; j < 16; j++)
		{
			if ((mod[i] << j) & 0x8000)
			{
				Write_Dat(color);
			}
			else
			{
				Write_Dat(BACK_COLOR);
				// LCD_ReadDat();
			}
		}
		y++;
#endif
	}
	return (16);
}
/*****************************************************************************
*****************************************************************************/
uint16_t WriteOneASCII(uint8_t *pucMsk, uint16_t x0, uint16_t y0, uint16_t color)
{
	uint16_t i, j;
	uint16_t y;
	uint8_t ucChar;

	y = y0;
	for (i = 0; i < 16; i++)
	{
		ucChar = *pucMsk++;
#ifdef __DISPLAY_BUFFER
		for (j = 0; j < 8; j++)
		{
			if ((ucChar << j) & 0x80)
			{
				DispBuf[240 * (y0 + i) + x0 + j] = color;
			}
		}
#else

		LCD_SetCursor(x0, y);
		LCD_WriteRAM_Prepare();
		for (j = 0; j < 8; j++)
		{
			if ((ucChar << j) & 0x80)
			{
				Write_Dat(color);
			}
			else
			{
				Write_Dat(BACK_COLOR);
				// LCD_ReadDat();
			}
		}
		y++;
#endif
	}
	return (8);
}
/*****************************************************************************
*****************************************************************************/
uint32_t Num_power(uint8_t m, uint8_t n)
{
	uint32_t result = 1;
	while (n--)
		result *= m;
	return result;
}
/*****************************************************************************
*****************************************************************************/
void LCD_ShowNum(uint8_t x, uint16_t y, uint32_t num, uint8_t len, uint8_t size)
{
	uint8_t t, temp;
	uint8_t enshow = 0;
	for (t = 0; t < len; t++)
	{
		temp = (num / Num_power(10, len - t - 1)) % 10;
		if (enshow == 0 && t < (len - 1))
		{
			if (temp == 0)
			{
				LCD_ShowChar(x + (size / 2) * t, y, ' ', size, 0);
				continue;
			}
			else
				enshow = 1;
		}
		LCD_ShowChar(x + (size / 2) * t, y, temp + '0', size, 0);
	}
}
/*****************************************************************************
*****************************************************************************/
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	uint16_t t;
	int xerr = 0, yerr = 0, delta_x, delta_y, distance;
	int incx, incy, uRow, uCol;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	uRow = x1;
	uCol = y1;
	if (delta_x > 0)
		incx = 1;
	else if (delta_x == 0)
		incx = 0;
	else
	{
		incx = -1;
		delta_x = -delta_x;
	}
	if (delta_y > 0)
		incy = 1;
	else if (delta_y == 0)
		incy = 0;
	else
	{
		incy = -1;
		delta_y = -delta_y;
	}
	if (delta_x > delta_y)
		distance = delta_x;
	else
		distance = delta_y;
	for (t = 0; t <= distance + 1; t++)
	{
		LCD_DrawPoint(uRow, uCol);
		xerr += delta_x;
		yerr += delta_y;
		if (xerr > distance)
		{
			xerr -= distance;
			uRow += incx;
		}
		if (yerr > distance)
		{
			yerr -= distance;
			uCol += incy;
		}
	}
}
/*****************************************************************************
*****************************************************************************/
void Draw_Circle(uint8_t x0, uint16_t y0, uint8_t r)
{
	int a, b;
	int di;
	a = 0;
	b = r;
	di = 3 - (r << 1);
	while (a <= b)
	{
		LCD_DrawPoint(x0 - b, y0 - a); // 3
		LCD_DrawPoint(x0 + b, y0 - a); // 0
		LCD_DrawPoint(x0 - a, y0 + b); // 1
		LCD_DrawPoint(x0 - b, y0 - a); // 7
		LCD_DrawPoint(x0 - a, y0 - b); // 2
		LCD_DrawPoint(x0 + b, y0 + a); // 4
		LCD_DrawPoint(x0 + a, y0 - b); // 5
		LCD_DrawPoint(x0 + a, y0 + b); // 6
		LCD_DrawPoint(x0 - b, y0 + a);
		a++;
		// Bresenham
		if (di < 0)
			di += 4 * a + 6;
		else
		{
			di += 10 + 4 * (a - b);
			b--;
		}
		LCD_DrawPoint(x0 + a, y0 + b);
	}
}
/*****************************************************************************
*****************************************************************************/
void LCD_Delay(uint32_t nCount)
{
	HAL_Delay(nCount);
}
/*********************************************************************************************************
** End of File
*********************************************************************************************************/
#endif /*TFT_ENABLED*/