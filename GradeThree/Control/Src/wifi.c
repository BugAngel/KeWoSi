/**
  ******************************************************************************
  * @file    wifi.c
  * @author  WangRong
  * @version V1.1
  * @date    2016.10.1
  * @note    蓝牙WIFI都可以用
  ******************************************************************************
  */
#include "wifi.h"
#include "Control.h"
#include "oled.h"
#include "Speaker.h"
#include <string.h>




extern UART_HandleTypeDef huart1;

extern uint8_t DianZiKeDa[] ;
extern uint8_t KeWoSi[] ;
extern uint8_t KaiChe[] ;
extern uint8_t TingChe[] ;
extern uint8_t ZuoZhuan[] ;
extern uint8_t YouZhuan[];
extern uint8_t JiaSu[] ;
extern uint8_t JianSu[] ;
extern uint8_t DaoChe[];

extern uint8_t RunFlag;            //电机启动标志

uint8_t WIFI_RX_BUF[WIFI_REC_LEN] = {0};   //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，   接收完成标志
//bit14，   接收到0x0d
//bit13~0， 接收到的有效字节数目
uint16_t WIFI_RX_STA = 0;     //接收状态标记

/**
  * @brief  接收上位机数据
  * @param  usart_receive 接收串口数据
      * @arg  第一位  0xff  检验
        * @arg  第二位  对应数据
        * @arg  第三位  数据整数部分
        * @arg  第四位  数据第一二位小数
        * @arg  第五位  0x0d  检验
        * @arg  第六位  0x0a  检验
    * @retval NONE
  * @attention
    @arg
  */
void UpperComputer(uint8_t *usart_receive)
{
    float usart_temp;
    uint8_t len;
    if ((WIFI_RX_STA & 0x8000) == 0) //接收未完成
    {
        if (WIFI_RX_STA & 0x4000) //接收到了0x0d
        {
            if (*usart_receive != 0x0a)
            {
                WIFI_RX_STA = 0; //接收错误,重新开始
            }
            else
            {
                WIFI_RX_STA |= 0x8000;  //接收完成了
            }
        }
        else //还没收到0X0D
        {
            if (*usart_receive == 0x0d)
            {
                WIFI_RX_STA |= 0x4000;
            }
            else
            {
                WIFI_RX_BUF[WIFI_RX_STA & 0X3FFF] = *usart_receive ;
                WIFI_RX_STA++;
                if (WIFI_RX_STA > (WIFI_REC_LEN - 1))
                {
                    WIFI_RX_STA =  0; //接收数据错误,重新开始接收
                }
            }
        }
    }

    if (WIFI_RX_STA & 0x8000)
    {
        len = WIFI_RX_STA & 0x3fff; //得到此次接收到的数据长度
        //检验第一位  确保数据正确
        if (WIFI_RX_BUF[0] == 0xff)
        {
            if (len == 5)
            {
                usart_temp = (float)(WIFI_RX_BUF[3]) + ((float)WIFI_RX_BUF[4]) / 100;
            }
            if (WIFI_RX_BUF[2] == 0x01)
            {
                usart_temp = -usart_temp;
            }
            switch (WIFI_RX_BUF[1])
            {

                case Rec_Forward:  /*命令“开始发车”*/
                    printf("开始发车\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "Forward", 24);
                    OLED_Refresh_Gram();//更新显示到OLED
                    Stright();
                    Speak(KaiChe, strlen(KaiChe));
                    RunFlag = 1;
                    break;

                case Rec_Backward:
                    printf("开始倒车\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "Backward", 24);
                    OLED_Refresh_Gram();//更新显示到OLED
                    Speak(DaoChe, strlen(DaoChe));
                    Back();
                    RunFlag = 1;
                    break;

                case Rec_TurnLeft: /*命令“向左转”*/
                    printf("向左转\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "TurnLeft", 24);
                    OLED_Refresh_Gram();//更新显示到OLED
                    Speak(ZuoZhuan, strlen(ZuoZhuan));
                    TurnLeft();
                    RunFlag = 1;
                    break;

                case Rec_TurnRight:  /*命令“向右转”*/
                    printf("向右转\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "TurnRight", 24);
                    OLED_Refresh_Gram();//更新显示到OLED
                    Speak(YouZhuan, strlen(YouZhuan));
                    TurnRight();
                    RunFlag = 1;
                    break;

                case Rec_Firing:  /*命令“准备开始”*/
                    printf("准备开始\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "Start", 24);
                    OLED_Refresh_Gram();//更新显示到OLED
                    Speak(DianZiKeDa, strlen(DianZiKeDa));
                    break;

                case Rec_Misfire: /*命令“结束了”*/
                    printf("结束了\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "End", 24);
                    OLED_Refresh_Gram();//更新显示到OLED
                    Stop();
                    Speak(TingChe, strlen(TingChe));
                    break;

                case Rec_EncoderForward: /*命令“开始加速”*/
                    printf("开始加速\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "SpeedUp", 24);
                    OLED_Refresh_Gram();//更新显示到OLED
                    Speak(JiaSu, strlen(JiaSu));
                    JIASu();
                    RunFlag = 1;
                    break;

                case Rec_EncoderBackward: /*命令“准备减速”*/
                    printf("准备减速\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "SpeedDown", 24);
                    OLED_Refresh_Gram();//更新显示到OLED
                    Speak(JianSu, strlen(JianSu));
                    JIANSu();
                    RunFlag = 1;
                    break;

                case Rec_EncoderTurnLeft: /*命令“准备停车”*/
                    printf("准备停车\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "Stop", 24);
                    OLED_Refresh_Gram();//更新显示到OLED
                    Speak(TingChe, strlen(TingChe));
                    Stop();
                    break;

            }
        }

        WIFI_RX_STA = 0;
    }



}

