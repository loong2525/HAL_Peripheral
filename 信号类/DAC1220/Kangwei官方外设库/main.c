#include "stm32_config.h"
#include "stdio.h"
#include "DAC1220.h"
#include "timer.h"
#include "oled.h"
#include "key.h"

uint8_t Num;
int32_t Vol = 1000;
uint16_t dacValue = 0;

int main(void)
{

	MY_NVIC_PriorityGroup_Config(NVIC_PriorityGroup_2);	//设置中断分组
	delay_init(72);	//初始化延时函数
	OLED_Init();
	Key_Init();
	Timer_Init();
	
	DAC1220_Init();
	delay_ms(100);
	
	OLED_ShowString(1,5,"DAC1220");
	
	while(1)
	{
		//电压输出
		Vol += Key_GetNum();
		OLED_ShowSignedNum(2,1,Vol,5);
		
		DAC1220VolWrite((float)Vol/1000);

		
		//三角波输出
//		DAC1220_WDAT(TriangleWave_Value[dacValue]);
//		dacValue++;
//		if(dacValue >= 256) dacValue = 0;
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Num++;
		if(Num > 20)
		{
			Key_Loop();
			Num = 0;
		}
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
