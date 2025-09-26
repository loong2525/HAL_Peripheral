/*
 * @Compony: NUC
 * @Date: 2025-09-20 16:59:00
 * @LastEditors: Loong2525
 * @LastEditTime: 2025-09-20 20:48:03
 */
#include "MOTOR.h"


void MOTOR_Init(MOTOR*motor)
{
    HAL_GPIO_WritePin(motor->GPIO_in1,motor->GPIOPIN_in1, RESET);
    HAL_GPIO_WritePin(motor->GPIO_in2,motor->GPIOPIN_in2, RESET);
    __HAL_TIM_SetCompare(motor->htim, TIM_CHANNEL_1,motor->pwm);
    
}
void MOTOR_Setaction(MOTOR*motor,bool i)
{
    if i
    {
        HAL_GPIO_WritePin(motor->GPIO_in1,motor->GPIOPIN_in1, SET);
        HAL_GPIO_WritePin(motor->GPIO_in2,motor->GPIOPIN_in2, RESET);
        __HAL_TIM_SetCompare(motor->htim, TIM_CHANNEL_1,motor->pwm);
    }
    else
    {
        HAL_GPIO_WritePin(motor->GPIO_in1,motor->GPIOPIN_in1, RESET);
        HAL_GPIO_WritePin(motor->GPIO_in2,motor->GPIOPIN_in2, SET);
        __HAL_TIM_SetCompare(motor->htim, TIM_CHANNEL_1,motor->pwm);
    }
}