/**
  ******************************************************************************
  * @file    Blue_Tooth.h
  * @author  Xiaofeige
  * @version V1.0
  * @date    2015.2.15
  * @note    ��������
  ******************************************************************************
  */

#include "stm32f1xx_hal.h"

#ifndef __BLUE_TOOTH_H
#define __BLUE_TOOTH_H

/*********������������***********/
#define Send_Speed 10
#define Send_LSpeed 11
#define Send_RSpeed 12
#define Send_MidValue 13   /*����ֵ*/
#define Send_Pitch 14
#define Send_Accel 15      /*���ٶ�*/
#define Send_Number1 16    /*��������  ���Ǹ�����*1000���з���*/
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
/***************������������***************/
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
#define Rec_MaxSpeed_E 0x31       /*����ٶ����� ��������ʽ*/
#define Rec_BSSpeed_E 0x32        /*�����ٽ��ٶ� ��������ʽ*/
#define Rec_SSSpeed_E 0x33        /*С���ٽ��ٶ� ��������ʽ*/
#define Rec_ZSpeed_E 0x34         /*ֱ���ٽ��ٶ� ��������ʽ*/
#define Rec_MaxSpeed_R 0x41       /*����ٶ����� ʵ���ٶ���ʽ*/
#define Rec_BSSpeed_R 0x42        /*�����ٽ��ٶ� ʵ���ٶ���ʽ*/
#define Rec_SSSpeed_R 0x43        /*С���ٽ��ٶ� ʵ���ٶ���ʽ*/
#define Rec_ZSpeed_R 0x44         /*ֱ���ٽ��ٶ� ʵ���ٶ���ʽ*/
#define Rec_Go 0x35               /*ֱ������ ���ڵ���*/
#define Rec_Break 0x36            /*�Ƶ�ɲ�� ���ڵ���*/
#define Rec_StandUp 0x37          /*ֱ��ƽ�� ����ң��*/
#define Rec_PushDown 0x38         /*�Ƶ�     ����ң��*/
#define Rec_TurnForward 0x39      /*ֱ��ǰת ����ң��*/
#define Rec_TurnBack 0x3A         /*ֱ����ת ����ң��*/
#define Rec_Up 0xE0               /*����� ��*/
#define Rec_Down 0xE1             /*����� ��*/
#define Rec_Left 0xE2             /*����� ��*/
#define Rec_Right 0xE3            /*����� ��*/
#define Rec_Angle 0xE4            /*�趨�Ƕ�*/
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

