#ifndef __KEY_H
#define __KEY_H

#include "include.h"

#define SHORT_TIME 50
#define LONG_TIME 500
#define ALWAYS_TIME LONG_TIME+500
//#define INTERVAL_MAX 300


typedef enum
{
KEY_RESET=0,   
KEY_SET,
}KEYState;

typedef struct KEY
{
	uint8_t short_press_flag;
	uint8_t long_press_flag;
	uint8_t always_press_flag;
	uint16_t temp_frequency;   //临时记录次数
	uint16_t press_frequency;  //一次有效操作时间内的按压次数
	uint16_t last_time;        //按下持续时间
	uint16_t interval_time;    //断开持续时间
	KEYState key_flag;         //用户开始一次有效控制
	
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
}KEY;


extern uint16_t LED_flag;
extern KEY sw;
void Key_Init(void);
void Key_Test(KEY* key);
void Key_Handle(void);

typedef struct
{
	uint8_t clockwise_flag;
	uint8_t counterclockwise_flag;
	
	int8_t last_count;                         //记录编码器脉冲数
	int8_t current_count;                         
	TIM_HandleTypeDef *htim;
}ENCODE;
void Encode_Init(void);
void Encode_Test(ENCODE* encode );
void Encode_Handle(void);
extern ENCODE encode;
#endif
