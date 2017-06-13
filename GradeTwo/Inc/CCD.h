/**
  ******************************************************************************
  * @file    CCD.h
  * @author  WangRong
  * @version V1.0
  * @date    2016/3/31
  * @brief   CCD�ײ�����
  **@attention
  * ʵ��ƽ̨:����ΰҵ���������CCD
  ******************************************************************************
  */

#ifndef __CCD_H
#define __CCD_H

#include "status.h"

#define SI1_SetVal()   HAL_GPIO_WritePin(SI_GPIO_Port,SI_Pin, GPIO_PIN_SET)
#define SI1_ClrVal()   HAL_GPIO_WritePin(SI_GPIO_Port,SI_Pin, GPIO_PIN_RESET)
#define CLK1_SetVal()  HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin, GPIO_PIN_SET)
#define CLK1_ClrVal()  HAL_GPIO_WritePin(CLK_GPIO_Port,CLK_Pin, GPIO_PIN_RESET)

typedef struct CCD_Info_//--------------------------------CCD����
{
    uint16_t PixelOri[2][128];          // CCDԭʼֵ
    uint16_t Pixel[128];                // CCD�˲���ֵ
    uint8_t PixelBinary[128];          // CCD��ֵ��ֵ

		uint16_t AD_MAX[4];					//AD���ֵ
	uint16_t AD_MIN[4];					//AD��Сֵ
	
    uint8_t Pixel_2[128];              //CCDͼ��ڶ����˲�ֵ
    int16_t CCD_LWideth[10];
    int16_t CCD_RWideth[10];           //�߽����ϴ��е����
    int16_t CCD_Wideth[10];	
    uint16_t CCD_Left[10];           //CCDɨ�������������
    uint16_t CCD_Right[10];          //CCDɨ�������ұ�����
    uint16_t Right_temp;                //CCD�ұ�����ʱֵ
    uint16_t Left_temp;                 //CCD�������ʱֵ

    int16_t  LeftLine[5];       //��߽����
    int16_t  CentralLine[5];    //���߶���
    int16_t  RightLine[5];      //�ұ߽����
    int16_t  LineError[5];      //ƫ�����
    int16_t  RoadWidth[5];      //·�����

    uint8_t LeftLoseLine_Flag;
    uint8_t RightLoseLine_Flag;
    uint8_t LossLine_Flag;
    int16_t  RoadWidthOfStraight;       //ֱ����·��
  
    uint8_t Cross_Flag;                 //ʮ�ֵ���־
    uint8_t  BurstNumber;
	float CCD_AD_TargetValue;			//CCD��ѹ�Ŵ��Ŀ��ֵ
	uint16_t CCD_Binary_MIN;
	uint16_t CCD_Binary_MAX;
} CCD_Info;

void CCD_Init(void);
void CCD_ImageCapture(CCD_Info *CCD1_info);
#endif
