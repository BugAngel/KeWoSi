/**
  ******************************************************************************
  * @file    ImageHandle.c
  * @author  WangRong
  * @version V1.0
  * @date    2016/3/31
  * @brief   CCD���ݴ���
  **@attention
  * ʵ��ƽ̨:����ΰҵ���������CCD
  ******************************************************************************
  */
#include "status.h"
#include "ccd.h"
#include "ImageHandle.h"

uint8_t GetLine(CCD_Info *CCD1_info)
{
    uint8_t ii = 0;
    uint8_t Line = 63;
    uint16_t  Value = 4096;
    for (ii = 0; ii < 128;
         ii++)
    {
        //ǰ������ȡƽ��  ��С���
        CCD1_info->Pixel[ii] = (CCD1_info->PixelOri[0][ii] + CCD1_info->PixelOri[1][ii])
                               >> 1;

        //�ƶ�CCDԭʼ���ݶ���
        CCD1_info->PixelOri[1][ii] = CCD1_info->PixelOri[0][ii];


    }
    for (ii = 40; ii < 87;
         ii++)
    {
        if (CCD1_info->Pixel[ii] < Value)
        {
            Value = CCD1_info->Pixel[ii];
            Line = ii;
        }


    }
    return Line;
}

#if 0
��˼�����Ѱ��ߴ��������
uint32_t BinaryEdgeValue = 1000;
const uint32_t InvalidPixel_Num = 20;
const uint32_t ROAD_WIDETH_MIN = 0;
uint32_t AD1_MAX;
uint32_t CentralLine_ExposureVoltage;
float AD_MultK_f;
uint32_t AD_MultK;

/**
 * @brief CCD�����˲�,��ֵ��
 * @param   CCD�ṹ��
 * @retval None
 */

void myCCD_Binarization(CCD_Info *CCD1_info)
{
    uint8_t ii = 0;
    uint32_t AD1_MAX = 0;
    uint32_t AD1_MIN = 4095;

    //�����˲�  ��ʮ��ʼ��֤������Ч���ֲ�̫ƫ������
    for (ii = 0; ii < 128;
         ii++)//60us
    {
        //ǰ������ȡƽ��  ��С���
        CCD1_info->Pixel[ii] = (CCD1_info->PixelOri[0][ii] + CCD1_info->PixelOri[1][ii])
                               >> 1;

        //�ƶ�CCD1ԭʼ���ݶ���
        CCD1_info->PixelOri[1][ii] = CCD1_info->PixelOri[0][ii];


    }

    //����һ�εķŴ���ԭʼֵ������Ŵ���
    CentralLine_ExposureVoltage =   (   CCD1_info->Pixel[CCD1_info->CentralLine[0]]
                                        + CCD1_info->Pixel[CCD1_info->CentralLine[0] - 1]
                                        + CCD1_info->Pixel[CCD1_info->CentralLine[0] - 2]
                                        + CCD1_info->Pixel[CCD1_info->CentralLine[0] + 1]
                                        + CCD1_info->Pixel[CCD1_info->CentralLine[0] + 2]
                                    ) / 5;

    AD_MultK_f = CCD1_info->CCD_AD_TargetValue / CentralLine_ExposureVoltage;


    //��ֹ�Ŵ�����С�͹���(1400/3096 = 0.45,1400/400 = 3.5)
    if (AD_MultK_f >  3.5)
    {
        AD_MultK_f = 3.5;
    }
    else if (AD_MultK_f < 0.45)
    {
        AD_MultK_f = 0.45;
    }

    //�ѷŴ����Ŵ�Ϊ��������
    AD_MultK = (uint32_t)(AD_MultK_f * 16);

    //����CCD1 CCD2 CCD3���ݷŴ�
    for (ii = 0; ii < 128; ii++)//80us
    {
        CCD1_info->Pixel[ii] = (CCD1_info->Pixel[ii] >> 4) * AD_MultK; //��CCD1���зŴ�

        //��CCD1�Ŵ���ADֵ�����޷�
        if (CCD1_info->Pixel[ii] > 4095)
        {
            CCD1_info->Pixel[ii] = 4095;
        }

        if ((ii >= 16) && (ii <= 112))
        {
            if (AD1_MAX < CCD1_info->Pixel[ii])     //�ҳ�CCD1�Ŵ���AD���ֵ
            {
                AD1_MAX = CCD1_info->Pixel[ii];
            }

            if (AD1_MIN > CCD1_info->Pixel[ii])     //�ҳ�CCD1�Ŵ���AD��Сֵ
            {
                AD1_MIN = CCD1_info->Pixel[ii];
            }
        }
    }

    //����AD_MAX,AD_MIN����
    CCD1_info->AD_MAX[0] = AD1_MAX;
    CCD1_info->AD_MIN[0] = AD1_MIN;

    //����CCD1��ֵ���ķֽ�ֵ
    BinaryEdgeValue = (     CCD1_info->AD_MAX[3] + CCD1_info->AD_MAX[2] +
                            CCD1_info->AD_MAX[1] + CCD1_info->AD_MAX[0]
                            + CCD1_info->AD_MIN[3] + CCD1_info->AD_MIN[2] + CCD1_info->AD_MIN[1] +
                            CCD1_info->AD_MIN[0]
                      ) >> 3;

    //���ƶ�ֵ���߽�ֵ�����ֵ��Сֵ(��ֵ��750����)
    if (BinaryEdgeValue < CCD1_info->CCD_Binary_MIN)
    {
        BinaryEdgeValue = CCD1_info->CCD_Binary_MIN;
    }
    else if (BinaryEdgeValue > CCD1_info->CCD_Binary_MAX)
    {
        BinaryEdgeValue = CCD1_info->CCD_Binary_MAX;
    }

    //CCD���ݵĶ�ֵ��
    for (ii = 0; ii < 128; ii++)
    {
        CCD1_info->PixelBinary[ii] = (CCD1_info->Pixel[ii] >= BinaryEdgeValue) ? 1 :
                                     0;//CCD1���ݶ�ֵ��
    }

}

