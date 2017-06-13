/**
******************************************************************************
    * @file     Control.c
    * @author   WangRong
    * @version  1.0
    * @date     2017/2/23
    * @brief    Motor Driver
            @arg    TIM4 CH1 TIM1 CH1控制左电机
            @arg    TIM4 CH3 TIM3 CH1控制右电机
******************************************************************************
*/

#include "Control.h"
#include "Speaker.h"
#include <string.h>

uint8_t ZuoLunChaoSu[] = {"左边太快了"};
uint8_t YouLunChaoSu[] = {"右边太快了"};

/**
  * @brief  左电机控制
  * @param  speed_value:预期PWM CCR寄存器值
  * @retval NONE
  */
void LeftMotorSpeed(int8_t speed_value)
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
        TIM1->CCR1 = 0;
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
        TIM1->CCR1 = -speed_value;
    }
}
/**
  * @brief  右电机控制
  * @param  speed_value:预期PWM CCR寄存器值
  * @retval NONE
  */
void RightMotorSpeed(int8_t speed_value)
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
        TIM4->CCR3 = speed_value;
        TIM3->CCR1 = 0;
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
        TIM4->CCR3 = 0;
        TIM3->CCR1 = -speed_value;
    }
}

/**
  * @brief  停车
  * @param  NONE
  * @retval NONE
  */
void Stop(void)
{
    LeftMotorSpeed(0);
    RightMotorSpeed(0);
}
/**
  * @brief  前进
  * @param  NONE
  * @retval NONE
  */
void Stright(void)
{
    LeftMotorSpeed(30);
    RightMotorSpeed(30);
}
/**
  * @brief  后退
  * @param  NONE
  * @retval NONE
  */
void Back(void)
{
    LeftMotorSpeed(-30);
    RightMotorSpeed(-30);
}
/**
  * @brief  左转
  * @param  NONE
  * @retval NONE
  */
void TurnLeft(void)
{
    LeftMotorSpeed(30);
    RightMotorSpeed(50);
}
/**
  * @brief  右转
  * @param  NONE
  * @retval NONE
  */
void TurnRight(void)
{
    LeftMotorSpeed(50);
    RightMotorSpeed(30);
}
/**
  * @brief  加速
  * @param  NONE
  * @retval NONE
  */
void JIASu(void)
{
    LeftMotorSpeed(40);
    RightMotorSpeed(40);
}
/**
  * @brief  减速
  * @param  NONE
  * @retval NONE
  */
void JIANSu(void)
{
    LeftMotorSpeed(25);
    RightMotorSpeed(25);
}
