/**
  ******************************************************************************
  * @file    ImageHandle.c
  * @author  WangRong
  * @version V1.0
  * @date    2016/3/31
  * @brief   CCD数据处理
  **@attention
  * 实验平台:红树伟业第五代线型CCD
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
        //前后两次取平均  减小误差
        CCD1_info->Pixel[ii] = (CCD1_info->PixelOri[0][ii] + CCD1_info->PixelOri[1][ii])
                               >> 1;

        //移动CCD原始数据队列
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
飞思卡尔搜白线代码用这个
uint32_t BinaryEdgeValue = 1000;
const uint32_t InvalidPixel_Num = 20;
const uint32_t ROAD_WIDETH_MIN = 0;
uint32_t AD1_MAX;
uint32_t CentralLine_ExposureVoltage;
float AD_MultK_f;
uint32_t AD_MultK;

/**
 * @brief CCD数据滤波,二值化
 * @param   CCD结构体
 * @retval None
 */

void myCCD_Binarization(CCD_Info *CCD1_info)
{
    uint8_t ii = 0;
    uint32_t AD1_MAX = 0;
    uint32_t AD1_MIN = 4095;

    //初步滤波  从十开始保证包括有效点又不太偏靠两边
    for (ii = 0; ii < 128;
         ii++)//60us
    {
        //前后两次取平均  减小误差
        CCD1_info->Pixel[ii] = (CCD1_info->PixelOri[0][ii] + CCD1_info->PixelOri[1][ii])
                               >> 1;

        //移动CCD1原始数据队列
        CCD1_info->PixelOri[1][ii] = CCD1_info->PixelOri[0][ii];


    }

    //用上一次的放大后的原始值来计算放大倍数
    CentralLine_ExposureVoltage =   (   CCD1_info->Pixel[CCD1_info->CentralLine[0]]
                                        + CCD1_info->Pixel[CCD1_info->CentralLine[0] - 1]
                                        + CCD1_info->Pixel[CCD1_info->CentralLine[0] - 2]
                                        + CCD1_info->Pixel[CCD1_info->CentralLine[0] + 1]
                                        + CCD1_info->Pixel[CCD1_info->CentralLine[0] + 2]
                                    ) / 5;

    AD_MultK_f = CCD1_info->CCD_AD_TargetValue / CentralLine_ExposureVoltage;


    //防止放大倍数过小和过大(1400/3096 = 0.45,1400/400 = 3.5)
    if (AD_MultK_f >  3.5)
    {
        AD_MultK_f = 3.5;
    }
    else if (AD_MultK_f < 0.45)
    {
        AD_MultK_f = 0.45;
    }

    //把放大倍数放大为整型数据
    AD_MultK = (uint32_t)(AD_MultK_f * 16);

    //进行CCD1 CCD2 CCD3数据放大
    for (ii = 0; ii < 128; ii++)//80us
    {
        CCD1_info->Pixel[ii] = (CCD1_info->Pixel[ii] >> 4) * AD_MultK; //对CCD1进行放大

        //对CCD1放大后的AD值进行限幅
        if (CCD1_info->Pixel[ii] > 4095)
        {
            CCD1_info->Pixel[ii] = 4095;
        }

        if ((ii >= 16) && (ii <= 112))
        {
            if (AD1_MAX < CCD1_info->Pixel[ii])     //找出CCD1放大后的AD最大值
            {
                AD1_MAX = CCD1_info->Pixel[ii];
            }

            if (AD1_MIN > CCD1_info->Pixel[ii])     //找出CCD1放大后的AD最小值
            {
                AD1_MIN = CCD1_info->Pixel[ii];
            }
        }
    }

    //更新AD_MAX,AD_MIN队列
    CCD1_info->AD_MAX[0] = AD1_MAX;
    CCD1_info->AD_MIN[0] = AD1_MIN;

    //计算CCD1二值化的分界值
    BinaryEdgeValue = (     CCD1_info->AD_MAX[3] + CCD1_info->AD_MAX[2] +
                            CCD1_info->AD_MAX[1] + CCD1_info->AD_MAX[0]
                            + CCD1_info->AD_MIN[3] + CCD1_info->AD_MIN[2] + CCD1_info->AD_MIN[1] +
                            CCD1_info->AD_MIN[0]
                      ) >> 3;

    //限制二值化边界值的最大值最小值(阈值在750左右)
    if (BinaryEdgeValue < CCD1_info->CCD_Binary_MIN)
    {
        BinaryEdgeValue = CCD1_info->CCD_Binary_MIN;
    }
    else if (BinaryEdgeValue > CCD1_info->CCD_Binary_MAX)
    {
        BinaryEdgeValue = CCD1_info->CCD_Binary_MAX;
    }

    //CCD数据的二值化
    for (ii = 0; ii < 128; ii++)
    {
        CCD1_info->PixelBinary[ii] = (CCD1_info->Pixel[ii] >= BinaryEdgeValue) ? 1 :
                                     0;//CCD1数据二值化
    }

}

/**
 * @brief CCD 图像滤波
 * @param   CCD结构体
 * @retval None
 */
