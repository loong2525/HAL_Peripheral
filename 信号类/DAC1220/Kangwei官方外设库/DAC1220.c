#include "DAC1220.h"

u32 TriangleWave_Value[256]={
0 ,8192 , 16384 , 24576 , 32768 , 40960 , 49152 , 57344 , 65536 , 73728 , 81920 , 90112 , 98304 , 106496 , 
	114688 , 122880 , 131072 , 139264 , 147456 , 155648 , 163840 , 172032 , 180224 , 188416 , 196608 , 204800 , 
	212992 , 221184 , 229376 , 237568 , 245760 , 253952 , 262144 , 270336 , 278528 , 286720 , 294912 , 303104 , 
	311296 , 319488 , 327680 , 335872 , 344064 , 352256 , 360448 , 368640 , 376832 , 385024 , 393216 , 401408 , 
	409600 , 417792 , 425984 , 434176 , 442368 , 450560 , 458752 , 466944 , 475136 , 483328 , 491520 , 499712 , 
	507904 , 516096 , 524288 , 532480 , 540672 , 548864 , 557056 , 565248 , 573440 , 581632 , 589824 , 598016 , 
	606208 , 614400 , 622592 , 630784 , 638976 , 647168 , 655360 , 663552 , 671744 , 679936 , 688128 , 696320 , 
	704512 , 712704 , 720896 , 729088 , 737280 , 745472 , 753664 , 761856 , 770048 , 778240 , 786432 , 794624 , 
	802816 , 811008 , 819200 , 827392 , 835584 , 843776 , 851968 , 860160 , 868352 , 876544 , 884736 , 892928 , 
	901120 , 909312 , 917504 , 925696 , 933888 , 942080 , 950272 , 958464 , 966656 , 974848 , 983040 , 991232 , 
	999424 , 1007616 , 1015808 , 1024000 , 1032192 , 1040384 , 1048576 ,1040384 , 1032192 , 1024000 , 1015808 , 1007616 , 
	999424 , 991232 , 983040 , 974848 , 966656 , 958464 , 950272 , 942080 , 933888 , 925696 , 917504 , 909312 , 901120 , 892928 , 
	884736 , 876544 , 868352 , 860160 , 851968 , 843776 , 835584 , 827392 , 819200 , 811008 , 802816 , 794624 , 786432 , 778240 , 
	770048 , 761856 , 753664 , 745472 , 737280 , 729088 , 720896 , 712704 , 704512 , 696320 , 688128 , 679936 , 671744 , 663552 , 
	655360 , 647168 , 638976 , 630784 , 622592 , 614400 , 606208 , 598016 , 589824 , 581632 , 573440 , 565248 , 557056 , 548864 , 
	540672 , 532480 , 524288 , 516096 , 507904 , 499712 , 491520 , 483328 , 475136 , 466944 , 458752 , 450560 , 442368 , 434176 , 
	425984 , 417792 , 409600 , 401408 , 393216 , 385024 , 376832 , 368640 , 360448 , 352256 , 344064 , 335872 , 327680 , 319488 , 
	311296 , 303104 , 294912 , 286720 , 278528 , 270336 , 262144 , 253952 , 245760 , 237568 , 229376 , 221184 , 212992 , 204800 , 
	196608 , 188416 , 180224 , 172032 , 163840 , 155648 , 147456 , 139264 , 131072 , 122880 , 114688 , 106496 , 98304 , 90112 , 
	81920 , 73728 , 65536 , 57344 , 49152 , 40960 , 32768 , 24576 , 16384 , 8192
};

void DAC1220_IO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(	DAC_SCL_CLK|DAC_SDA_CLK|DAC_CS_CLK|RCC_APB2Periph_AFIO, ENABLE );	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);

	GPIO_InitStructure.GPIO_Pin = DAC_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DAC_SCL_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DAC_SDA_PIN;
	GPIO_Init(DAC_SDA_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = DAC_CS_PIN;
	GPIO_Init(DAC_CS_PORT, &GPIO_InitStructure);
	
	DAC_CS = 0;
}

void SDA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = DAC_SDA_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DAC_SDA_PORT, &GPIO_InitStructure);
}

void SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = DAC_SDA_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_Init(DAC_SDA_PORT, &GPIO_InitStructure);
}

