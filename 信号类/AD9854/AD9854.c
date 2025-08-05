#include "AD9854.h"
#include "main.h"

// ????
u8 FreqWord[6];  // ?????

// ?????? (20MHz??, 15??)
#define CLK_Set 15
const u32 Freq_mult_ulong = 938250;

// GPIO???
void AD9854_IO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    // ????
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    
    // ??????
    GPIO_InitStruct.Pin = AD9854_RST_PIN | AD9854_UDCLK_PIN | AD9854_WR_PIN | AD9854_RD_PIN | AD9854_OSK_PIN | AD9854_FSK_BPSK_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(AD9854_RST_PORT, &GPIO_InitStruct);

    
    // ?????? (PC0-PC13)
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | 
                          GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | 
                          GPIO_PIN_10 | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(AD9854_DATA_PORT, &GPIO_InitStruct);
    
    // ????
    HAL_GPIO_WritePin(AD9854_RST_PORT, AD9854_RST_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(AD9854_UDCLK_PORT, AD9854_UDCLK_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(AD9854_WR_PORT, AD9854_WR_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(AD9854_RD_PORT, AD9854_RD_PIN, GPIO_PIN_SET);
}

// ?????AD9854
void AD9854_WR_Byte(u32 addr, u32 dat)
{
    u32 dat1 = dat | (addr << 8);  // ???????
    
    // ?????? (PC0-PC13)
    AD9854_DATA_PORT->ODR = (AD9854_DATA_PORT->ODR & 0xC000) | (dat1 & 0x3FFF);
    
    // ????
    HAL_GPIO_WritePin(AD9854_WR_PORT, AD9854_WR_PIN, GPIO_PIN_RESET);
    HAL_Delay(1);  // ?????????
    HAL_GPIO_WritePin(AD9854_WR_PORT, AD9854_WR_PIN, GPIO_PIN_SET);
}

// ??????
void Freq_convert(u32 Freq)
{
    u64 Temp = (u64)Freq * Freq_mult_ulong;
    
    // ???6??
    FreqWord[0] = (u8)(Temp);
    FreqWord[1] = (u8)(Temp >> 8);
    FreqWord[2] = (u8)(Temp >> 16);
    FreqWord[3] = (u8)(Temp >> 24);
    FreqWord[4] = (u8)(Temp >> 32);
    FreqWord[5] = (u8)(Temp >> 40);
}

// ???????
void AD9854_InitSingle(void)
{
    // ????
    HAL_GPIO_WritePin(AD9854_RST_PORT, AD9854_RST_PIN, GPIO_PIN_SET);
    HAL_Delay(10);
    HAL_GPIO_WritePin(AD9854_RST_PORT, AD9854_RST_PIN, GPIO_PIN_RESET);
    HAL_Delay(10);
    
    // ?????
    AD9854_WR_Byte(0x1D, 0x00);  // ?????
    AD9854_WR_Byte(0x1E, CLK_Set);  // ????????
    AD9854_WR_Byte(0x1F, 0x00);   // ????
    AD9854_WR_Byte(0x20, 0x60);   // ?????
    
    // ????
    HAL_GPIO_WritePin(AD9854_UDCLK_PORT, AD9854_UDCLK_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(AD9854_UDCLK_PORT, AD9854_UDCLK_PIN, GPIO_PIN_RESET);
}

// ?????
void AD9854_SetSine(u32 Freq, u16 Shape)
{
    u8 count;
    u8 Address = 0x04;  // ?????????
    
    // ????
    Freq_convert(Freq);
    
    // ???????
    for(count = 6; count > 0; )
    {
        AD9854_WR_Byte(Address++, FreqWord[--count]);
    }
    
    // ????
    AD9854_WR_Byte(0x21, Shape >> 8);      // I?????
    AD9854_WR_Byte(0x22, Shape & 0xFF);    // I?????
    AD9854_WR_Byte(0x23, Shape >> 8);      // Q?????
    AD9854_WR_Byte(0x24, Shape & 0xFF);    // Q?????
    
    // ????
    HAL_GPIO_WritePin(AD9854_UDCLK_PORT, AD9854_UDCLK_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(AD9854_UDCLK_PORT, AD9854_UDCLK_PIN, GPIO_PIN_RESET);
}

// ????
void AD9854_GenerateSquareWave(u32 Freq)
{
    // ???????
    AD9854_WR_Byte(0x1D, 0x00);  // ?????
    AD9854_WR_Byte(0x20, 0x00);  // ???????
    
    // ????
    AD9854_SetSine(Freq, 4095);  // ????
    
    // ????
    HAL_GPIO_WritePin(AD9854_UDCLK_PORT, AD9854_UDCLK_PIN, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(AD9854_UDCLK_PORT, AD9854_UDCLK_PIN, GPIO_PIN_RESET);
}