void CCD_Filter(CCD_Info *CCD_info)
{
    uint8_t ii = 0;
    uint8_t jj_Left = 0, jj_Right = 0;
    int16_t CCD_Error_Min = 60;

    /*CCD图像找上升沿和下降沿*/
    //if特殊判断第一个点
    if (CCD_info->PixelBinary[InvalidPixel_Num] == 100)
    {
        CCD_info->CCD_Left[jj_Left] = InvalidPixel_Num ;
        jj_Left++;
    }

    //循环判断中间点  三个点同时跳变记为黑线
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
    //if特殊判断最后一点
    if (CCD_info->PixelBinary[127 - InvalidPixel_Num] == 100)
    {
        CCD_info->CCD_Right[jj_Right] = 127 - InvalidPixel_Num;
        jj_Right++;
    }

    /*上升沿与下降沿个数必须相等*/
    if (jj_Right == jj_Left)
    {

        /*CCD图像算左右边与上次中点误差 取最小的作为新一次左右边界*/

        //误差最小记为这次值
        for (ii = 0; ii <= jj_Right; ii++)
        {
            CCD_info->CCD_RWideth[ii] = CCD_info->CCD_Right[ii] -
                                        CCD_info->CentralLine[0]; //右边与上一次误差
            CCD_info->CCD_LWideth[ii] =  CCD_info->CCD_Left[ii] -
                                         CCD_info->CentralLine[0];  //左边与上一次误差
            CCD_info->CCD_Wideth[ii] = CCD_info->CCD_RWideth[ii] +
                                       CCD_info->CCD_LWideth[ii];    //两次误差相加
            if ( ABS(CCD_info->CCD_Wideth[ii]) < ABS(CCD_Error_Min))
            {
                CCD_Error_Min =  ABS(CCD_info->CCD_Wideth[ii]);
                CCD_info->Right_temp = CCD_info->CCD_Right[ii];
                CCD_info->Left_temp = CCD_info->CCD_Left[ii];
            }
        }

        /*限制路宽  不能太短*/
        if (CCD_info->Right_temp - CCD_info->Left_temp < ROAD_WIDETH_MIN)
        {
            CCD_info->Left_temp  = CCD_info->LeftLine[0];
            CCD_info->Right_temp  = CCD_info->RightLine[0];
        }


        /*防止错误出现零*/
        else if ((CCD_info->Left_temp != 0) && (CCD_info->Right_temp != 0))
        {
            CCD_info->LeftLine[0] = CCD_info->Left_temp;
            CCD_info->RightLine[0] = CCD_info->Right_temp;
        }
        else
        {
            CCD_info->Cross_Flag = 1;
        }

        /*CCD所取宽度处置100，别的归零*/
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
 * @brief  CCD 数据初始化
 * @param  CCD结构体
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

    CCD_info->LossLine_Flag = 0;        //丢线标记
    CCD_info->Cross_Flag = 0;           //十字道标记
    CCD_info->BurstNumber = 30;
    CCD_info->CCD_AD_TargetValue = 1400;
    CCD_info->CCD_Binary_MIN = 1000;
    CCD_info->CCD_Binary_MAX = 700;
}
/**
 * @brief 更新
 * @param   CCD结构体
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
 * @brief  CCD丢线标记
 * @param  CCD结构体
 * @retval None
 */
void Sideline_Handle(CCD_Info *CCD_info)
{

    //左边丢线
    if ( CCD_info->Left_temp == InvalidPixel_Num)
    {
        CCD_info->LeftLoseLine_Flag = 1;
        CCD_info->LossLine_Flag = 1;
    }
    //右边丢线
    if (CCD_info->Right_temp == 127 - InvalidPixel_Num)
    {
        CCD_info->RightLoseLine_Flag = 1;
        CCD_info->LossLine_Flag = 1;
    }
    //左右同时丢线就是十字道
    if ((CCD_info->LeftLoseLine_Flag) && (CCD_info->RightLoseLine_Flag))
    {
        CCD_info->Cross_Flag = 1;
        CCD_info->LossLine_Flag = 0;
    }
}

/**
 * @brief CCD搜寻中线,求得偏差
 * @param   CCD结构体
 * @retval None
 */

void CCD_GetLineError(CCD_Info *CCD_info)
{
    /*不丢线计算中点和路宽*/
    if (CCD_info->LossLine_Flag == 0 ) //防止路宽过大
    {
        CCD_info->CentralLine[0] = (CCD_info->LeftLine[0] + CCD_info->RightLine[0])
                                   >> 1;
        CCD_info->RoadWidth[0] = CCD_info->RightLine[0] - CCD_info->LeftLine[0];

    }

    //左边丢线
    else if (CCD_info->LeftLoseLine_Flag == 1)
    {
        CCD_info->CentralLine[0] = CCD_info->RightLine[0] - ((CCD_info->RoadWidth[0]) >>
                                   1);
    }
    //右边丢线
    else if (CCD_info->RightLoseLine_Flag == 1)
    {
        CCD_info->CentralLine[0] = CCD_info->LeftLine[0] + ((CCD_info->RoadWidth[0]) >>
                                   1);
    }

}

/**
 * @brief  CCD数据处理
 * @param  CCD结构体
 * @retval None
 */

void myCCD_DataHandle(  CCD_Info *CCD1_info )
{
    //更新队列
    Update_Data(CCD1_info);

    //数据初步滤波和二值化
    myCCD_Binarization(CCD1_info);

    //赛道滤波
    CCD_Filter(CCD1_info);

    //丢线标记
    Sideline_Handle(CCD1_info);

    //CCD搜边线和偏差计算
    CCD_GetLineError(CCD1_info);

}

#endif


