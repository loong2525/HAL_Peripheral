#include "Menu.h"

#define ROW_HEIGHT 14

uint16_t MenuIndex=1;
uint16_t Choose=0;
//创建一级菜单
MENU menu;

//选择菜单   
void Menu_switch(MENU* menu)
{
	if(menu ->confirm_flag ==1)      											//进入下一级
	{
		MenuIndex*=10;
		menu ->confirm_flag =0;
		Choose=0;
		OLED_Clear();
	}
	if(menu ->return_flag ==1)		 	  										//返回上一级
	{
		MenuIndex /=10;
		menu ->return_flag =0;
		Choose=0;
		OLED_Clear();
	}
	if(menu->previous_item_flag ==1)                      //选择上一项
	{
		MenuIndex-=1;
		menu->previous_item_flag =0;     
		Choose-=ROW_HEIGHT;
		OLED_Clear();
	}
	if(menu->next_item_flag ==1)													//选择下一项
	{
		MenuIndex+=1;
		menu->next_item_flag =0;
		Choose+=ROW_HEIGHT;
		OLED_Clear();
	}
}
void Menu_show()																			//调用该函数显示UI界面,选择任务
{
	OLED_ShowString(112,Choose,"<-",OLED_8X16 ); 
	OLED_ShowNum(0,42,MenuIndex ,3,OLED_8X16 );
	switch(MenuIndex)
	{
		case 1://开始界面
		{
			OLED_ShowString(0,0,"Menu",OLED_8X16 );
			OLED_ShowString(0,14,"Test",OLED_8X16 );
			OLED_ShowString(0,28,"About",OLED_8X16 );
			break;
		}
		case 2:
		{
			OLED_ShowString(0,0,"Menu",OLED_8X16 );
			OLED_ShowString(0,14,"Test",OLED_8X16 );
			OLED_ShowString(0,28,"About",OLED_8X16 );
			break;
		}
		case 3:
		{
			OLED_ShowString(0,0,"Menu",OLED_8X16 );
			OLED_ShowString(0,14,"Test",OLED_8X16 );
			OLED_ShowString(0,28,"About",OLED_8X16 );
			break;
		}
		case 10:
		{
			OLED_ShowString(0,0,"blank",OLED_8X16 );
			break;
		}
		case 20:
		{
			OLED_ShowString(0,0,"Test1",OLED_8X16 );
			OLED_ShowString(0,14,"Test2",OLED_8X16 );
			OLED_ShowString(0,28,"Test3",OLED_8X16 );
			break;
		}
		case 21:
		{
			OLED_ShowString(0,0,"Test1",OLED_8X16 );
			OLED_ShowString(0,14,"Test2",OLED_8X16 );
			OLED_ShowString(0,28,"Test3",OLED_8X16 );
			break;
		}
		case 22:
		{
			OLED_ShowString(0,0,"Test1",OLED_8X16 );
			OLED_ShowString(0,14,"Test2",OLED_8X16 );
			OLED_ShowString(0,28,"Test3",OLED_8X16 );
			break;
		}
		case 200:
		{
			OLED_ShowString(0,0,"Test1",OLED_8X16 );
			//Test1();
			break;
		}
		case 210:
		{
			OLED_ShowString(0,0,"Test2",OLED_8X16 );
			//Test2();
			break;
		}
		case 220:
		{
			OLED_ShowString(0,0,"Test3",OLED_8X16 );
			//Test3();
			break;
		}
		case(30):
		{
			OLED_ShowString(0,0,"Hello,world!",OLED_8X16 );
			OLED_ShowString(0,14,"By loong2525!",OLED_8X16 );
			break;
		}
	}
}   
