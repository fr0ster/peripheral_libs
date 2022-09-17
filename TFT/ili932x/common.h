#ifndef __COMMON_H
#define __COMMON_H

// #include <stdio.h>
// // #include <stdint.h>

// //TFTLCD������Ҫ���õĺ���		   
// extern uint16_t  POINT_COLOR;//Ĭ�Ϻ�ɫ    
// extern uint16_t  BACK_COLOR; //������ɫ.Ĭ��Ϊ��ɫ

// /* LED ���� */
// #define LED1 PAout(2)	   //�����϶�Ӧ��LED1
// #define LED2 PAout(3)	   //�����϶�Ӧ��LED2

// /* ���� ���� */
// #define KEY1   PAin(0)	   //�����ϵ�KEY1��
// #define KEY2   PAin(1)	   //�����ϵ�KEY2��

// /* LCD ������������*/
// #define LCD_CS  PCout(8)
// #define LCD_RS	PCout(9)
// #define LCD_WR  PCout(10)
// #define LCD_RD	PCout(11)

//����LCD�ĳߴ�
#define LCD_W 240
#define LCD_H 320

/***********************************************************************************
������ɫ�궨��
***********************************************************************************/
#define   BLACK        0x0000                    /* ��ɫ�� 0, 0, 0               */
#define   NAVY         0x000F                    /* ����ɫ�� 0, 0, 128           */
#define   DGREEN       0x03E0                    /* ����ɫ�� 0, 128, 0           */
#define   DCYAN        0x03EF                    /* ����ɫ�� 0, 128, 128         */
#define   MAROON       0x7800                    /* ���ɫ��128, 0, 0            */
#define   PURPLE       0x780F                    /* ��ɫ�� 128, 0, 128           */
#define   OLIVE        0x7BE0                    /* ����̣�128, 128, 0          */
#define   LGRAY        0xC618                    /* �Ұ�ɫ��192, 192, 192        */
#define   DGRAY        0x7BEF                    /* ���ɫ��128, 128, 128        */
#define   BLUE         0x001F                    /* ��ɫ�� 0, 0, 255             */
#define   GREEN        0x07E0                 	 /* ��ɫ�� 0, 255, 0             */
#define   CYAN         0x07FF                    /* ��ɫ�� 0, 255, 255           */
#define   RED          0xF800                    /* ��ɫ�� 255, 0, 0             */
#define   MAGENTA      0xF81F                    /* Ʒ�죺 255, 0, 255           */
#define   YELLOW       0xFFE0                    /* ��ɫ�� 255, 255, 0           */
#define   WHITE        0xFFFF                    /* ��ɫ�� 255, 255, 255         */
#define   IDMCOLOR(color) (((color & 0x001F) << 11) | ((color & 0xF800) >> 11) | (color & 0x07E0))

#endif	    
		
