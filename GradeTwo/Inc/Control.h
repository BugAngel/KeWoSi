/**
  ******************************************************************************
  * @file    control.h
  * @author  WangRong
  * @version V3.3
  * @date    2016/1/13
  * @brief   pid
  ******************************************************************************
  */


#ifndef _Control_H_
#define _Control_H_

#include "stm32f1xx_hal.h"

void Pid_Control(uint8_t line_pos);

#endif  /* _Control_H_ */

