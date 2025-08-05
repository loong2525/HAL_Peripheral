#include "lcd_init.h"
#include "main.h"  // 确保包含main.h以获取系统时钟定义

// 简单延时函数，需根据实际系统时钟实现
void delay_ms(uint32_t ms)
{
    HAL_Delay(ms);
}

void LCD_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    // 使能GPIOA时钟
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    // 配置所有LCD引脚为推挽输出
    GPIO_InitStruct.Pin = LCD_SCLK_PIN | LCD_MOSI_PIN | LCD_RES_PIN | 
                          LCD_DC_PIN | LCD_CS_PIN | LCD_BLK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LCD_GPIO_PORT, &GPIO_InitStruct);
    
    // 初始化所有引脚为高电平
    HAL_GPIO_WritePin(LCD_GPIO_PORT, 
        LCD_SCLK_PIN | LCD_MOSI_PIN | LCD_RES_PIN | 
        LCD_DC_PIN | LCD_CS_PIN | LCD_BLK_PIN, 
        GPIO_PIN_SET);
}

/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(u8 dat) 
{	
    u8 i;
    LCD_CS_Clr();
    
    for(i = 0; i < 8; i++)
    {			  
        LCD_SCLK_Clr();
        if(dat & 0x80) {
            LCD_MOSI_Set();
        } else {
            LCD_MOSI_Clr();
        }
        LCD_SCLK_Set();
        dat <<= 1;
    }	
    
    LCD_CS_Set();	
}

/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(u8 dat)
{
    LCD_Writ_Bus(dat);
}

/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(u32 dat)
{
    LCD_Writ_Bus(dat >> 16);
    LCD_Writ_Bus(dat >> 8);
    LCD_Writ_Bus(dat);
}

/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
    LCD_DC_Clr();  // 写命令
    LCD_Writ_Bus(dat);
    LCD_DC_Set();  // 写数据
}

/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2)
{
    LCD_WR_REG(0x2A);  // 列地址设置
    LCD_WR_DATA8(x1 >> 8);
    LCD_WR_DATA8(x1);
    LCD_WR_DATA8(x2 >> 8);
    LCD_WR_DATA8(x2);
    
    LCD_WR_REG(0x2B);  // 行地址设置
    LCD_WR_DATA8(y1 >> 8);
    LCD_WR_DATA8(y1);
    LCD_WR_DATA8(y2 >> 8);
    LCD_WR_DATA8(y2);
    
    LCD_WR_REG(0x2C);  // 储存器写
}

void LCD_Init(void)
{
    LCD_GPIO_Init();  // 初始化GPIO
    
    // 复位序列
    LCD_RES_Clr();    // 复位
    delay_ms(100);
    LCD_RES_Set();
    delay_ms(100);
    
    // 打开背光
    LCD_BLK_Set();
    delay_ms(100);
    
    // ILI9488初始化序列
    LCD_WR_REG(0xE0); 
    LCD_WR_DATA8(0x00); 
    LCD_WR_DATA8(0x07); 
    LCD_WR_DATA8(0x0f); 
    LCD_WR_DATA8(0x0D); 
    LCD_WR_DATA8(0x1B); 
    LCD_WR_DATA8(0x0A); 
    LCD_WR_DATA8(0x3c); 
    LCD_WR_DATA8(0x78); 
    LCD_WR_DATA8(0x4A); 
    LCD_WR_DATA8(0x07); 
    LCD_WR_DATA8(0x0E); 
    LCD_WR_DATA8(0x09); 
    LCD_WR_DATA8(0x1B); 
    LCD_WR_DATA8(0x1e); 
    LCD_WR_DATA8(0x0f);  
    
    LCD_WR_REG(0xE1); 
    LCD_WR_DATA8(0x00); 
    LCD_WR_DATA8(0x22); 
    LCD_WR_DATA8(0x24); 
    LCD_WR_DATA8(0x06); 
    LCD_WR_DATA8(0x12); 
    LCD_WR_DATA8(0x07); 
    LCD_WR_DATA8(0x36); 
    LCD_WR_DATA8(0x47); 
    LCD_WR_DATA8(0x47); 
    LCD_WR_DATA8(0x06); 
    LCD_WR_DATA8(0x0a); 
    LCD_WR_DATA8(0x07); 
    LCD_WR_DATA8(0x30); 
    LCD_WR_DATA8(0x37); 
    LCD_WR_DATA8(0x0f); 
    
    LCD_WR_REG(0xC0); 
    LCD_WR_DATA8(0x10); 
    LCD_WR_DATA8(0x10); 
    
    LCD_WR_REG(0xC1); 
    LCD_WR_DATA8(0x41); 
    
    LCD_WR_REG(0xC5); 
    LCD_WR_DATA8(0x00); 
    LCD_WR_DATA8(0x22); 
    LCD_WR_DATA8(0x80); 
    
    // 设置显示方向
    LCD_WR_REG(0x36);  // Memory Access Control 
    if(USE_HORIZONTAL == 0) {
        LCD_WR_DATA8(0x48);
    } else if(USE_HORIZONTAL == 1) {
        LCD_WR_DATA8(0x88);
    } else if(USE_HORIZONTAL == 2) {
        LCD_WR_DATA8(0x28);
    } else {
        LCD_WR_DATA8(0xE8);
    }
    
    LCD_WR_REG(0x3A);  // Interface Mode Control
    LCD_WR_DATA8(0x66);
        
    LCD_WR_REG(0xB0);  // Interface Mode Control  
    LCD_WR_DATA8(0x00); 
    LCD_WR_REG(0xB1);  // Frame rate 70HZ  
    LCD_WR_DATA8(0xB0); 
    LCD_WR_DATA8(0x11); 
    LCD_WR_REG(0xB4); 
    LCD_WR_DATA8(0x02);   
    LCD_WR_REG(0xB6);  // RGB/MCU Interface Control
    LCD_WR_DATA8(0x02); 
    LCD_WR_DATA8(0x02); 
    
    LCD_WR_REG(0xB7); 
    LCD_WR_DATA8(0xC6); 
    LCD_WR_REG(0xE9); 
    LCD_WR_DATA8(0x00);
    
    LCD_WR_REG(0xF7);    
    LCD_WR_DATA8(0xA9); 
    LCD_WR_DATA8(0x51); 
    LCD_WR_DATA8(0x2C); 
    LCD_WR_DATA8(0x82);
    
    LCD_WR_REG(0x11);  // 退出睡眠模式
    delay_ms(120); 
    LCD_WR_REG(0x29);  // 开启显示
}







