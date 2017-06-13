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
  * @brief  PID����
  * @param  line_pos:��ǰλ����Ϣ
  * @retval NONE
  */
void Pid_Control(uint8_t line_pos)
{
    PID_PositionCalc(&SteerPID, line_pos, 63);
    SteerChange(-SteerPID.U);                           //���ת�����

    PID_PositionCalc(&PositionPID, line_pos, 63);

    MotorSpeedL((int32_t)( SPEEDBASE + PositionPID.U));  //���ת�ٿ���
    MotorSpeedR((int32_t)( SPEEDBASE - PositionPID.U));  //�Ӽ��ŷ������ת��
}



