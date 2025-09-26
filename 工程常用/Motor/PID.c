/*
 * @Compony: NUC
 * @Date: 2025-09-20 16:59:00
 * @LastEditors: Loong2525
 * @LastEditTime: 2025-09-20 17:36:17
 */
#include "PID.h"

/*
    @discription: 定时调用该方法对某个PID对象进行控制
*/

void PID_handle(
    PID* pid,
    int16_t setvalue)
    {
        pid->setvalue =setvalue;
        pid->currentvalue =getcurrentvalue();
        pid->last_error =pid->current_error;
        pid->current_error = pid->setvalue - pid->currentvalue;
        pid->errorINT += pid->current_error;

        pid->out = pid->Kp * pid->current_error + pid->Ki * pid->errorINT+ pid->Kd * (pid->currentvalue - pid->last_error);
        limit_out(&pid);
    }

/*
    @discription: SET某个PID对象的控制参数
*/
void PID_Set(
    PID* pid,
    uint8_t Kp,
    uint8_t Ki,
    uint8_t Kd)
    {
        pid->Kd=Kd;
        pid->Ki=Ki;
        pid->Kp=Kp;
    }
/*
    @discription: 对PID的out限幅
*/
void limit_out(PID* pid)
{
    if (pid->out > MAXOUT)
    {
        pid->out =MAXOUT;
    }
    if (pid->out < MINOUT)
    {
        pid->out =MINOUT；
    }

}