/**
  ******************************************************************************
  * @file    Blue_Tooth.c
  * @author  Afei
  * @version V1.0
  * @date    2015.2.15
  * @note    串口蓝牙
    @brief   WangRong modify it to stm32 in 2016/3/11
  ******************************************************************************
  */
#include "pid.h"
#include "Blue_Tooth.h"
#include "Motor.h"
#include "status.h"

extern UART_HandleTypeDef huart1;

uint8_t SEND_BUF[9] = {0xc0, 0xfb, 0xe2, 0, 0, 0, 0, 0, 0xdd};   //用于发送浮点数
uint8_t USART[9];

uint8_t MotorOutputFlag = 0;
int BlueToothChexk[4] = {0, 0, 0, 0};

extern float setspeed;

float ii;
 uint8_t usart1_temp;
/**
  * @brief  数据发送
  * @param  浮点数  整形数 Num是实际数据；Num_Type是数据类型
  * @retval None
  */
void Send_Data(float num, uint8_t NUM_Type)
{
    int32_t Num;
    Num = num * 1000;
    if (Num < 0)
    {
        Num = 0 - Num;
        SEND_BUF[3] = 0x00;
    }
    else
    {
        SEND_BUF[3] = 0x01;
    }
    switch (NUM_Type)
    {
        case Send_Speed:
            SEND_BUF[4] = 0xC0;
            break;
        case Send_LSpeed:
            SEND_BUF[4] = 0xC1;
            break;
        case Send_RSpeed:
            SEND_BUF[4] = 0xC2;
            break;
        case Send_Pitch:
            SEND_BUF[4] = 0xC3;
            break;
        case Send_Accel:
            SEND_BUF[4] = 0xC4;
            break;
        case Send_CPUProcesse:
            SEND_BUF[4] = 0xD5;
            break;
        case Send_FreeHeap:
            SEND_BUF[4] = 0xD6;
            break;
        case Send_MidValue:
            SEND_BUF[4] = 0xC5;
            break;
        case Send_Number1:
            SEND_BUF[4] = 0xC6;
            break;
        case Send_Number2:
            SEND_BUF[4] = 0xC7;
            break;
        case Send_Number3:
            SEND_BUF[4] = 0xC8;
            break;
        case Send_Number4:
            SEND_BUF[4] = 0xC9;
            break;
        case Send_Number5:
            SEND_BUF[4] = 0xCA;
            break;
        case Send_Number6:
            SEND_BUF[4] = 0xCB;
            break;
        case Send_FailNum:
            SEND_BUF[4] = 0xD7;
            break;
        case Send_CCDPix1:
            SEND_BUF[4] = 0xD8;
            break;
        case Send_CCDPix3:
            SEND_BUF[4] = 0xD9;
            break;
    }
    SEND_BUF[5] = (uint8_t)(Num / 65536);
    SEND_BUF[6] = (uint8_t)(Num / 256);
    SEND_BUF[7] = (uint8_t)(Num % 256);

    HAL_UART_Transmit(&huart1 , SEND_BUF, sizeof(SEND_BUF), 0xff);

}


