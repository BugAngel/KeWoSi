/**
******************************************************************************
    * @file     Control.c
    * @author   WangRong
    * @version  1.0
    * @date     2017/2/23
    * @brief    Motor Driver
            @arg    TIM4 CH1 TIM1 CH1��������
            @arg    TIM4 CH3 TIM3 CH1�����ҵ��
******************************************************************************
*/

#include "Control.h"
#include "Speaker.h"
#include <string.h>

uint8_t ZuoLunChaoSu[] = {"���̫����"};
uint8_t YouLunChaoSu[] = {"�ұ�̫����"};

/**
  * @brief  ��������
  * @param  speed_value:Ԥ��PWM CCR�Ĵ���ֵ
  * @retval NONE
  */
void LeftMotorSpeed(int8_t speed_value)
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
        TIM1->CCR1 = 0;
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
        TIM1->CCR1 = -speed_value;
    }
}
/**
  * @brief  �ҵ������
  * @param  speed_value:Ԥ��PWM CCR�Ĵ���ֵ
  * @retval NONE
  */
void RightMotorSpeed(int8_t speed_value)
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
        TIM4->CCR3 = speed_value;
        TIM3->CCR1 = 0;
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
        TIM4->CCR3 = 0;
        TIM3->CCR1 = -speed_value;
    }
}

/**
  * @brief  ͣ��
  * @param  NONE
  * @retval NONE
  */
void Stop(void)
{
    LeftMotorSpeed(0);
    RightMotorSpeed(0);
}
/**
  * @brief  ǰ��
  * @param  NONE
  * @retval NONE
  */
void Stright(void)
{
    LeftMotorSpeed(30);
    RightMotorSpeed(30);
}
/**
  * @brief  ����
  * @param  NONE
  * @retval NONE
  */
void Back(void)
{
    LeftMotorSpeed(-30);
    RightMotorSpeed(-30);
}
/**
  * @brief  ��ת
  * @param  NONE
  * @retval NONE
  */
void TurnLeft(void)
{
    LeftMotorSpeed(30);
    RightMotorSpeed(50);
}
/**
  * @brief  ��ת
  * @param  NONE
  * @retval NONE
  */
void TurnRight(void)
{
    LeftMotorSpeed(50);
    RightMotorSpeed(30);
}
/**
  * @brief  ����
  * @param  NONE
  * @retval NONE
  */
void JIASu(void)
{
    LeftMotorSpeed(40);
    RightMotorSpeed(40);
}
/**
  * @brief  ����
  * @param  NONE
  * @retval NONE
  */
void JIANSu(void)
{
    LeftMotorSpeed(25);
    RightMotorSpeed(25);
}
