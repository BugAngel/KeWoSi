/**
  ******************************************************************************
  * @file    status.c
  * @author  WangRong
  * @version V1.0
  * @date    2016-03-12
  * @brief   Ѱ��С��״̬
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
    PID_SetParam(&PositionPID, 10, 0, 15, 0, 0, 0, 0);  //���PID
    PID_SetParam(&SteerPID, 17, 1, 15, 0, 0, 0, 0);  //���PID
}
/************************************END OF FILE*******************************/