void ImproveCar(void)
{
    uint16_t ch;

    static uint32_t i = 3;
    int32_t usart_temp;

    ch = usart1_temp;
    if (i == 3)
    {
        USART[0] = USART[1];
        USART[1] = USART[2];
        USART[2] = USART[3];
    }
    *(USART + i) = ch;
    if (USART[0] == 0x01 && USART[1] == 0x02 && USART[2] == 0x03
        && USART[3] == 0x04)
    {
        i++;
    }
    if (i == 9)
    {
        switch (USART[4])
        {
            case 0x01:
                usart_temp = (USART[5] << 16) + (USART[6] << 8) + USART[7];
                break;
            case 0x00:
                usart_temp = -((USART[5] << 16) + (USART[6] << 8) + USART[7]);
                break;
        }
        switch (USART[8])
        {
            case Rec_Balance_P:
                ii = (float)usart_temp / 1000;
                SteerPID.Kp  = (float)usart_temp / 1000;//舵机P
                break;

            case Rec_Balance_I:

                break;

            case Rec_Balance_D:
                SteerPID.Kd  = (float)usart_temp / 1000;//舵机D
                break;

            case Rec_Speed_P:

                break;

            case Rec_Speed_I:

                break;

            case Rec_Speed_D:

                break;

            case Rec_Position_P:
                PositionPID.Kp = (float)usart_temp / 1000; //差速P
                break;

            case Rec_Position_I:
                PositionPID.Ki = (float)usart_temp / 1000;  //差速I
                break;

            case Rec_Position_D:
                PositionPID.Kd = (float)usart_temp / 1000; //差速D
                break;

            case Rec_Balance_PIDRange_Max:

                break;

            case Rec_Balance_PIDRange_Min:

                break;

            case Rec_Speed_PIDRange_Max:

                break;

            case Rec_Speed_PIDRange_Min:

                break;

            case Rec_Position_PIDRange_Max:

                break;

            case Rec_Position_PIDRange_Min:

                break;

            case Rec_MaxSpeed_E:
			{
				if((SPEEDBASE+800)<7000)
				{
				SPEEDBASE+=800;
				}
			}
                break;

            case Rec_BSSpeed_E:
			{
				if((SPEEDBASE+300)<7000)
				{				
				SPEEDBASE+=300;
				}
			}
                break;

            case Rec_SSSpeed_E:
			{
				if((SPEEDBASE-800)>0)
				{
				SPEEDBASE-=800;
				}
			}
                break;

            case Rec_ZSpeed_E:
			{
				if((SPEEDBASE-300)>0)
				{				
				SPEEDBASE-=300;
				}
			}
                break;

            case Rec_MaxSpeed_R:

                break;

            case Rec_BSSpeed_R:

                break;

            case Rec_SSSpeed_R:

                break;

            case Rec_ZSpeed_R:

                break;
                /*启动*/
            case Rec_Go:
                MotorOutputFlag = 1;

                break;

            case Rec_Break:
 
			{
                MotorOutputFlag = 0;
                MotorSpeedR(0);
                MotorSpeedL(0);
                SteerChange(0);
			}
                break;
                /*遥控模式  在Go_Flag=0时可用*/
            case Rec_StandUp:
                {

                    //FTM_PWM_ChangeDuty(HW_FTM1, HW_FTM_CH0, 0);
                }
                break;

            case Rec_PushDown:
                {

                    //FTM_PWM_ChangeDuty(HW_FTM1, HW_FTM_CH0, 0);
                }
                break;

            case Rec_TurnForward:
                {

                    // FTM_PWM_ChangeDuty(HW_FTM1, HW_FTM_CH0, 0);
                }
                break;

            case Rec_TurnBack:
                {
                }
                break;

            case Rec_Up:
                //KeyUpCounter = 1;
                BlueToothChexk[0] = 0;
                if (!MotorOutputFlag)
                {
                    MotorSpeedR(SPEEDBASE);
                    MotorSpeedL(SPEEDBASE);
                    SteerChange(0);
                }
                break;

            case Rec_Down:
                BlueToothChexk[1] = 0;
                if (!MotorOutputFlag)
                {
                    MotorSpeedL(-SPEEDBASE);
                    MotorSpeedR(-SPEEDBASE);
                    SteerChange(0);
                }
                break;

            case Rec_Left:
                BlueToothChexk[2] = 0;
                if (!MotorOutputFlag)
                {
                    MotorSpeedR(SPEEDBASE);
                    MotorSpeedL(SPEEDBASE-800);
                    SteerChange(STEER_MIN);
                }
                break;

            case Rec_Right:
                BlueToothChexk[3] = 0;
                if (!MotorOutputFlag)
                {
                    MotorSpeedR(SPEEDBASE-800);
                    MotorSpeedL(SPEEDBASE);
                    SteerChange(STEER_MAX);
                }
                break;
            case Rec_Angle:
//                    AngleSet = (float)usart_temp / 1000;
                break;
        }
        i = 3;

    }
}


