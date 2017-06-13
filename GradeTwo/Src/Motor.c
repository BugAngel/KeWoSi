/**
******************************************************************************
    * @file     Motor.c
    * @author   Johnny Sun
    * @version  1.0
    * @date     2014/10/22
    * @brief    Motor Driver
      WangRong modify it to stm32 in 2016/3/11
******************************************************************************
*/

#include "Motor.h"

/**
  * @brief  右电机控制
  * @param  speed_value:预期速度
  * @retval NONE
  */
void MotorSpeedR(int32_t speed_value)
{

    if (speed_value > 0)     //正转
    {
        if (speed_value > MOTOR_SPEED_MAX)
        {
            speed_value = MOTOR_SPEED_MAX;
        }
        if (speed_value < MOTOR_SPEED_MIN)
        {
            speed_value = MOTOR_SPEED_MIN;
        }
        TIM4->CCR1 = speed_value;
        TIM4->CCR2 = 0;
    }
    else                       //反转
    {
        if (speed_value < -MOTOR_SPEED_MAX)
        {
            speed_value = -MOTOR_SPEED_MAX;
        }
        if (speed_value > -MOTOR_SPEED_MIN)
        {
            speed_value = -MOTOR_SPEED_MIN;
        }
        TIM4->CCR1 = 0;
        TIM4->CCR2 = -speed_value;
    }
}
/**
  * @brief  左电机控制
  * @param  speed_value:预期速度
  * @retval NONE
  */
void MotorSpeedL(int32_t speed_value)
{
    if (speed_value > 0)  //正转
    {
        if (speed_value > MOTOR_SPEED_MAX)
        {
            speed_value = MOTOR_SPEED_MAX;
        }
        else if (speed_value < MOTOR_SPEED_MIN)
        {
            speed_value = MOTOR_SPEED_MIN;
        }
        TIM4->CCR3 = speed_value;
        TIM4->CCR4 = 0;
    }
    else  // 倒转
    {
        if (speed_value < -MOTOR_SPEED_MAX)
        {
            speed_value = -MOTOR_SPEED_MAX;
        }
        else if (speed_value > -MOTOR_SPEED_MIN)
        {
            speed_value = -MOTOR_SPEED_MIN;
        }
        TIM4->CCR3 = 0;
        TIM4->CCR4 = -speed_value;
    }
}


/**
  * @brief  舵机控制.
  * @param  position_value:位置改变量
  * @retval NONE
  */
void SteerChange(int32_t position_value)
{

    if (position_value > STEER_MAX)
    {
        position_value = STEER_MAX;
    }
    else if (position_value < STEER_MIN)
    {
        position_value = STEER_MIN;
    }

    TIM5->CCR2 = position_value + STEER_Middle;
}


