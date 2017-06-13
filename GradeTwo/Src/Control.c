/**
  ******************************************************************************
  * @file    control.h
  * @author  WangRong
  * @version V1.0
  * @date    2016/1/13
  * @brief   control

  ******************************************************************************
  */
#include "stm32f1xx_hal.h"
#include "pid.h"
#include "Control.h"
#include "Motor.h"
#include "status.h"



/**
  * @brief  PID控制
  * @param  line_pos:当前位置信息
  * @retval NONE
  */
void Pid_Control(uint8_t line_pos)
{
    PID_PositionCalc(&SteerPID, line_pos, 63);
    SteerChange(-SteerPID.U);                           //舵机转向控制

    PID_PositionCalc(&PositionPID, line_pos, 63);

    MotorSpeedL((int32_t)( SPEEDBASE + PositionPID.U));  //电机转速控制
    MotorSpeedR((int32_t)( SPEEDBASE - PositionPID.U));  //加减号方向控制转向
}