void DAC1220_Write_Byte(uint8_t out_data)
{
	uint8_t index;
	SDA_OUT();
	DAC_SCLK=0;
	DAC_SDIO=0;
	for(index=0;index<8;index++)
	{
		delay_us(5);
		DAC_SCLK=1;
		if((out_data&0x80)==0x80)
		{
			DAC_SDIO=1;
		}
		else
		{
			DAC_SDIO=0;
		}
		out_data=out_data<<1;		//数据移位
		delay_us(5);
		DAC_SCLK=0;		//锁存数据
	}
}
uint8_t DAC1220_Read_Byte(void)
{
	uint8_t data=0,index=0;
	SDA_IN();
	DAC_SCLK=0;
	for(index=0;index<8;index++)
	{
		delay_us(5);
		DAC_SCLK=1;
		data<<=1;
		if(R_DAC_SDIO)
			data++;
		delay_us(5);
		DAC_SCLK=0;		//锁存数据
	}
	delay_us(5);
	return data;
}


/*复位DA*/
void DAC1220_Reset(void)
{
	DAC_SCLK = 0;
	delay_us(10);
	
//****//
//SCLK复位模式
//DAC1220没有专用的复位引脚。
//相反，它包含一个等待特殊模式出现在SCLK上的电路，并在检测到特殊模式时触发内部硬件复位线。
//此模式称为SCLK重置模式。
//这种模式与SCLK上通常出现的时钟模式有很大的不同，在正常工作时不太可能被意外检测到。CS低有效
//详见DAC1220.PDF:页11：Table 5. Reset Timing Characteristics
	DAC_SCLK = 1;
	delay_us(600*TXIN);
	DAC_SCLK = 0;
	delay_us(20*TXIN);
	DAC_SCLK = 1;
	delay_us(1100*TXIN);
	DAC_SCLK = 0;
	delay_us(20*TXIN);
	DAC_SCLK = 1;
	delay_us(2100*TXIN);
	DAC_SCLK = 0;
//****//
	delay_us(10);
}

void DAC1220_Init(void)
{
	uint8_t command;			//缓存命令字节
	DAC1220_IO_Init();
	DAC1220_Reset();
	DAC1220_Self_Calibration();//自校准
	command=0x04;
	DAC1220_Write_Byte(command);
	delay_us(10);
	DAC1220_Write_Byte(0x00);
	delay_us(10);
	command=0x05;
	DAC1220_Write_Byte(command);
	delay_us(10);
	DAC1220_Write_Byte(0xA0);	//配置成正常20位模式，(直接二进制)Straight binary
	delay_us(10);
	
}

void DAC1220_WDAT(uint32_t dat)
{
	uint8_t command;

	if(dat > 1048575)
		dat = 1048575;
	dat = dat<<4;
	
	delay_us(10);
	command=0x00;		//DIR高字节
	DAC1220_Write_Byte(command);
	delay_us(10);
	command=(dat>>16)&0X00FF;			//写DIR高位数据
	DAC1220_Write_Byte(command);
	delay_us(10);

	command=0x01;		//写中位数据
	DAC1220_Write_Byte(command);
	delay_us(10);
	command=(dat>>8)&0X00FF;
	DAC1220_Write_Byte(command);
	delay_us(10);

	command=0x02;		//写低位数据
	DAC1220_Write_Byte(command);
	delay_us(10);
	command=(dat>>0)&0X00FF;
	DAC1220_Write_Byte(command);
	delay_us(10);

}

void DAC1220_Self_Calibration(void) //自校准
{
	DAC1220_Write_Byte(0x04);//写命令 寄存器高字节
	delay_us(10);
	DAC1220_Write_Byte(0x00);//校准期间输出将断开
	delay_us(10);
	DAC1220_Write_Byte(0x05);//写命令 寄存器低字节
	delay_us(10);
	DAC1220_Write_Byte(0xA1);	//配置成20位模式，(直接二进制)Straight binary  校准模式
	delay_ms(600); //等待校准
	
	DAC1220_Write_Byte(0x85);//读命令 寄存器低字节
	delay_us(10);
	while((DAC1220_Read_Byte()&0x03)!=0) //检测校准是否完成
	{
		delay_ms(500);
	}
	
}
void DAC1220VolWrite(float v)
{
	uint32_t dacData;
	dacData=mapfloat(v,-10.0,10.0,0,1048575);
	DAC1220_WDAT(dacData);
}


/*
************************************************************
*	函数名称：	mapfloat
*
*	函数功能：	将一个区间内的值，映射到另一个区间
*
*	入口参数：	x输入值、
*						in_min输入最小值，
*						in_max输入最大值，
*						out_min输出最小值，
*						out_max输出最大值。
*	返回参数：	映射后的值
*	说明：	
************************************************************/
uint32_t mapfloat(float x, float in_min, float in_max, uint32_t out_min, uint32_t out_max)
{
	uint32_t out;
	out=(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;

 return out;
  
}
