/**
  ******************************************************************************
  * @file    Listener.c
  * @author  WangRong
  * @version V1.0
  * @date    2017.2.2
  * @note    芯片LD3320
  淘宝链接https://detail.tmall.com/item.htm?id=41365254224&spm=a1z09.2.0.0.57hs6J&_u=m23aecgacdfc
  ******************************************************************************
  */

#include "Listener.h"
#include "Speaker.h"
#include "oled.h"
#include <string.h>
#include "Control.h"

uint8_t DianZiKeDa[] = {"口令对上了"};
uint8_t KeWoSi[] = {"可以了吗"};
uint8_t KaiChe[] = {"跑"};
uint8_t TingChe[] = {"不走"};
uint8_t ZuoZhuan[] = {"向左拐"};
uint8_t YouZhuan[] = {"向右转"};
uint8_t JiaSu[] = {"加快"};
uint8_t JianSu[] = {"减慢"};
uint8_t DaoChe[] = {"倒车"};

extern uint8_t RunFlag;            //电机启动标志

uint8_t BLUE_RX_BUF[BLUE_REC_LEN] = {0};   //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，   接收完成标志
//bit14，   接收到0x0d
//bit13~0， 接收到的有效字节数目
uint16_t BLUE_RX_STA = 0;     //接收状态标记

void Receive(uint8_t *usart_receive)
{
    if ((BLUE_RX_STA & 0x8000) == 0) //接收未完成
    {
        if (BLUE_RX_STA & 0x4000) //接收到了0x0d
        {
            if (*usart_receive != 0x0a)
            {
                BLUE_RX_STA = 0; //接收错误,重新开始
            }
            else
            {
                BLUE_RX_STA |= 0x8000;  //接收完成了
            }
        }
        else //还没收到0X0D
        {
            if (*usart_receive == 0x0d)
            {
                BLUE_RX_STA |= 0x4000;
            }
            else
            {
                BLUE_RX_BUF[BLUE_RX_STA & 0X3FFF] = *usart_receive ;
                BLUE_RX_STA++;
                if (BLUE_RX_STA > (BLUE_REC_LEN - 1))
                {
                    BLUE_RX_STA =  0; //接收数据错误,重新开始接收
                }
            }
        }
    }
    if (BLUE_RX_STA & 0x8000)
    {
        switch (BLUE_RX_BUF[0])       /*对结果执行相关操作*/
        {
            case CODE_DZKD:         /*命令“准备开始”*/
                printf("准备开始\r\n");
                OLED_Clear();
                OLED_ShowString(12, 12, "Start", 24);
                OLED_Refresh_Gram();//更新显示到OLED
                Speak(DianZiKeDa, strlen(DianZiKeDa));
                break;

            case CODE_KWS:          /*命令“结束了”*/
                printf("结束了\r\n");
                OLED_Clear();
                OLED_ShowString(12, 12, "End", 24);
                OLED_Refresh_Gram();//更新显示到OLED
                Speak(KeWoSi, strlen(KeWoSi));
                Stop();
                break;

            case CODE_KC:    /*命令“开始发车”*/
                printf("开始发车\r\n");
                Speak(KaiChe, strlen(KaiChe));
                OLED_Clear();
                OLED_ShowString(12, 12, "Forward", 24);
                OLED_Refresh_Gram();//更新显示到OLED
                Stright();
                RunFlag = 1;
                break;

            case CODE_TC:       /*命令“准备停车”*/
                printf("准备停车\r\n");
                OLED_Clear();
                OLED_ShowString(12, 12, "Stop", 24);
                OLED_Refresh_Gram();//更新显示到OLED
                Speak(TingChe, strlen(TingChe));
                Stop();

                break;

            case CODE_ZZ:       /*命令“向左转”*/
                printf("向左转\r\n");
                OLED_Clear();
                OLED_ShowString(12, 12, "TurnLeft", 24);
                OLED_Refresh_Gram();//更新显示到OLED
                Speak(ZuoZhuan, strlen(ZuoZhuan));
                TurnLeft();
                RunFlag = 1;
                break;

            case CODE_YZ:       /*命令“向右转”*/
                printf("向右转\r\n");
                OLED_Clear();
                OLED_ShowString(12, 12, "TurnRight", 24);
                OLED_Refresh_Gram();//更新显示到OLED
                Speak(YouZhuan, strlen(YouZhuan));
                TurnRight();
                RunFlag = 1;
                break;

            case CODE_JIASU:        /*命令“开始加速”*/
                printf("开始加速\r\n");
                OLED_Clear();
                OLED_ShowString(12, 12, "SpeedUp", 24);
                OLED_Refresh_Gram();//更新显示到OLED
                Speak(JiaSu, strlen(JiaSu));
                JIASu();
                RunFlag = 1;
                break;

            case CODE_JIANSU:       /*命令“准备减速”*/
                printf("准备减速\r\n");
                OLED_Clear();
                OLED_ShowString(12, 12, "SpeedDown", 24);
                OLED_Refresh_Gram();//更新显示到OLED
                Speak(JianSu, strlen(JianSu));
                JIANSu();
                RunFlag = 1;
                break;

            case CODE_DAOCHE:       /*命令“倒车”*/
                printf("开始倒车\r\n");
                OLED_Clear();
                OLED_ShowString(12, 12, "Backward", 24);
                OLED_Refresh_Gram();//更新显示到OLED
                Speak(DaoChe, strlen(DaoChe));
                Back();
                RunFlag = 1;
                break;
            case ERROR: /*错误指令*/
                printf("指令错误\r\n");
                break;
            case KouLing: /*错误指令*/
                printf("请输入一级口令\r\n");
                break;
        }
        BLUE_RX_STA = 0;
    }
}
