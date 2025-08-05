#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "stm32f1xx_hal.h"  // HAL��ͷ�ļ�

#define USE_HORIZONTAL 1  // ��Ļ����0��1Ϊ������2��3Ϊ����

#if USE_HORIZONTAL==0 || USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 160
#else
#define LCD_W 160
#define LCD_H 128
#endif

// ���Ŷ��� - ʹ��HAL��GPIO����
#define LCD_SCLK_Clr() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET)
#define LCD_SCLK_Set() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET)

#define LCD_MOSI_Clr() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET)
#define LCD_MOSI_Set() HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET)
 
#define LCD_RES_Clr()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET)
#define LCD_RES_Set()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET)
#define LCD_DC_Set()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET)

#define LCD_CS_Clr()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
#define LCD_CS_Set()   HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)

#define LCD_BLK_Clr()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET)
#define LCD_BLK_Set()  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET)

void LCD_GPIO_Init(void);  // GPIO��ʼ��
void LCD_Writ_Bus(uint8_t dat);  // ģ��SPIд����
void LCD_WR_DATA8(uint8_t dat);  // д8λ����
void LCD_WR_DATA(uint16_t dat);  // д16λ����
void LCD_WR_REG(uint8_t dat);  // д����
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);  // ������ʾ����
void LCD_Init(void);  // LCD��ʼ��

#endif

