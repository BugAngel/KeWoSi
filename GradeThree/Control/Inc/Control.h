/**
******************************************************************************
    * @file     Control.c
    * @author   WangRong
    * @version  1.0
    * @date     2017/2/23
    * @brief    Motor Driver
            @arg    TIM4 CH1 2控制左电机
            @arg    TIM4 CH3 4控制右电机
******************************************************************************
*/

#ifndef __CONTROL_H
#define __CONTROL_H

#include "stm32f1xx_hal.h"

#define MOTOR_SPEED_MAX 99
#define MOTOR_SPEED_MIN 0

void LeftMotorSpeed(int8_t speed_value);
void RightMotorSpeed(int8_t speed_value);
void Stop(void);
void Stright(void);
void Back(void);
void TurnLeft(void);
void TurnRight(void);
void JIASu(void);
void JIANSu(void);
#endif