/**
 * @brief CCD ͼ���˲�
 * @param   CCD�ṹ��
 * @retval None
 */
void CCD_Filter(CCD_Info *CCD_info)
{
    uint8_t ii = 0;
    uint8_t jj_Left = 0, jj_Right = 0;
    int16_t CCD_Error_Min = 60;

    /*CCDͼ���������غ��½���*/
    //if�����жϵ�һ����
    if (CCD_info->PixelBinary[InvalidPixel_Num] == 100)
    {
        CCD_info->CCD_Left[jj_Left] = InvalidPixel_Num ;
        jj_Left++;
    }

    //ѭ���ж��м��  ������ͬʱ�����Ϊ����
    for (ii = InvalidPixel_Num + 1;
         ii < 127 - InvalidPixel_Num; ii++)
    {
        if ((CCD_info->PixelBinary[ii] == 100)
            && (CCD_info->PixelBinary[ii - 1] == 0))
        {
            if ((CCD_info->PixelBinary[ii - 2] == 0)
                && (CCD_info->PixelBinary[ii - 3] == 0))
            {
                CCD_info->CCD_Left[jj_Left] = ii;
                jj_Left++;
            }
        }
        if ((CCD_info->PixelBinary[ii] == 100)
            && (CCD_info->PixelBinary[ii + 1] == 0))
        {
            if ((CCD_info->PixelBinary[ii + 2] == 0)
                && (CCD_info->PixelBinary[ii + 3] == 0))
            {
                CCD_info->CCD_Right[jj_Right] = ii;
                jj_Right++;
            }
        }
    }
    //if�����ж����һ��
    if (CCD_info->PixelBinary[127 - InvalidPixel_Num] == 100)
    {
        CCD_info->CCD_Right[jj_Right] = 127 - InvalidPixel_Num;
        jj_Right++;
    }

    /*���������½��ظ����������*/
    if (jj_Right == jj_Left)
    {

        /*CCDͼ�������ұ����ϴ��е���� ȡ��С����Ϊ��һ�����ұ߽�*/

        //�����С��Ϊ���ֵ
        for (ii = 0; ii <= jj_Right; ii++)
        {
            CCD_info->CCD_RWideth[ii] = CCD_info->CCD_Right[ii] -
                                        CCD_info->CentralLine[0]; //�ұ�����һ�����
            CCD_info->CCD_LWideth[ii] =  CCD_info->CCD_Left[ii] -
                                         CCD_info->CentralLine[0];  //�������һ�����
            CCD_info->CCD_Wideth[ii] = CCD_info->CCD_RWideth[ii] +
                                       CCD_info->CCD_LWideth[ii];    //����������
            if ( ABS(CCD_info->CCD_Wideth[ii]) < ABS(CCD_Error_Min))
            {
                CCD_Error_Min =  ABS(CCD_info->CCD_Wideth[ii]);
                CCD_info->Right_temp = CCD_info->CCD_Right[ii];
                CCD_info->Left_temp = CCD_info->CCD_Left[ii];
            }
        }

        /*����·��  ����̫��*/
        if (CCD_info->Right_temp - CCD_info->Left_temp < ROAD_WIDETH_MIN)
        {
            CCD_info->Left_temp  = CCD_info->LeftLine[0];
            CCD_info->Right_temp  = CCD_info->RightLine[0];
        }


        /*��ֹ���������*/
        else if ((CCD_info->Left_temp != 0) && (CCD_info->Right_temp != 0))
        {
            CCD_info->LeftLine[0] = CCD_info->Left_temp;
            CCD_info->RightLine[0] = CCD_info->Right_temp;
        }
        else
        {
            CCD_info->Cross_Flag = 1;
        }

        /*CCD��ȡ��ȴ���100����Ĺ���*/
        for (ii = 0; ii <= 127; ii++)
        {
            if ((ii >= CCD_info->LeftLine[0]) && (ii <= CCD_info->RightLine[0]))
            {
                CCD_info->Pixel_2[ii] = 100;
            }
            else
            {
                CCD_info->Pixel_2[ii] = 0;
            }
        }

    }
    else
    {
        CCD_info->Cross_Flag = 1;
    }
}


