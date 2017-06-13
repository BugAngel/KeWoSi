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
  * @brief  �ҵ������
  * @param  speed_value:Ԥ���ٶ�
  * @retval NONE
  */
void MotorSpeedR(int32_t speed_value)
{

    if (speed_value > 0)     //��ת
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
    else                       //��ת
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
  * @brief  ��������
  * @param  speed_value:Ԥ���ٶ�
  * @retval NONE
  */
void MotorSpeedL(int32_t speed_value)
{
    if (speed_value > 0)  //��ת
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
    else  // ��ת
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
  * @brief  �������.
  * @param  position_value:λ�øı���
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


