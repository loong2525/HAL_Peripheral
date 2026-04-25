/*
 * @Compony: NUC
 * @Date: 2026-04-24 09:01:03
 * @LastEditors: Loong2525
 * @LastEditTime: 2026-04-24 09:19:09
 */

#ifndef _DAC1220_H_
#define _DAC1220_H_

#include "main.h"

#define DAC_SCLK_PORT GPIOB
#define DAC_SCLK_PIN GPIO_PIN_3

#define DAC_SDIO_PORT GPIOB
#define DAC_SDIO_PIN GPIO_PIN_4

#define DAC_CS_PORT GPIOB
#define DAC_CS_PIN GPIO_PIN_5

#define FXIN 2.4576f            // MHz
#define TXIN (1.0f / FXIN)      //us    1/FXIN
#define VREF 2.5f               //V

#define DAC_CS_HIGH()   HAL_GPIO_WritePin(DAC_CS_PORT, DAC_CS_PIN, GPIO_PIN_SET)
#define DAC_CS_LOW()    HAL_GPIO_WritePin(DAC_CS_PORT, DAC_CS_PIN, GPIO_PIN_RESET)

#define DAC_SCLK_HIGH() HAL_GPIO_WritePin(DAC_SCLK_PORT, DAC_SCLK_PIN, GPIO_PIN_SET)
#define DAC_SCLK_LOW()  HAL_GPIO_WritePin(DAC_SCLK_PORT, DAC_SCLK_PIN, GPIO_PIN_RESET)

#define DAC_SDIO_HIGH() HAL_GPIO_WritePin(DAC_SDIO_PORT, DAC_SDIO_PIN, GPIO_PIN_SET)
#define DAC_SDIO_LOW()  HAL_GPIO_WritePin(DAC_SDIO_PORT, DAC_SDIO_PIN, GPIO_PIN_RESET)
#define DAC_SDIO_READ() HAL_GPIO_ReadPin(DAC_SDIO_PORT, DAC_SDIO_PIN)

uint8_t DAC1220_Init(void);
void DAC1220_WDAT(uint32_t dat);
void DAC1220_VoltageOutput(float voltage);



extern uint32_t TriangleWave_Value[256];











#endif