/**
 * @brief  CCD ���ݳ�ʼ��
 * @param  CCD�ṹ��
 * @retval None
 */

void myCCD_DataInit(CCD_Info * CCD_info)
{
    uint8_t ii = 0, jj = 0;

    for (ii = 0; ii < 2; ii++)
    {
        for (jj = 0; jj < 20; jj++)
        {
            CCD_info->PixelOri[ii][jj] = 0;
            CCD_info->PixelOri[ii][127 - jj] = 0;
        }

        for (jj = 20; jj < 107; jj++)
        {
            CCD_info->PixelOri[ii][jj] = 0;
        }
    }

    for (ii = 0; ii < 128; ii++)
    {
        CCD_info->Pixel[ii] = 0;
        CCD_info->PixelBinary[ii] = 0;
        CCD_info->Pixel_2[ii] = 0;
    }

    for (ii = 0; ii < 5; ii++)
    {
        CCD_info->LeftLine[ii] = 0;
        CCD_info->RightLine[ii] = 0;
        CCD_info->CentralLine[ii] = 63;
        CCD_info->LineError[ii] = 0;
    }

    CCD_info->LeftLoseLine_Flag = 0;
    CCD_info->RightLoseLine_Flag = 0;

    for (ii = 0; ii < 10; ii++)
    {
        CCD_info->RoadWidth[ii] = 50;
    }

    for (ii = 0; ii < 4; ii++)
    {
        CCD_info->AD_MAX[ii] = 1200;
        CCD_info->AD_MIN[ii] = 0;
    }

    CCD_info->RoadWidthOfStraight = 70;

    CCD_info->LeftLine[0] = 28;
    CCD_info->RightLine[0] = 100;

    CCD_info->LossLine_Flag = 0;        //���߱��
    CCD_info->Cross_Flag = 0;           //ʮ�ֵ����
    CCD_info->BurstNumber = 30;
    CCD_info->CCD_AD_TargetValue = 1400;
    CCD_info->CCD_Binary_MIN = 1000;
    CCD_info->CCD_Binary_MAX = 700;
}
/**
 * @brief ����
 * @param   CCD�ṹ��
 * @retval None
 */
