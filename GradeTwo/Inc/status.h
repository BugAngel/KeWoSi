/**
  ******************************************************************************
  * @file    status.c
  * @author  WangRong
  * @version V1.0
  * @date    2016-03-12
  * @brief   Ñ°¹âÐ¡³µ×´Ì¬
  ******************************************************************************
  * @attention
  ******************************************************************************
  */


#ifndef __STATUS_H
#define __STATUS_H

#include "stm32f1xx_hal.h"
#include "pid.h"


#if !defined(ABS)
#define ABS(a)         (((a) < 0) ? (-(a)) : (a))
#endif

extern PidTypeDef PositionPID, SteerPID;

extern uint32_t SPEEDBASE ;

void PID_init(void);

#endif
/************************************END OF FILE*******************************/
