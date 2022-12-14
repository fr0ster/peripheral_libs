#include "conf.h"
#ifdef WHXXXX_ENABLED
#ifndef __WHXXXX_H
#define __WHXXXX_H


#ifdef __cplusplus
extern "C"
{
#endif
#include "WDXXXXconf.h"
#include "WHxxxx_i2c.h"

#if !defined(LCD_ADDR)
#error "Define LCD1602 or LCD2004"
#endif
#define PIN_RS (1 << 0)
#define PIN_EN (1 << 2)
#define BACKLIGHT (1 << 3)

#define LCD_DELAY_MS 5

    void initLcd(I2C_HandleTypeDef *phi2c);

    void clearLcd();

    void firstLineLcd();

    void secondLineLcd();

#ifdef LCD2004
    void thirdLineLcd();

    void fourthLineLcd();
#endif

    void LCD_SendString(char *str);

#ifdef __cplusplus
}
#endif

#endif /* __WHXXXX_H */
#endif /*MAX6675_ENABLED*/