void Update_Data(CCD_Info *CCD_info)
{
    uint8_t ii;

    CCD_info->Cross_Flag = 0;
    CCD_info->LeftLoseLine_Flag = 0;
    CCD_info->RightLoseLine_Flag = 0;
    CCD_info->LossLine_Flag = 0;

    for (ii = 5 - 1; ii > 0; ii--)
    {
        CCD_info->LeftLine[ii]    = CCD_info->LeftLine[ii - 1];
        CCD_info->RightLine[ii]   = CCD_info->RightLine[ii - 1];
        CCD_info->CentralLine[ii] = CCD_info->CentralLine[ii - 1];
        CCD_info->LineError[ii]   = CCD_info->LineError[ii - 1];
        CCD_info->RoadWidth[ii] = CCD_info->RoadWidth[ii - 1];
        CCD_info->AD_MAX[ii] = CCD_info->AD_MAX[ii - 1];
        CCD_info->AD_MIN[ii] = CCD_info->AD_MIN[ii - 1];
    }

    for (ii = 0; ii < 10; ii++)
    {
        CCD_info->CCD_LWideth[ii] = 0;
        CCD_info->CCD_RWideth[ii] = 0;
        CCD_info->CCD_Left[ii] = 0;
        CCD_info->CCD_Right[ii] = 0;
    }

}
/**
 * @brief  CCD���߱��
 * @param  CCD�ṹ��
 * @retval None
 */
void Sideline_Handle(CCD_Info *CCD_info)
{

    //��߶���
    if ( CCD_info->Left_temp == InvalidPixel_Num)
    {
        CCD_info->LeftLoseLine_Flag = 1;
        CCD_info->LossLine_Flag = 1;
    }
    //�ұ߶���
    if (CCD_info->Right_temp == 127 - InvalidPixel_Num)
    {
        CCD_info->RightLoseLine_Flag = 1;
        CCD_info->LossLine_Flag = 1;
    }
    //����ͬʱ���߾���ʮ�ֵ�
    if ((CCD_info->LeftLoseLine_Flag) && (CCD_info->RightLoseLine_Flag))
    {
        CCD_info->Cross_Flag = 1;
        CCD_info->LossLine_Flag = 0;
    }
}

/**
 * @brief CCD��Ѱ����,���ƫ��
 * @param   CCD�ṹ��
 * @retval None
 */

void CCD_GetLineError(CCD_Info *CCD_info)
{
    /*�����߼����е��·��*/
    if (CCD_info->LossLine_Flag == 0 ) //��ֹ·�����
    {
        CCD_info->CentralLine[0] = (CCD_info->LeftLine[0] + CCD_info->RightLine[0])
                                   >> 1;
        CCD_info->RoadWidth[0] = CCD_info->RightLine[0] - CCD_info->LeftLine[0];

    }

    //��߶���
    else if (CCD_info->LeftLoseLine_Flag == 1)
    {
        CCD_info->CentralLine[0] = CCD_info->RightLine[0] - ((CCD_info->RoadWidth[0]) >>
                                   1);
    }
    //�ұ߶���
    else if (CCD_info->RightLoseLine_Flag == 1)
    {
        CCD_info->CentralLine[0] = CCD_info->LeftLine[0] + ((CCD_info->RoadWidth[0]) >>
                                   1);
    }

}

/**
 * @brief  CCD���ݴ���
 * @param  CCD�ṹ��
 * @retval None
 */

void myCCD_DataHandle(  CCD_Info *CCD1_info )
{
    //���¶���
    Update_Data(CCD1_info);

    //���ݳ����˲��Ͷ�ֵ��
    myCCD_Binarization(CCD1_info);

    //�����˲�
    CCD_Filter(CCD1_info);

    //���߱��
    Sideline_Handle(CCD1_info);

    //CCD�ѱ��ߺ�ƫ�����
    CCD_GetLineError(CCD1_info);

}

#endif


