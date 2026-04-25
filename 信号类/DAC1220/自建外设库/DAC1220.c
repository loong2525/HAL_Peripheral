/*
 * @Compony: NUC
 * @Date: 2026-04-24 09:01:27
 * @LastEditors: Loong2525
 * @LastEditTime: 2026-04-25 13:17:24
 */

#include "DAC1220.h"
#include "stdint.h"

#include "core_cm3.h"  // F1
//#include "core_cm4.h"  // F4
//#include "core_cm7.h"  // H7

//写
#define Write_1_B 0X00 
#define Write_2_B 0X20
#define Write_3_B 0X40 
//读
#define Read_1_B 0X80
#define Read_2_B 0XA0
#define Read_3_B 0XC0

//寄存器地址
#define ADR_0 0X00//DIR byte 2
#define ADR_1 0X01//DIR byte 1
#define ADR_2 0X02//DIR byte 0
#define ADR_3 0X03//Reserved
#define ADR_4 0X04//CMR byte 1
#define ADR_5 0X05//CMR byte 0
#define ADR_6 0X06//Reserved
#define ADR_7 0X07//Reserved
#define ADR_8 0X08//OCR byte 2
#define ADR_9 0X09//OCR byte 1
#define ADR_10 0X0A//OCR byte 0
#define ADR_11 0X0B//Reserved
#define ADR_12 0X0C//FCR byte 2
#define ADR_13 0X0D//FCR byte 1
#define ADR_14 0X0E//FCR byte 0
#define ADR_15 0X0F//Reserved

#define WriteDIR (Write_2_B | ADR_0)//写数据寄存器
#define WriteCMR (Write_2_B | ADR_4)//写命令寄存器
#define ReadDIR (Read_2_B | ADR_0)//读数据寄存器
#define ReadCMR (Read_2_B | ADR_4)//读命令寄存器
#define ReadOCR (Read_3_B | ADR_8)//读偏置校准寄存器
#define ReadFCR (Read_3_B | ADR_12)//读增益校准寄存器


//命令寄存器
#define CMR_15 0X0F//ADPT自适应滤波
#define CMR_14 0X0E//CALPIN校准引脚选择
#define CMR_13 0X0D//Reserved
#define CMR_12 0X0C//Reserved
#define CMR_11 0X0B//Reserved
#define CMR_10 0X0A//Reserved
#define CMR_9 0X09//CRST 清除OCR寄存器
#define CMR_8 0X08//Reserved
#define CMR_7 0X07//Res 选择分辨率
#define CMR_6 0X06//CLR 清除data寄存器
#define CMR_5 0X05//DF 数据格式选择
#define CMR_4 0X04//DISF 自适应滤波选择
#define CMR_3 0X03//BD 地址递增模式选择
#define CMR_2 0X02//MSB 大小端选择
#define CMR_1 0X01//MD 模式选择
#define CMR_0 0X00//MD 模式选择

//CMR配置值
#define Work_Mode 0x2080//0b0010000010000000 20位模式，正常工作
#define Cal_Mode  0x2281//0b0010001010000001 20位模式，校准模式



uint32_t TriangleWave_Value[256]={
				0 ,  8192 , 16384 , 24576 , 32768 , 40960 , 49152 , 57344 , 65536 , 73728 , 81920 , 90112 , 98304 , 106496 , 
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

/**
 * @name: delay_us
 * @param {uint32_t} us
 * @description: 延时函数，延时us微秒
 * @note:对于对延迟精度要求极高（尤其是 < 5 μs）或需要极长延迟（> 数十秒）的应用，建议额外补偿或改用定时器
 */
static void delay_us(uint32_t us)
{
    // 使能 DWT 计数器（若未使能）
    if (!(DWT->CTRL & DWT_CTRL_CYCCNTENA_Msk)) {
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // 使能跟踪
        DWT->CYCCNT = 0;
        DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    }
    uint32_t ticks_start = DWT->CYCCNT;
    uint32_t ticks_needed = us * (HAL_RCC_GetHCLKFreq() / 1000000);  
	// 根据当前系统时钟计算 f1 72000000 / 1000000 = 72 ticks/us 
	// F4 168000000 / 1000000 = 168 ticks/us 
	// H7 216000000 / 1000000 = 216 ticks/us 
    while( (uint32_t)(DWT->CYCCNT - ticks_start) < ticks_needed );
}

/**
 * @name: SDIO_Output_Mode
 * @description: 配置SDIO引脚为输出模式
 */
static void SDIO_Output_Mode(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DAC_SDIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DAC_SDIO_PORT, &GPIO_InitStruct);
}

