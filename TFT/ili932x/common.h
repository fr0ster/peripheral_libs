#ifndef __COMMON_H
#define __COMMON_H

#define LCD_W 240
#define LCD_H 320

/***********************************************************************************
***********************************************************************************/
#define   BLACK        0x0000                    /*  0,   0,   0*/
#define   NAVY         0x000F                    /*  0,   0, 128*/
#define   DGREEN       0x03E0                    /*  0, 128,   0*/
#define   DCYAN        0x03EF                    /*  0, 128, 128*/
#define   MAROON       0x7800                    /*128,   0,   0*/
#define   PURPLE       0x780F                    /*128,   0, 128*/
#define   OLIVE        0x7BE0                    /*128, 128,   0*/
#define   LGRAY        0xC618                    /*192, 192, 192*/
#define   DGRAY        0x7BEF                    /*128, 128, 128*/
#define   BLUE         0x001F                    /*0,     0, 255*/
#define   GREEN        0x07E0                 	 /*0,   255,   0*/
#define   CYAN         0x07FF                    /*0,   255, 255*/
#define   RED          0xF800                    /*255,   0,   0*/
#define   MAGENTA      0xF81F                    /*255,   0, 255*/
#define   YELLOW       0xFFE0                    /*255, 255,   0*/
#define   WHITE        0xFFFF                    /*255, 255, 255*/
#define   IDMCOLOR(color) (((color & 0x001F) << 11) | ((color & 0xF800) >> 11) | (color & 0x07E0))

#endif	    