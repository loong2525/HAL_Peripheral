#ifndef __AD9854_H
#define __AD9854_H

#include "stm32f4xx_hal.h"

// ??????
#define AD9854_RST_PIN          GPIO_PIN_1
#define AD9854_RST_PORT         GPIOA
#define AD9854_UDCLK_PIN        GPIO_PIN_2
#define AD9854_UDCLK_PORT       GPIOA
#define AD9854_WR_PIN           GPIO_PIN_3
#define AD9854_WR_PORT          GPIOA
#define AD9854_RD_PIN           GPIO_PIN_4
#define AD9854_RD_PORT          GPIOA
#define AD9854_OSK_PIN          GPIO_PIN_5
#define AD9854_OSK_PORT         GPIOA
#define AD9854_FSK_BPSK_PIN     GPIO_PIN_6
#define AD9854_FSK_BPSK_PORT    GPIOA

// ??????
#define AD9854_DATA_PORT        GPIOE

// ????
#define AUTO       1
#define MANUAL     0

// ????
typedef uint32_t  u32;
typedef uint16_t u16;
typedef uint8_t  u8;
typedef uint64_t u64;

// ????
void AD9854_IO_Init(void);
void AD9854_WR_Byte(u32 addr, u32 dat);
void Freq_convert(u32 Freq);
void AD9854_InitSingle(void);
void AD9854_SetSine(u32 Freq, u16 Shape);
void AD9854_GenerateSquareWave(u32 Freq);

#endif
