/*
******************************************************************************
    * @file     Motor.h
    * @author   Johnny Sun
    * @version  1.0
    * @date     2014/10/22
    * @brief    Motor Driver
******************************************************************************
*/


#ifndef __Motor_H
#define __Motor_H
#include "stm32f1xx_hal.h"

#define MOTOR_SPEED_MAX     8000
#define MOTOR_SPEED_MIN     0

#define STEER_MIN  -250
#define STEER_MAX  250
#define STEER_Middle  1499

void MotorSpeedL(int32_t speed);
void MotorSpeedR(int32_t speed);
void SteerChange(int32_t position_value);



#endif  //__Motor_H

/* End of "Motor.h" */
