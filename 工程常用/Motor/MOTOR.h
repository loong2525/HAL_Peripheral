/*
 * @Compony: NUC
 * @Date: 2025-09-20 16:59:31
 * @LastEditors: Loong2525
 * @LastEditTime: 2025-09-20 20:53:39
 * @description: 使用该库创建Motor对象（和PID对象关联）
 */

#ifndef __ENCODER_H
#define __ENCODER_H
#include"stdint.h"
#include"PID.h"

typedef struct{
    GPIO_TypeDef GPIO_in1;
    uint32_t GPIOPIN_in1;
    GPIO_TypeDef GPIO_in2;
    uint32_t GPIOPIN_in2;
    GPIO_TypeDef GPIO_pwm;
    uint32_t GPIOPIN_pwm;
    TIM_HandleTypeDef* htim;
    PID motorpid;
}MOTOR;

void MOTOR_Init(MOTOR*motor);
void MOTOR_Setaction(MOTOR*motor,bool i);








#endif

