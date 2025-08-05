// lcd.h
#ifndef __LCD_H
#define __LCD_H

#include "stm32f1xx_hal.h"  // 使用HAL库标准头文件

// 函数声明
void LCD_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint32_t color);
void LCD_DrawPoint(uint16_t x, uint16_t y, uint32_t color);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t color);
void Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint32_t color);

void LCD_ShowChinese(uint16_t x, uint16_t y, const uint8_t *s, uint32_t fc, uint32_t bc, uint8_t sizey, uint8_t mode);
void LCD_ShowChar(uint16_t x, uint16_t y, uint8_t num, uint32_t fc, uint32_t bc, uint8_t sizey, uint8_t mode);
void LCD_ShowString(uint16_t x, uint16_t y, const uint8_t *p, uint32_t fc, uint32_t bc, uint8_t sizey, uint8_t mode);
void LCD_ShowIntNum(uint16_t x, uint16_t y, uint16_t num, uint8_t len, uint32_t fc, uint32_t bc, uint8_t sizey);
void LCD_ShowFloatNum1(uint16_t x, uint16_t y, float num, uint8_t len, uint32_t fc, uint32_t bc, uint8_t sizey);
void LCD_ShowPicture(uint16_t x, uint16_t y, uint16_t length, uint16_t width, const uint8_t pic[]);

// 颜色定义
#define WHITE       0xFCFCFC
#define BLACK       0x000000
#define RED         0xFC0000
#define GREEN       0x00FC00
#define BLUE        0x0000FC

#endif