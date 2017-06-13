/**
  ******************************************************************************
  * @file    status.c
  * @author  WangRong
  * @version V1.0
  * @date    2016-03-12
  * @brief   寻光小车状态
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

#include "status.h"

PidTypeDef PositionPID;
PidTypeDef SteerPID;

uint32_t SPEEDBASE=2000;

void PID_init(void)
{
    PID_SetParam(&PositionPID, 10, 0, 15, 0, 0, 0, 0);  //电机PID
    PID_SetParam(&SteerPID, 17, 1, 15, 0, 0, 0, 0);  //舵机PID
}
/************************************END OF FILE*******************************/
