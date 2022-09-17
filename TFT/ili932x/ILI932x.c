#include "ILI932x.h"
#ifdef ILI932x_ENABLED
#include "Font_Lib.h"
uint16_t POINT_COLOR = BLUE, BACK_COLOR = WHITE;

/*****************************************************************************
*****************************************************************************/
void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_Dat)
{
	Write_Cmd(LCD_Reg);
	Write_Dat(LCD_Dat);
}
/*****************************************************************************
*****************************************************************************/
void Write_Cmd(uint16_t LCD_Reg)
{
	// LCD_CS = 0;
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);
	// LCD_RS = 0;
	HAL_GPIO_WritePin(TFT_RS_GPIO_Port, TFT_RS_Pin, GPIO_PIN_RESET);
	GPIOC->ODR = (GPIOC->ODR & 0xff00) | (LCD_Reg & 0x00ff);
	// #ifdef TFT_16_ENABLED
	GPIOB->ODR = (GPIOB->ODR & 0x00ff) | (LCD_Reg & 0xff00);
	// #endif
	// LCD_WR = 0;
	HAL_GPIO_WritePin(TFT_WR_GPIO_Port, TFT_WR_Pin, GPIO_PIN_RESET);
	// LCD_WR = 1;
	HAL_GPIO_WritePin(TFT_WR_GPIO_Port, TFT_WR_Pin, GPIO_PIN_SET);
	// LCD_CS = 1;
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_SET);
}
/*****************************************************************************
*****************************************************************************/
void Write_Dat(uint16_t LCD_Dat)
{
	// LCD_CS = 0;
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);
	// LCD_RS = 1;
	HAL_GPIO_WritePin(TFT_RS_GPIO_Port, TFT_RS_Pin, GPIO_PIN_SET);
	GPIOC->ODR = (GPIOC->ODR & 0xff00) | (LCD_Dat & 0x00ff);
	// #ifdef TFT_16_ENABLED
	GPIOB->ODR = (GPIOB->ODR & 0x00ff) | (LCD_Dat & 0xff00);
	// #endif
	// LCD_WR = 0;
	HAL_GPIO_WritePin(TFT_WR_GPIO_Port, TFT_WR_Pin, GPIO_PIN_RESET);
	// LCD_WR = 1;
	HAL_GPIO_WritePin(TFT_WR_GPIO_Port, TFT_WR_Pin, GPIO_PIN_SET);
	// LCD_CS = 1;
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_SET);
}
/*****************************************************************************
*****************************************************************************/
uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{
	uint16_t temp;
	Write_Cmd(LCD_Reg);

	GPIOB->CRH = (GPIOB->CRH & 0x00000000) | 0x44444444;
	GPIOC->CRL = (GPIOC->CRL & 0x00000000) | 0x44444444;
	// LCD_CS = 0;
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);
	// LCD_RS = 1;
	HAL_GPIO_WritePin(TFT_RS_GPIO_Port, TFT_RS_Pin, GPIO_PIN_SET);
	// LCD_RD = 0;
	HAL_GPIO_WritePin(TFT_RD_GPIO_Port, TFT_RD_Pin, GPIO_PIN_RESET);
	temp = ((GPIOB->IDR & 0xff00) | (GPIOC->IDR & 0x00ff));
	// LCD_RD = 1;
	HAL_GPIO_WritePin(TFT_RD_GPIO_Port, TFT_RD_Pin, GPIO_PIN_SET);
	// LCD_CS = 1;
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_SET);
	GPIOB->CRH = (GPIOB->CRH & 0x00000000) | 0x33333333;
	GPIOC->CRL = (GPIOC->CRL & 0x00000000) | 0x33333333;
	return temp;
}
/*****************************************************************************
*****************************************************************************/
uint16_t LCD_ReadDat()
{
	uint16_t temp;

	GPIOE->CRH = (GPIOE->CRH & 0x00000000) | 0x44444444;
	GPIOE->CRL = (GPIOE->CRL & 0x00000000) | 0x44444444;
	// LCD_CS = 0;
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_RESET);
	// LCD_RS = 1;
	HAL_GPIO_WritePin(TFT_RS_GPIO_Port, TFT_RS_Pin, GPIO_PIN_SET);
	// LCD_RD = 0;
	HAL_GPIO_WritePin(TFT_RD_GPIO_Port, TFT_RD_Pin, GPIO_PIN_RESET);
	temp = ((GPIOB->IDR & 0xff00) | (GPIOC->IDR & 0x00ff));
	// LCD_RD = 1;
	HAL_GPIO_WritePin(TFT_RD_GPIO_Port, TFT_RD_Pin, GPIO_PIN_SET);
	// LCD_CS = 1;
	HAL_GPIO_WritePin(TFT_CS_GPIO_Port, TFT_CS_Pin, GPIO_PIN_SET);
	GPIOE->CRH = (GPIOE->CRH & 0x00000000) | 0x33333333;
	GPIOE->CRL = (GPIOE->CRL & 0x00000000) | 0x33333333;

	return temp;
}
/*****************************************************************************
*****************************************************************************/
void LCD_Configuration()
{
#ifdef TFT_08_ENABLED
#if (defined(DB08_Pin) | \
	 defined(DB09_Pin) | \
	 defined(DB10_Pin) | \
	 defined(DB11_Pin) | \
	 defined(DB12_Pin) | \
	 defined(DB13_Pin) | \
	 defined(DB14_Pin) | \
	 defined(DB15_Pin))
