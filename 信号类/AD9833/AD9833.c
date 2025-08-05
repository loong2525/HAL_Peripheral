#include "ad9833.h"

// 初始化两个AD9833的GPIO
void AD9833_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    // 使能GPIOA和GPIOB时钟（STM32F103C8T6支持）
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    // 配置第一路AD9833引脚（GPIOA6/5/4）
    GPIO_InitStruct.Pin = AD9833A_SDATA_PIN | AD9833A_SCLK_PIN | AD9833A_FSYNC_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(AD9833A_SDATA_PORT, &GPIO_InitStruct);
    
    // 配置第二路AD9833引脚（GPIOB6/5/4）
    GPIO_InitStruct.Pin = AD9833B_SDATA_PIN | AD9833B_SCLK_PIN | AD9833B_FSYNC_PIN;
    HAL_GPIO_Init(AD9833B_SDATA_PORT, &GPIO_InitStruct);
    
    // 初始化引脚为高电平
    AD9833A_SDATA_HIGH;
    AD9833A_SCLK_HIGH;
    AD9833A_FSYNC_HIGH;
    AD9833B_SDATA_HIGH;
    AD9833B_SCLK_HIGH;
    AD9833B_FSYNC_HIGH;
}

// 简单延时（确保SPI时序稳定）
static void AD9833_Delay(void)
{
    volatile uint8_t i;  // volatile防止编译器优化
    for(i = 0; i < 5; i++);
}

// 第一路AD9833写入16位数据（模拟SPI）
void AD9833A_WriteData(uint16_t txdata)
{
    int i;
    AD9833A_FSYNC_LOW;  // 拉低片选，选中芯片
    for(i = 0; i < 16; i++)
    {
        // 发送高位在前
        if(txdata & 0x8000) AD9833A_SDATA_HIGH;
        else AD9833A_SDATA_LOW;
        
        AD9833_Delay();
        AD9833A_SCLK_LOW;  // 时钟下降沿锁存数据
        AD9833_Delay();
        AD9833A_SCLK_HIGH; // 时钟拉高，准备下一位
        txdata <<= 1;      // 处理下一位
    }
    AD9833A_FSYNC_HIGH;  // 拉高片选，结束通信
}

// 第二路AD9833写入16位数据（模拟SPI）
void AD9833B_WriteData(uint16_t txdata)
{
    int i;
    AD9833B_FSYNC_LOW;  // 拉低片选，选中芯片
    for(i = 0; i < 16; i++)
    {
        if(txdata & 0x8000) AD9833B_SDATA_HIGH;
        else AD9833B_SDATA_LOW;
        
        AD9833_Delay();
        AD9833B_SCLK_LOW;
        AD9833_Delay();
        AD9833B_SCLK_HIGH;
        txdata <<= 1;
    }
    AD9833B_FSYNC_HIGH;
}

// 第一路AD9833设置频率（25MHz晶振）
void AD9833A_SetFrequency(unsigned short reg, double fout)
{
    long int freq_hex;
    uint16_t freq_lsb, freq_msb;
    // 频率计算公式：freq_hex = (fout * 2^28) / 25,000,000
    freq_hex = (long int)(fout * 268435456.0 / 25000000.0);
    
    // 拆分32位频率字为两个14位（AD9833频率寄存器为14位）
    freq_lsb = (freq_hex & 0x3FFF) | reg;       // 低14位 + 寄存器地址
    freq_msb = ((freq_hex >> 14) & 0x3FFF) | reg; // 高14位 + 寄存器地址
    
    // 写入频率（B28=1表示32位模式）
    AD9833A_WriteData(AD9833_B28 | AD9833_RESET);
    AD9833A_WriteData(freq_lsb);
    AD9833A_WriteData(freq_msb);
}

// 第二路AD9833设置频率
void AD9833B_SetFrequency(unsigned short reg, double fout)
{
    long int freq_hex;
    uint16_t freq_lsb, freq_msb;
    freq_hex = (long int)(fout * 268435456.0 / 25000000.0);
    freq_lsb = (freq_hex & 0x3FFF) | reg;
    freq_msb = ((freq_hex >> 14) & 0x3FFF) | reg;
    
    AD9833B_WriteData(AD9833_B28 | AD9833_RESET);
    AD9833B_WriteData(freq_lsb);
    AD9833B_WriteData(freq_msb);
}

// 第一路AD9833设置相位（0~4095对应0~360度）
void AD9833A_SetPhase(unsigned short reg, unsigned short val)
{
    val &= 0x0FFF;  // 相位寄存器为12位
    AD9833A_WriteData(reg | val);
}

// 第二路AD9833设置相位
void AD9833B_SetPhase(unsigned short reg, unsigned short val)
{
    val &= 0x0FFF;
    AD9833B_WriteData(reg | val);
}

// 第一路AD9833一站式配置
void AD9833A_Setup(unsigned int Freq_SFR, double Freq, 
                  unsigned int Phase_SFR, unsigned short Phase, unsigned int WaveMode)
{
    uint16_t fsel, psel;
    
    // 复位芯片
    AD9833A_WriteData(AD9833_RESET);
    
    // 设置频率和相位
    AD9833A_SetFrequency(Freq_SFR, Freq);
    AD9833A_SetPhase(Phase_SFR, Phase);
    
    // 选择频率/相位寄存器
    fsel = (Freq_SFR == AD9833_REG_FREQ0) ? AD9833_FSEL0 : AD9833_FSEL1;
    psel = (Phase_SFR == AD9833_REG_PHASE0) ? AD9833_PSEL0 : AD9833_PSEL1;
    
    // 配置波形并清除复位
    AD9833A_WriteData(WaveMode | fsel | psel | AD9833_CLEAR_RESET);
}

// 第二路AD9833一站式配置
void AD9833B_Setup(unsigned int Freq_SFR, double Freq, 
                  unsigned int Phase_SFR, unsigned short Phase, unsigned int WaveMode)
{
    uint16_t fsel, psel;
    
    AD9833B_WriteData(AD9833_RESET);
    AD9833B_SetFrequency(Freq_SFR, Freq);
    AD9833B_SetPhase(Phase_SFR, Phase);
    
    fsel = (Freq_SFR == AD9833_REG_FREQ0) ? AD9833_FSEL0 : AD9833_FSEL1;
    psel = (Phase_SFR == AD9833_REG_PHASE0) ? AD9833_PSEL0 : AD9833_PSEL1;
    
    AD9833B_WriteData(WaveMode | fsel | psel | AD9833_CLEAR_RESET);
}
