/**
  ******************************************************************************
  * @file    Blue_Tooth.h
  * @author  Xiaofeige
  * @version V1.0
  * @date    2015.2.15
  * @note    串口蓝牙
  ******************************************************************************
  */

#include "stm32f1xx_hal.h"

#ifndef __BLUE_TOOTH_H
#define __BLUE_TOOTH_H

/*********发送数据类型***********/
#define Send_Speed 10
#define Send_LSpeed 11
#define Send_RSpeed 12
#define Send_MidValue 13   /*中线值*/
#define Send_Pitch 14
#define Send_Accel 15      /*加速度*/
#define Send_Number1 16    /*备用数据  若是浮点数*1000进行发送*/
#define Send_Number2 17
#define Send_Number3 18
#define Send_Number4 19
#define Send_Number5 20
#define Send_Number6 21
#define Send_CPUProcesse 22
#define Send_FreeHeap 23
#define Send_FailNum 24
#define Send_CCDPix1 25
#define Send_CCDPix3 26
/***************接收数据类型***************/
#define Rec_Balance_P 0x20
#define Rec_Balance_I 0x21
#define Rec_Balance_D 0x22
#define Rec_Position_P 0x23
#define Rec_Position_I 0x24
#define Rec_Position_D 0x25
#define Rec_Speed_P 0x26
#define Rec_Speed_I 0x27
#define Rec_Speed_D 0x28
#define Rec_Balance_PIDRange_Max 0x29
#define Rec_Balance_PIDRange_Min 0x2A
#define Rec_Speed_PIDRange_Max 0x2B
#define Rec_Speed_PIDRange_Min 0x2C
#define Rec_Position_PIDRange_Max 0x2D
#define Rec_Position_PIDRange_Min 0x2E
#define Rec_EEPROM_Write 0x2F
#define Rec_EEPROM_Read 0x30
#define Rec_MaxSpeed_E 0x31       /*最大速度上限 编码器形式*/
#define Rec_BSSpeed_E 0x32        /*大弯临界速度 编码器形式*/
#define Rec_SSSpeed_E 0x33        /*小弯临界速度 编码器形式*/
#define Rec_ZSpeed_E 0x34         /*直角临界速度 编码器形式*/
#define Rec_MaxSpeed_R 0x41       /*最大速度上限 实际速度形式*/
#define Rec_BSSpeed_R 0x42        /*大弯临界速度 实际速度形式*/
#define Rec_SSSpeed_R 0x43        /*小弯临界速度 实际速度形式*/
#define Rec_ZSpeed_R 0x44         /*直角临界速度 实际速度形式*/
#define Rec_Go 0x35               /*直立启动 用于调试*/
#define Rec_Break 0x36            /*推倒刹车 用于调试*/
#define Rec_StandUp 0x37          /*直立平衡 用于遥控*/
#define Rec_PushDown 0x38         /*推倒     用于遥控*/
#define Rec_TurnForward 0x39      /*直立前转 用于遥控*/
#define Rec_TurnBack 0x3A         /*直立后转 用于遥控*/
#define Rec_Up 0xE0               /*方向键 上*/
#define Rec_Down 0xE1             /*方向键 下*/
#define Rec_Left 0xE2             /*方向键 左*/
#define Rec_Right 0xE3            /*方向键 右*/
#define Rec_Angle 0xE4            /*设定角度*/
/*********************************************/
typedef enum
{
    CCD1,
    CCD3,
    BothCCD,
} CCD_Type;

extern uint8_t MotorOutputFlag;
extern uint8_t usart1_temp;
extern int BlueToothChexk[4];

void Send_Data(float num, uint8_t NUM_Type);
void Send_CCD(uint8_t * Array1);
void ImproveCar(void);
/*****************************************/


#endif