#else
#error "Configure TFT data Pins in CubeMX, set pins for DB08-DB15 and set name for this pins as DB08-DB15"
#endif
#endif
#ifdef TFT_16_ENABLED
#if (defined(DB00_Pin) | \
	 defined(DB01_Pin) | \
	 defined(DB02_Pin) | \
	 defined(DB03_Pin) | \
	 defined(DB04_Pin) | \
	 defined(DB05_Pin) | \
	 defined(DB06_Pin) | \
	 defined(DB07_Pin))
#else
#error "Configure TFT data Pins in CubeMX, set pins for DB00-DB07 and set name for this pins as DB00-DB07"
#endif
#endif
	// __HAL_RCC_GPIOC_CLK_ENABLE();
	// __HAL_RCC_GPIOB_CLK_ENABLE();
	HAL_GPIO_WritePin(GPIOC, TFT_CS_Pin | TFT_RS_Pin | TFT_WR_Pin | TFT_RD_Pin, GPIO_PIN_SET);
}
/*****************************************************************************
*****************************************************************************/
void LCD_Init(void)
{
	static uint16_t DeviceCode;
	LCD_Configuration();
	LCD_WriteReg(0x0000, 0x0001);
	LCD_Delay(50); // LCD_Delay 50 ms
	DeviceCode = LCD_ReadReg(0x0000);
	printf(" ID=0x%x\n", DeviceCode);
	if (DeviceCode == 0x9325 || DeviceCode == 0x9328) // ILI9325
	{
		LCD_WriteReg(0x00e5, 0x78F0);
		//        LCD_WriteReg(0x0000,0x0001);
		LCD_WriteReg(0x0001, 0x0100);
		LCD_WriteReg(0x0002, 0x0700);
		LCD_WriteReg(0x0003, 0x1030);
		LCD_WriteReg(0x0004, 0x0000);
		LCD_WriteReg(0x0008, 0x0202);
		LCD_WriteReg(0x0009, 0x0000);
		LCD_WriteReg(0x000a, 0x0000);
		LCD_WriteReg(0x000c, 0x0001);
		LCD_WriteReg(0x000d, 0x0000);
		LCD_WriteReg(0x000f, 0x0000);
		// Power On sequence //
		LCD_WriteReg(0x0010, 0x0000);
		LCD_WriteReg(0x0011, 0x0007);
		LCD_WriteReg(0x0012, 0x0000);
		LCD_WriteReg(0x0013, 0x0000);
		LCD_WriteReg(0x0007, 0x0001);
		LCD_Delay(5);
		LCD_WriteReg(0x0010, 0x1690);
		LCD_WriteReg(0x0011, 0x0227);
		LCD_Delay(5);
		LCD_WriteReg(0x0012, 0x009d);
		LCD_Delay(5);
		LCD_WriteReg(0x0013, 0x1900);
		LCD_WriteReg(0x0029, 0x0025);
		LCD_WriteReg(0x002b, 0x000d);
		LCD_Delay(5);
		LCD_WriteReg(0x0020, 0x0000);
		LCD_WriteReg(0x0021, 0x0000);
		LCD_Delay(5);
		//٤��У��
		LCD_WriteReg(0x0030, 0x0007);
		LCD_WriteReg(0x0031, 0x0303);
		LCD_WriteReg(0x0032, 0x0003);
		LCD_WriteReg(0x0035, 0x0206);
		LCD_WriteReg(0x0036, 0x0008);
		LCD_WriteReg(0x0037, 0x0406);
		LCD_WriteReg(0x0038, 0x0304);
		LCD_WriteReg(0x0039, 0x0007);
		LCD_WriteReg(0x003c, 0x0602);
		LCD_WriteReg(0x003d, 0x0008);
		LCD_Delay(5);
		LCD_WriteReg(0x0050, 0x0000);
		LCD_WriteReg(0x0051, 0x00ef);
		LCD_WriteReg(0x0052, 0x0000);
		LCD_WriteReg(0x0053, 0x013f);

		LCD_WriteReg(0x0060, 0xa700);
		LCD_WriteReg(0x0061, 0x0001);
		LCD_WriteReg(0x006a, 0x0000);
		LCD_WriteReg(0x0080, 0x0000);
		LCD_WriteReg(0x0081, 0x0000);
		LCD_WriteReg(0x0082, 0x0000);
		LCD_WriteReg(0x0083, 0x0000);
		LCD_WriteReg(0x0084, 0x0000);
		LCD_WriteReg(0x0085, 0x0000);

		LCD_WriteReg(0x0090, 0x0010);
		LCD_WriteReg(0x0092, 0x0600);

		LCD_WriteReg(0x0007, 0x0133);
	}
	else if (DeviceCode == 0x9320 || DeviceCode == 0x9300)
	{
		LCD_WriteReg(0x00, 0x0000);
		LCD_WriteReg(0x01, 0x0100); // Driver Output Contral.
		LCD_WriteReg(0x02, 0x0700); // LCD Driver Waveform Contral.
		LCD_WriteReg(0x03, 0x1030); // Entry Mode Set.
		// LCD_WriteReg(0x03,0x1018);	//Entry Mode Set.

		LCD_WriteReg(0x04, 0x0000);	  // Scalling Contral.
		LCD_WriteReg(0x08, 0x0202);	  // Display Contral 2.(0x0207)
		LCD_WriteReg(0x09, 0x0000);	  // Display Contral 3.(0x0000)
		LCD_WriteReg(0x0a, 0x0000);	  // Frame Cycle Contal.(0x0000)
		LCD_WriteReg(0x0c, (1 << 0)); // Extern Display Interface Contral 1.(0x0000)
		LCD_WriteReg(0x0d, 0x0000);	  // Frame Maker Position.
		LCD_WriteReg(0x0f, 0x0000);	  // Extern Display Interface Contral 2.
		LCD_Delay(10);
		LCD_WriteReg(0x07, 0x0101); // Display Contral.
		LCD_Delay(10);
		LCD_WriteReg(0x10, (1 << 12) | (0 << 8) | (1 << 7) | (1 << 6) | (0 << 4)); // Power Control 1.(0x16b0)
		LCD_WriteReg(0x11, 0x0007);												   // Power Control 2.(0x0001)
		LCD_WriteReg(0x12, (1 << 8) | (1 << 4) | (0 << 0));						   // Power Control 3.(0x0138)
		LCD_WriteReg(0x13, 0x0b00);												   // Power Control 4.
		LCD_WriteReg(0x29, 0x0000);												   // Power Control 7.

		LCD_WriteReg(0x2b, (1 << 14) | (1 << 4));
		LCD_WriteReg(0x50, 0); // Set X Star
		//ˮƽGRAM��ֹλ��Set X End.
		LCD_WriteReg(0x51, 239); // Set Y Star
		LCD_WriteReg(0x52, 0);	 // Set Y End.t.
		LCD_WriteReg(0x53, 319); //

		LCD_WriteReg(0x60, 0x2700); // Driver Output Control.
		LCD_WriteReg(0x61, 0x0001); // Driver Output Control.
		LCD_WriteReg(0x6a, 0x0000); // Vertical Srcoll Control.

		LCD_WriteReg(0x80, 0x0000); // Display Position? Partial Display 1.
		LCD_WriteReg(0x81, 0x0000); // RAM Address Start? Partial Display 1.
		LCD_WriteReg(0x82, 0x0000); // RAM Address End-Partial Display 1.
		LCD_WriteReg(0x83, 0x0000); // Displsy Position? Partial Display 2.
		LCD_WriteReg(0x84, 0x0000); // RAM Address Start? Partial Display 2.
		LCD_WriteReg(0x85, 0x0000); // RAM Address End? Partial Display 2.

		LCD_WriteReg(0x90, (0 << 7) | (16 << 0)); // Frame Cycle Contral.(0x0013)
		LCD_WriteReg(0x92, 0x0000);				  // Panel Interface Contral 2.(0x0000)
		LCD_WriteReg(0x93, 0x0001);				  // Panel Interface Contral 3.
		LCD_WriteReg(0x95, 0x0110);				  // Frame Cycle Contral.(0x0110)
		LCD_WriteReg(0x97, (0 << 8));			  //
		LCD_WriteReg(0x98, 0x0000);				  // Frame Cycle Contral.
		LCD_WriteReg(0x07, 0x0173);				  //(0x0173)
		LCD_Delay(10);
	}
	LCD_Clear(BACK_COLOR);
}
/*****************************************************************************
*****************************************************************************/
void LCD_DrawPoint(uint16_t x, uint16_t y)
{
	LCD_SetCursor(x, y);
	Write_Cmd(R34);
	Write_Dat(POINT_COLOR);
}
/*****************************************************************************
*****************************************************************************/
void LCD_WriteRAM_Prepare()
{
	Write_Cmd(R34);
}
/*****************************************************************************
*****************************************************************************/
void LCD_SetCursor(uint8_t Xpos, uint16_t Ypos)
{
	LCD_WriteReg(R32, Xpos);
	LCD_WriteReg(R33, Ypos);
}
/*****************************************************************************
*****************************************************************************/
void LCD_SetDisplayWindow(uint8_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width)
{
	LCD_WriteReg(R80, Xpos);
	LCD_WriteReg(R81, Xpos + Height);
	LCD_WriteReg(R82, Ypos);
	LCD_WriteReg(R83, Ypos + Width);

	LCD_SetCursor(Xpos, Ypos);
}
/*****************************************************************************
*****************************************************************************/
#define MAX_CHAR_POSX 232
#define MAX_CHAR_POSY 304
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
void LCD_ShowChar(uint8_t x, uint16_t y, uint8_t chars, uint8_t size, uint8_t mode)
{
	uint8_t temp;
	uint8_t pos, t;
	if (x > MAX_CHAR_POSX || y > MAX_CHAR_POSY)
		return;

	LCD_SetDisplayWindow(x, y, (size / 2 - 1), size - 1);

	LCD_WriteRAM_Prepare();
	if (!mode)
	{
		for (pos = 0; pos < size; pos++)
		{
			if (size == 12)
				temp = ASCII_1206[chars - 0x20][pos];
			else
				temp = ASCII_1608[chars - 0x20][pos];
			for (t = 0; t < size / 2; t++)
			{
				// if(temp&0x01)
				if ((temp << t) & 0x80)
				{
					Write_Dat(RED);
				}
				else
				{
					Write_Dat(WHITE);
				}
				// temp>>=1;
			}
		}
	}
	else
	{
		for (pos = 0; pos < size; pos++)
		{
			if (size == 12)
				temp = ASCII_1206[chars - 0x20][pos];
			else
				temp = ASCII_1608[chars - 0x20][pos];
			for (t = 0; t < size / 2; t++)
			{
				if ((temp << t) & 0x80)
					LCD_DrawPoint(x + t, y + pos);
				// temp>>=1;
			}
		}
	}
	LCD_WriteReg(R80, 0x0000);
	LCD_WriteReg(R81, 0x00EF);
	LCD_WriteReg(R82, 0x0000);
	LCD_WriteReg(R83, 0x013F);
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
	// uint16_t usIndex;
	uint16_t usWidth = 0;
	// FNT_GB16 *ptGb16 = 0;

	// ptGb16 = (FNT_GB16 *)GBHZ_16;
	while (1)
	{
		if (*pcStr == 0)
		{
			break;
		}
		x0 = x0 + (usWidth);
		if (*pcStr > 0x80)
		{
			// if ((x0 + 16) > LCD_W)
			// {
			// 	x0 = 0;
			// 	y0 = y0 + 16;
			// 	if (y0 > LCD_H)
			// 	{
			// 		y0 = 0;
			// 	}
			// }
			// usIndex = findHzIndex(pcStr);
			// usWidth = WriteOneHzChar((uint8_t *)&(ptGb16[usIndex].Msk[0]), x0, y0, color);
			// pcStr += 2;
		}
		else
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
uint16_t WriteOneHzChar(uint8_t *pucMsk,
						uint16_t x0,
						uint16_t y0,
						uint16_t color)
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
uint16_t WriteOneASCII(uint8_t *pucMsk,
					   uint16_t x0,
					   uint16_t y0,
					   uint16_t color)
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
		{ /* 8��                          */
			if ((ucChar << j) & 0x80)
			{ /* ��ʾ��ģ                     */
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
	return (8); /* ����16λ�п�                 */
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
void LCD_WriteBMP(uint8_t Xpos, uint16_t Ypos, uint8_t Height, uint16_t Width, uint8_t *bitmap)
{
	uint32_t index;
	uint32_t size = Height * Width;
	uint16_t *bitmap_ptr = (uint16_t *)bitmap;

	LCD_SetDisplayWindow(Xpos, Ypos, Width - 1, Height - 1);

	// LCD_WriteReg(0x03, 0x1038);

	LCD_WriteRAM_Prepare();

	for (index = 0; index < size; index++)
	{
		Write_Dat(*bitmap_ptr++);
	}
	LCD_WriteReg(R80, 0x0000);
	LCD_WriteReg(R81, 0x00EF);
	LCD_WriteReg(R82, 0x0000);
	LCD_WriteReg(R83, 0x013F);
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
	di = 3 - (r << 1); //�ж��¸���λ�õı�־
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
		//ʹ��Bresenham�㷨��Բ
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
void LCD_Fill(uint8_t xsta, uint16_t ysta, uint8_t xend, uint16_t yend, uint16_t color)
{
	uint32_t n;
	//���ô���
	LCD_WriteReg(R80, xsta);
	LCD_WriteReg(R81, xend);
	LCD_WriteReg(R82, ysta);
	LCD_WriteReg(R83, yend);
	LCD_SetCursor(xsta, ysta);
	LCD_WriteRAM_Prepare(); //��ʼд��GRAM
	n = (uint32_t)(yend - ysta + 1) * (xend - xsta + 1);
	while (n--)
	{
		Write_Dat(color);
	} //��ʾ��������ɫ.
	//�ָ�����
	LCD_WriteReg(R80, 0x0000);
	LCD_WriteReg(R81, 0x00EF);
	LCD_WriteReg(R82, 0x0000);
	LCD_WriteReg(R83, 0x013F);
}
/*****************************************************************************
*****************************************************************************/
void LCD_Delay(uint32_t nCount)
{
	// __IO uint16_t i;
	// for (i = 0; i < nCount * 100; i++)
	// 	// __asm__ __volatile__("nop");
	// 	;
	HAL_Delay(nCount);
}
/*********************************************************************************************************
** End of File
*********************************************************************************************************/
#endif /*ILI932x_ENABLED*/