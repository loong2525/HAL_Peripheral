/*
 * @Compony: NUC
 * @Date: 2025-09-20 16:59:00
 * @LastEditors: Loong2525
 * @LastEditTime: 2025-09-20 17:38:51
 */
#ifndef __PID_H
#define __PID_H


#define MAXOUT 500
#define MINOUT 0

#include"stdint.h" 
#include"Encoder.h"

entern int16_t getcurrentvalue();//main自定义函数，STM32HAL关联__HAL_TIM_GET_COUNTER方法



//位置式PID
typedef struct{
    int16_t setvalue;
    int16_t currentvalue;
    int16_t current_error;
    int16_t last_error;
    int16_t errorINT；
    float Kp;
    float Ki;
    float Kd;
    int16_t out;
}PID;

static void PID_handle(
    PID* pid,
    int16_t setvalue);//调用pid控制句柄

static void PID_Set(
    PID* pid,
    uint8_t Kp,
    uint8_t Ki,
    uint8_t Kd);
void limit_out(PID* pid);//限幅out



#endif