/**
 * @name: SDIO_Input_Mode
 * @description: 配置SDIO引脚为输入模式
 */
static void SDIO_Input_Mode(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DAC_SDIO_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(DAC_SDIO_PORT, &GPIO_InitStruct);
}
/**
 * @name: DAC1220_IO_Init
 * @description: 初始化DAC1220的IO引脚
 */
static void DAC1220_IO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // 使能 GPIO 时钟
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // CS 推挽输出
    GPIO_InitStruct.Pin = DAC_CS_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DAC_CS_PORT, &GPIO_InitStruct);

    // SCLK 推挽输出
    GPIO_InitStruct.Pin = DAC_SCLK_PIN;
    HAL_GPIO_Init(DAC_SCLK_PORT, &GPIO_InitStruct);

    // SDIO 默认为输出模式
    SDIO_Output_Mode();

    // 初始电平：CS 拉低（选中），SCLK 低电平
    DAC_CS_LOW();
    DAC_SCLK_LOW();
}
/**
 * @name: DAC1220_Reset
 * @description: 利用SCL的复位时序复位DAC1220
 */
static void DAC1220_Reset(void)
{
    DAC_SCLK_LOW();
    delay_us(10);

    // 复位时序
    DAC_SCLK_HIGH();
    delay_us(600 * TXIN);		//t16 
    DAC_SCLK_LOW();
    delay_us(20 * TXIN);		//t17
    DAC_SCLK_HIGH();
    delay_us(1100 * TXIN);		//t18
    DAC_SCLK_LOW();
    delay_us(20 * TXIN);		//t17
    DAC_SCLK_HIGH();
    delay_us(2200 * TXIN);		//t19
    DAC_SCLK_LOW();

    delay_us(10);
}
/**
 * @name: DAC1220_Write_Byte
 * @param {uint8_t} data
 * @description: 写一个字节（MSB 先）
 */
void DAC1220_Write_Byte(uint8_t data)
{
    SDIO_Output_Mode();
    DAC_SCLK_LOW();
    DAC_SDIO_LOW();
	delay_us(5);
    for (uint8_t i = 0; i < 8; i++) 
	{
        if ((data & 0x80)==0x80)
            DAC_SDIO_HIGH();
        else
            DAC_SDIO_LOW();
        data = data << 1;
        delay_us(5);
        DAC_SCLK_HIGH();   
        delay_us(5*TXIN);		//t3
        DAC_SCLK_LOW();			// 下降沿数据写入
		delay_us(5*TXIN);		//t4
    }
}

/**
 * @name: DAC1220_Read_Byte
 * @description: 读一个字节（MSB 先）
 */
uint8_t DAC1220_Read_Byte(void)
{
    uint8_t data = 0;
    SDIO_Input_Mode();
    DAC_SCLK_LOW();
	delay_us(5);
    for (uint8_t i = 0; i < 8; i++) 
	{
        DAC_SCLK_HIGH();
		delay_us(1);
        data = data << 1;
        if (DAC_SDIO_READ())
            data |= 0x01;
        delay_us(5*TXIN-1);		//t3
        DAC_SCLK_LOW();			
		delay_us(5*TXIN);		//t4
    }
    return data;
}

/**
 * @name: DAC1220_Self_Calibration
 * @description: 执行DAC1220的自校准流程
 * @return {uint8_t} 0 校准成功，1 校准失败
 */
