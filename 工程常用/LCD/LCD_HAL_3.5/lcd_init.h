#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "stm32f1xx_hal.h"  // 包含HAL库头文件

// 屏幕方向定义:
// 0: 竖屏模式1
// 1: 竖屏模式2
// 2: 横屏模式1
// 3: 横屏模式2
#define USE_HORIZONTAL 3

// 根据方向设置屏幕尺寸
#if (USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1)
#define LCD_WIDTH  320
#define LCD_HEIGHT 480
#else
#define LCD_WIDTH  480
#define LCD_HEIGHT 320
#endif

//-----------------LCD引脚定义---------------- 
#define LCD_SCLK_PIN GPIO_PIN_3
#define LCD_MOSI_PIN GPIO_PIN_5
#define LCD_RES_PIN  GPIO_PIN_1
#define LCD_DC_PIN   GPIO_PIN_2
#define LCD_CS_PIN   GPIO_PIN_3
#define LCD_BLK_PIN  GPIO_PIN_4

#define LCD_GPIO_PORT GPIOA

// HAL库GPIO控制宏
#define LCD_SCLK_Clr() HAL_GPIO_WritePin(GPIOB, LCD_SCLK_PIN, GPIO_PIN_RESET)
#define LCD_SCLK_Set() HAL_GPIO_WritePin(GPIOB, LCD_SCLK_PIN, GPIO_PIN_SET)

#define LCD_MOSI_Clr() HAL_GPIO_WritePin(GPIOB, LCD_MOSI_PIN, GPIO_PIN_RESET)
#define LCD_MOSI_Set() HAL_GPIO_WritePin(GPIOB, LCD_MOSI_PIN, GPIO_PIN_SET)

#define LCD_RES_Clr()  HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_RES_PIN, GPIO_PIN_RESET)
#define LCD_RES_Set()  HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_RES_PIN, GPIO_PIN_SET)

#define LCD_DC_Clr()   HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_DC_PIN, GPIO_PIN_RESET)
#define LCD_DC_Set()   HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_DC_PIN, GPIO_PIN_SET)

#define LCD_CS_Clr()   HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_CS_PIN, GPIO_PIN_RESET)
#define LCD_CS_Set()   HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_CS_PIN, GPIO_PIN_SET)

#define LCD_BLK_Clr()  HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_BLK_PIN, GPIO_PIN_RESET)
#define LCD_BLK_Set()  HAL_GPIO_WritePin(LCD_GPIO_PORT, LCD_BLK_PIN, GPIO_PIN_SET)

// 类型定义
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

// 函数声明
void LCD_GPIO_Init(void);
void LCD_Writ_Bus(u8 dat);
void LCD_WR_DATA8(u8 dat);
void LCD_WR_DATA(u32 dat);
void LCD_WR_REG(u8 dat);
void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_Init(void);

#endif
