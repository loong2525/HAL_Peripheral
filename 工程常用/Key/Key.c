#include "Key.h"

uint16_t LED_flag=1;//LED标志位

KEY sw;             //按键对象
ENCODE encode;      //旋转编码器对象

void Key_Init(void)
{
	sw.GPIOx =KEY_GPIO_Port ;
	sw.GPIO_Pin =KEY_Pin ;
	
	sw.always_press_flag =0;
	sw.long_press_flag =0;
	sw.short_press_flag =0;
	sw.last_time =0;
	sw.interval_time =0;
	sw.temp_frequency=0;
	sw.press_frequency =0;
	sw.key_flag = KEY_RESET;
	
}

void Key_Test(KEY* key)
{
	
	if(HAL_GPIO_ReadPin(key->GPIOx ,key->GPIO_Pin )==1)
	{
		key->last_time++;                                            //开始记录按压时间
		//if(key->key_flag==KEY_RESET){key->interval_time =0;key->key_flag=KEY_SET;}        
		
		if(key->last_time>=ALWAYS_TIME)
		{
			key->always_press_flag=1;           //SET 一直按 标志位
		}
		
		
	}
	else 
	{
		key->interval_time ++;
		
		key->always_press_flag=0;              //开关断开，RESET 一直按 标志位		
		if(key->last_time>=LONG_TIME&&key->last_time <=ALWAYS_TIME)//根据持续时间判断是 长按 还是 短按
		{
			key->long_press_flag =1;
			key->short_press_flag=0;
			//key->key_flag=KEY_RESET;
		}
		else if(key->last_time>=SHORT_TIME&&key->last_time<=LONG_TIME)
		{
			key->short_press_flag=1;
			key->long_press_flag=0;
			//key->key_flag=KEY_SET;
			/*
			if( key->interval_time <INTERVAL_MAX )
			{
				key->temp_frequency ++;
			}*/
		}
		
         /*
		if(key->interval_time>=INTERVAL_MAX)
		{ 
			key->key_flag =KEY_RESET;            //一次有效操作时间到
			key->interval_time =0;         			//间隔时间清零
			key->press_frequency =key->temp_frequency;//得到有效时间内按压次数
			key->temp_frequency=0;               //归零临时记次变量
		} */
		key->last_time=0;                      //一次按键结束，清空按压持续时间

	}	
}

void Key_Handle(void )
{
	if(sw.press_frequency>=1)
	{
		switch(sw.press_frequency)
		{
			case 1:
			{
				
				break;
			}
			
			case 2:
			{
				
				break;
			}
				
			case 3:
			{
				
				break;
			}
		}
		sw.press_frequency =0;
	}
	if(sw.short_press_flag==1)
	{
		menu.confirm_flag  =1;
		sw.short_press_flag=0;
	}
	if(sw.long_press_flag==1)
	{
		menu .return_flag =1;
		sw.long_press_flag=0;
	}
	if(sw.always_press_flag==1)
	{
		MenuIndex=1;
		sw.always_press_flag=0;
	}
	
}

void Encode_Init(void)
{
	encode.current_count=0;
	encode.last_count =0;
	encode.clockwise_flag =0;
	encode.counterclockwise_flag=0;
	encode.htim=&htim1 ;
}
void Encode_Test(ENCODE* encode )
{
	encode->current_count =__HAL_TIM_GET_COUNTER(encode->htim );
	if(encode->current_count<encode->last_count)
	{
		encode ->counterclockwise_flag =1;
		encode ->clockwise_flag =0;
	}
	else if(encode->current_count>encode->last_count)
	{
		encode ->counterclockwise_flag =0;
		encode ->clockwise_flag =1;
	}
	encode->last_count =encode->current_count ;
}
void Encode_Handle(void)
{
	if(encode.clockwise_flag ==1)
	{
		menu .next_item_flag =1;
		encode.clockwise_flag =0;
		LED_flag=1;
	}
	else if(encode.counterclockwise_flag  ==1)
	{
		menu.previous_item_flag =1;
		encode.counterclockwise_flag  =0;   
		LED_flag=0;
	}
}
