/**
  ******************************************************************************
  * @file    wifi.c
  * @author  WangRong
  * @version V1.1
  * @date    2016.10.1
  * @note    ����WIFI��������
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

extern uint8_t RunFlag;            //���������־

uint8_t WIFI_RX_BUF[WIFI_REC_LEN] = {0};   //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��   ������ɱ�־
//bit14��   ���յ�0x0d
//bit13~0�� ���յ�����Ч�ֽ���Ŀ
uint16_t WIFI_RX_STA = 0;     //����״̬���

/**
  * @brief  ������λ������
  * @param  usart_receive ���մ�������
      * @arg  ��һλ  0xff  ����
        * @arg  �ڶ�λ  ��Ӧ����
        * @arg  ����λ  ������������
        * @arg  ����λ  ���ݵ�һ��λС��
        * @arg  ����λ  0x0d  ����
        * @arg  ����λ  0x0a  ����
    * @retval NONE
  * @attention
    @arg
  */
void UpperComputer(uint8_t *usart_receive)
{
    float usart_temp;
    uint8_t len;
    if ((WIFI_RX_STA & 0x8000) == 0) //����δ���
    {
        if (WIFI_RX_STA & 0x4000) //���յ���0x0d
        {
            if (*usart_receive != 0x0a)
            {
                WIFI_RX_STA = 0; //���մ���,���¿�ʼ
            }
            else
            {
                WIFI_RX_STA |= 0x8000;  //���������
            }
        }
        else //��û�յ�0X0D
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
                    WIFI_RX_STA =  0; //�������ݴ���,���¿�ʼ����
                }
            }
        }
    }

    if (WIFI_RX_STA & 0x8000)
    {
        len = WIFI_RX_STA & 0x3fff; //�õ��˴ν��յ������ݳ���
        //�����һλ  ȷ��������ȷ
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

                case Rec_Forward:  /*�����ʼ������*/
                    printf("��ʼ����\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "Forward", 24);
                    OLED_Refresh_Gram();//������ʾ��OLED
                    Stright();
                    Speak(KaiChe, strlen(KaiChe));
                    RunFlag = 1;
                    break;

                case Rec_Backward:
                    printf("��ʼ����\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "Backward", 24);
                    OLED_Refresh_Gram();//������ʾ��OLED
                    Speak(DaoChe, strlen(DaoChe));
                    Back();
                    RunFlag = 1;
                    break;

                case Rec_TurnLeft: /*�������ת��*/
                    printf("����ת\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "TurnLeft", 24);
                    OLED_Refresh_Gram();//������ʾ��OLED
                    Speak(ZuoZhuan, strlen(ZuoZhuan));
                    TurnLeft();
                    RunFlag = 1;
                    break;

                case Rec_TurnRight:  /*�������ת��*/
                    printf("����ת\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "TurnRight", 24);
                    OLED_Refresh_Gram();//������ʾ��OLED
                    Speak(YouZhuan, strlen(YouZhuan));
                    TurnRight();
                    RunFlag = 1;
                    break;

                case Rec_Firing:  /*���׼����ʼ��*/
                    printf("׼����ʼ\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "Start", 24);
                    OLED_Refresh_Gram();//������ʾ��OLED
                    Speak(DianZiKeDa, strlen(DianZiKeDa));
                    break;

                case Rec_Misfire: /*��������ˡ�*/
                    printf("������\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "End", 24);
                    OLED_Refresh_Gram();//������ʾ��OLED
                    Stop();
                    Speak(TingChe, strlen(TingChe));
                    break;

                case Rec_EncoderForward: /*�����ʼ���١�*/
                    printf("��ʼ����\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "SpeedUp", 24);
                    OLED_Refresh_Gram();//������ʾ��OLED
                    Speak(JiaSu, strlen(JiaSu));
                    JIASu();
                    RunFlag = 1;
                    break;

                case Rec_EncoderBackward: /*���׼�����١�*/
                    printf("׼������\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "SpeedDown", 24);
                    OLED_Refresh_Gram();//������ʾ��OLED
                    Speak(JianSu, strlen(JianSu));
                    JIANSu();
                    RunFlag = 1;
                    break;

                case Rec_EncoderTurnLeft: /*���׼��ͣ����*/
                    printf("׼��ͣ��\r\n");
                    OLED_Clear();
                    OLED_ShowString(12, 12, "Stop", 24);
                    OLED_Refresh_Gram();//������ʾ��OLED
                    Speak(TingChe, strlen(TingChe));
                    Stop();
                    break;

            }
        }

        WIFI_RX_STA = 0;
    }



}