static uint8_t DAC1220_Self_Calibration(void)
{
    // // 进入校准模式
    // DAC1220_Write_Byte(WriteCMR);   
    // DAC1220_Write_Byte(0x22);   // 写命令寄存
    // DAC1220_Write_Byte(0x81);   
    // HAL_Delay(600);             
    // 检测校准是否完成
    // DAC1220_Write_Byte(ReadCMR);   // 读命令寄存器低字节
    // delay_us(10);
    // for(uint i=0;(DAC1220_Read_Byte() & 0x03) != 0; i++) 
	// {
    // 	HAL_Delay(50);
	// 	if(i > 10) {
	// 		return 1; // 校准失败，超时
    // 	}
	// }
    // return 0; // 校准成功

    DAC1220_Write_Byte(0x04);
    delay_us(10);
    DAC1220_Write_Byte(0x00);
    delay_us(10);
    DAC1220_Write_Byte(0x05);
    delay_us(10);
    DAC1220_Write_Byte(0xA1);
    HAL_Delay(600);

    //检测校准是否完成
    DAC1220_Write_Byte(0x85);   // 读命令寄存器低字节
    delay_us(10);
    for(uint8_t i=0;(DAC1220_Read_Byte() & 0x03) != 0; i++) 
		{
			HAL_Delay(500);
			if(i > 10) 
			{
				return 1; // 校准失败，超时
			}
		}
    return 0; // 校准成功

}

/**
 * @name: DAC1220_Init
 * @description: 初始化DAC1220，执行复位和自校准
 * @return {uint8_t} 0 初始化成功，1 初始化失败
 */
uint8_t DAC1220_Init(void)
{
    HAL_Delay(100); // 上电稳定延时
    DAC1220_IO_Init();
    DAC1220_Reset();
    uint8_t i = DAC1220_Self_Calibration();
    DAC1220_Write_Byte(0x04);
    delay_us(10);
    DAC1220_Write_Byte(0x00);
    delay_us(10);
    DAC1220_Write_Byte(0x05);
    delay_us(10);
    DAC1220_Write_Byte(0xA0); //直接二进制
    return i;
}
/**
 * @name: DAC1220_WDAT
 * @param {uint32_t} dat
 * @description: 写入DAC数据
 */
void DAC1220_WDAT(uint32_t dat)
{
    if (dat > 1048575) dat = 1048575;  // 2的20次方 - 1，确保数据不超过20位最大值
    dat <<= 4;  // 20 位数据左移 4 位变成 24 位格式

    // 写高 8 位
    DAC1220_Write_Byte(0x00);
    delay_us(10);
    DAC1220_Write_Byte((dat >> 16)&0x00FF);
    delay_us(10);
    // 写中 8 位
    DAC1220_Write_Byte(0x01);
    delay_us(10);
    DAC1220_Write_Byte((dat >> 8)&0x00FF);
    delay_us(10);
    // 写低 8 位
    DAC1220_Write_Byte(0x02);
    delay_us(10);
    DAC1220_Write_Byte((dat)&0x00FF);
    delay_us(10);
}

/**
 * @name: mapfloat
 * @param {float} x,输出电压值
 * @param {float} in_min，输入电压范围最小值
 * @param {float} in_max，输入电压范围最大值
 * @param {float} out_min，输出数字范围最小值
 * @param {float} out_max，输出数字范围最大值
 * @description: 浮点数映射函数,将输入值x从范围[in_min, in_max]线性映射到范围[out_min, out_max]
 */
uint32_t mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (uint32_t)((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}

/**
 * @name: DAC1220_VoltageOutput
 * @param {float} voltage
 * @description: 输出指定电压
 */
void DAC1220_VoltageOutput(float voltage)
{
    uint32_t dacData;
    dacData =mapfloat(voltage,-10.0f,10.0f,0.0f,1048575.0f); // 将电压值映射到DAC的数字范围
    DAC1220_WDAT(dacData);
}




