#ifdef I2C_ENABLED
#include "WHxxxx.h"

I2C_HandleTypeDef *hi2c;

void initLcd(I2C_HandleTypeDef *phi2c)
{
    I2C_send(0b00110000,0,phi2c,LCD_ADDR,LCD_DELAY_MS);   // 8th bits interface
    I2C_send(0b00000010,0,phi2c,LCD_ADDR,LCD_DELAY_MS);   // set cursor on strat of line
    I2C_send(0b00001100,0,phi2c,LCD_ADDR,LCD_DELAY_MS);   // normale mode, disable cursor
    I2C_send(0b00000001,0,phi2c,LCD_ADDR,LCD_DELAY_MS);   // clear display
    hi2c = phi2c;
}

void clearLcd()
{
    I2C_send(0b00000001,0,hi2c,LCD_ADDR,LCD_DELAY_MS);   // clear display
}

void firstLineLcd()
{
    I2C_send(0b10000000,0,hi2c,LCD_ADDR,LCD_DELAY_MS);   // go to first line
}

void secondLineLcd()
{
    I2C_send(0b11000000,0,hi2c,LCD_ADDR,LCD_DELAY_MS);   // go to second line
}

#ifdef LCD2004
void thirdLineLcd()
{
    I2C_send(0b10010100,0,hi2c,LCD_ADDR,LCD_DELAY_MS);   // go to third line
}

void fourthLineLcd()
{
    I2C_send(0b11010100,0,hi2c,LCD_ADDR,LCD_DELAY_MS);   // go to fourth line
}
#endif

void LCD_SendString(char *str)
{
	while(*str) 
    {                                   
        I2C_send((uint8_t)(*str), 1, hi2c, LCD_ADDR,LCD_DELAY_MS); 
        str++;                                     
    }
}
#endif /*I2C_ENABLED*/
