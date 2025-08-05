#ifndef _AD9833_H
#define _AD9833_H
#include "main.h"

// 第一路AD9833引脚定义（GPIOA）
#define AD9833A_SDATA_PORT  GPIOD
#define AD9833A_SDATA_PIN   GPIO_PIN_6
#define AD9833A_SCLK_PORT   GPIOD
#define AD9833A_SCLK_PIN    GPIO_PIN_5
#define AD9833A_FSYNC_PORT  GPIOD
#define AD9833A_FSYNC_PIN   GPIO_PIN_4

// 第二路AD9833引脚定义（GPIOB）
#define AD9833B_SDATA_PORT  GPIOB
#define AD9833B_SDATA_PIN   GPIO_PIN_6
#define AD9833B_SCLK_PORT   GPIOB
#define AD9833B_SCLK_PIN    GPIO_PIN_5
#define AD9833B_FSYNC_PORT  GPIOB
#define AD9833B_FSYNC_PIN   GPIO_PIN_4  

// 快速设置引脚电平的宏
#define AD9833A_SDATA_HIGH  HAL_GPIO_WritePin(AD9833A_SDATA_PORT, AD9833A_SDATA_PIN, GPIO_PIN_SET)
#define AD9833A_SDATA_LOW   HAL_GPIO_WritePin(AD9833A_SDATA_PORT, AD9833A_SDATA_PIN, GPIO_PIN_RESET)
#define AD9833A_SCLK_HIGH   HAL_GPIO_WritePin(AD9833A_SCLK_PORT, AD9833A_SCLK_PIN, GPIO_PIN_SET)
#define AD9833A_SCLK_LOW    HAL_GPIO_WritePin(AD9833A_SCLK_PORT, AD9833A_SCLK_PIN, GPIO_PIN_RESET)
#define AD9833A_FSYNC_HIGH  HAL_GPIO_WritePin(AD9833A_FSYNC_PORT, AD9833A_FSYNC_PIN, GPIO_PIN_SET)
#define AD9833A_FSYNC_LOW   HAL_GPIO_WritePin(AD9833A_FSYNC_PORT, AD9833A_FSYNC_PIN, GPIO_PIN_RESET)

// 第二路AD9833引脚电平宏
#define AD9833B_SDATA_HIGH  HAL_GPIO_WritePin(AD9833B_SDATA_PORT, AD9833B_SDATA_PIN, GPIO_PIN_SET)
#define AD9833B_SDATA_LOW   HAL_GPIO_WritePin(AD9833B_SDATA_PORT, AD9833B_SDATA_PIN, GPIO_PIN_RESET)
#define AD9833B_SCLK_HIGH   HAL_GPIO_WritePin(AD9833B_SCLK_PORT, AD9833B_SCLK_PIN, GPIO_PIN_SET)
#define AD9833B_SCLK_LOW    HAL_GPIO_WritePin(AD9833B_SCLK_PORT, AD9833B_SCLK_PIN, GPIO_PIN_RESET)
#define AD9833B_FSYNC_HIGH  HAL_GPIO_WritePin(AD9833B_FSYNC_PORT, AD9833B_FSYNC_PIN, GPIO_PIN_SET)
#define AD9833B_FSYNC_LOW   HAL_GPIO_WritePin(AD9833B_FSYNC_PORT, AD9833B_FSYNC_PIN, GPIO_PIN_RESET)

/* 波形模式 */
#define AD9833_OUT_SINUS    ((0 << 5) | (0 << 1))  // 正弦波（MODE=0, OPBITEN=0）
#define AD9833_OUT_TRIANGLE ((0 << 5) | (1 << 1))  // 三角波（MODE=1, OPBITEN=0）
#define AD9833_OUT_SQUARE   ((1 << 5) | (0 << 3))  // 方波（OPBITEN=1, DIV2=0）

/* 寄存器地址 */
#define AD9833_REG_FREQ0    (1 << 14)  // 频率寄存器0
#define AD9833_REG_FREQ1    (2 << 14)  // 频率寄存器1
#define AD9833_REG_PHASE0   (6 << 13)  // 相位寄存器0
#define AD9833_REG_PHASE1   (7 << 13)  // 相位寄存器1

/* 控制位 */
#define AD9833_B28          (1 << 13)  // 32位频率控制
#define AD9833_FSEL0        (0 << 11)  // 选择频率寄存器0
#define AD9833_FSEL1        (1 << 11)  // 选择频率寄存器1
#define AD9833_PSEL0        (0 << 10)  // 选择相位寄存器0
#define AD9833_PSEL1        (1 << 10)  // 选择相位寄存器1
#define AD9833_RESET        (1 << 8)   // 复位
#define AD9833_CLEAR_RESET  (0 << 8)   // 清除复位

// 函数声明
void AD9833_Init(void);
static void AD9833_Delay(void);
// 第一路AD9833
void AD9833A_WriteData(uint16_t txdata);
void AD9833A_SetFrequency(unsigned short reg, double fout);
void AD9833A_SetPhase(unsigned short reg, unsigned short val);
void AD9833A_Setup(unsigned int Freq_SFR, double Freq, unsigned int Phase_SFR, unsigned short Phase, unsigned int WaveMode);
// 第二路AD9833
void AD9833B_WriteData(uint16_t txdata);
void AD9833B_SetFrequency(unsigned short reg, double fout);
void AD9833B_SetPhase(unsigned short reg, unsigned short val);
void AD9833B_Setup(unsigned int Freq_SFR, double Freq, unsigned int Phase_SFR, unsigned short Phase, unsigned int WaveMode);

#endif
