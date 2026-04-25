#ifndef	_DAC1220_H_
#define	_DAC1220_H_
#include "sys.h"
#include "stm32f10x.h"
#include "delay.h"

#define DAC_SCL_PORT              GPIOC
#define DAC_SCL_CLK               RCC_APB2Periph_GPIOC
#define DAC_SCL_PIN               GPIO_Pin_11

#define DAC_SDA_PORT              GPIOC
#define DAC_SDA_CLK               RCC_APB2Periph_GPIOC
#define DAC_SDA_PIN               GPIO_Pin_10

#define DAC_CS_PORT             	GPIOC
#define DAC_CS_CLK               	RCC_APB2Periph_GPIOC
#define DAC_CS_PIN               	GPIO_Pin_9

#define DAC_SCLK PCout(11)
#define DAC_SDIO PCout(10)
#define DAC_CS	 PCout(9)

#define R_DAC_SDIO PCin(10)

#define FXIN	2.4576//MHz
#define TXIN	0.41//uS   1/FXIN

extern u32 TriangleWave_Value[];

void DAC1220_IO_Init(void);
void SDA_OUT(void);
void SDA_IN(void);
void DAC1220_Init(void);
void DAC1220_Write_Byte(uint8_t out_data);//д
uint8_t DAC1220_Read_Byte(void);//��
void DAC1220_WDAT(uint32_t dat);

void DAC1220_Reset(void);//��λ
void DAC1220_Self_Calibration(void); //��У׼

#endif

