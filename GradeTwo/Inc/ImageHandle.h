/**
  ******************************************************************************
  * @file    ImageHandle.h
  * @author  WangRong
  * @version V1.0
  * @date    2016/3/31
  * @brief   CCD数据处理
  **@attention
  * 实验平台:红树伟业第五代线型CCD
  ******************************************************************************
  */
#ifndef __IMAGEHANDLE_H
#define __IMAGEHANDLE_H

#include "ccd.h"

uint8_t GetLine(CCD_Info *CCD1_info);
void myCCD_Binarization(CCD_Info *CCD1_info);
void CCD_Filter(CCD_Info *CCD_info);
void myCCD_DataInit(CCD_Info * CCD_info);
void Update_Data(CCD_Info *CCD_info);
void Sideline_Handle(CCD_Info *CCD_info);
void CCD_GetLineError(CCD_Info *CCD_info);
void myCCD_DataHandle(  CCD_Info *CCD1_info );

#endif

