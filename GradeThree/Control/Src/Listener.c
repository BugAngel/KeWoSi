/**
  ******************************************************************************
  * @file    Listener.c
  * @author  WangRong
  * @version V1.0
  * @date    2017.2.2
  * @note    оƬLD3320
  �Ա�����https://detail.tmall.com/item.htm?id=41365254224&spm=a1z09.2.0.0.57hs6J&_u=m23aecgacdfc
  ******************************************************************************
  */

#include "Listener.h"
#include "Speaker.h"
#include "oled.h"
#include <string.h>
#include "Control.h"

uint8_t DianZiKeDa[] = {"���������"};
uint8_t KeWoSi[] = {"��������"};
uint8_t KaiChe[] = {"��"};
uint8_t TingChe[] = {"����"};
uint8_t ZuoZhuan[] = {"�����"};
uint8_t YouZhuan[] = {"����ת"};
uint8_t JiaSu[] = {"�ӿ�"};
uint8_t JianSu[] = {"����"};
uint8_t DaoChe[] = {"����"};

extern uint8_t RunFlag;            //���������־

uint8_t BLUE_RX_BUF[BLUE_REC_LEN] = {0};   //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��   ������ɱ�־
//bit14��   ���յ�0x0d
//bit13~0�� ���յ�����Ч�ֽ���Ŀ
uint16_t BLUE_RX_STA = 0;     //����״̬���

void Receive(uint8_t *usart_receive)
{
    if ((BLUE_RX_STA & 0x8000) == 0) //����δ���
    {
        if (BLUE_RX_STA & 0x4000) //���յ���0x0d
        {
            if (*usart_receive != 0x0a)
            {
                BLUE_RX_STA = 0; //���մ���,���¿�ʼ
            }
            else
            {
                BLUE_RX_STA |= 0x8000;  //���������
            }
        }
        else //��û�յ�0X0D
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
                    BLUE_RX_STA =  0; //�������ݴ���,���¿�ʼ����
                }
            }
        }
    }
    if (BLUE_RX_STA & 0x8000)
    {
        switch (BLUE_RX_BUF[0])       /*�Խ��ִ����ز���*/
        {
            case CODE_DZKD:         /*���׼����ʼ��*/
                printf("׼����ʼ\r\n");
                OLED_Clear();
                OLED_ShowString(12, 12, "Start", 24);
                OLED_Refresh_Gram();//������ʾ��OLED
                Speak(DianZiKeDa, strlen(DianZiKeDa));
                break;

            case CODE_KWS:          /*��������ˡ�*/
                printf("������\r\n");
                OLED_Clear();
                OLED_ShowString(12, 12, "End", 24);
                OLED_Refresh_Gram();//������ʾ��OLED
                Speak(KeWoSi, strlen(KeWoSi));
                Stop();
                break;

            case CODE_KC:    /*�����ʼ������*/
                printf("��ʼ����\r\n");
                Speak(KaiChe, strlen(KaiChe));
                OLED_Clear();
                OLED_ShowString(12, 12, "Forward", 24);
                OLED_Refresh_Gram();//������ʾ��OLED
                Stright();
                RunFlag = 1;
                break;

            case CODE_TC:       /*���׼��ͣ����*/
                printf("׼��ͣ��\r\n");
                OLED_Clear();
                OLED_ShowString(12, 12, "Stop", 24);
                OLED_Refresh_Gram();//������ʾ��OLED
                Speak(TingChe, strlen(TingChe));
                Stop();

                break;

            case CODE_ZZ:       /*�������ת��*/
                printf("����ת\r\n");
                OLED_Clear();
                OLED_ShowString(12, 12, "TurnLeft", 24);
                OLED_Refresh_Gram();//������ʾ��OLED
                Speak(ZuoZhuan, strlen(ZuoZhuan));
                TurnLeft();
                RunFlag = 1;
                break;

            case CODE_YZ:       /*�������ת��*/
                printf("����ת\r\n");
                OLED_Clear();
                OLED_ShowString(12, 12, "TurnRight", 24);
                OLED_Refresh_Gram();//������ʾ��OLED
                Speak(YouZhuan, strlen(YouZhuan));
                TurnRight();
                RunFlag = 1;
                break;

            case CODE_JIASU:        /*�����ʼ���١�*/
                printf("��ʼ����\r\n");
                OLED_Clear();
                OLED_ShowString(12, 12, "SpeedUp", 24);
                OLED_Refresh_Gram();//������ʾ��OLED
                Speak(JiaSu, strlen(JiaSu));
                JIASu();
                RunFlag = 1;
                break;

            case CODE_JIANSU:       /*���׼�����١�*/
                printf("׼������\r\n");
                OLED_Clear();
                OLED_ShowString(12, 12, "SpeedDown", 24);
                OLED_Refresh_Gram();//������ʾ��OLED
                Speak(JianSu, strlen(JianSu));
                JIANSu();
                RunFlag = 1;
                break;

            case CODE_DAOCHE:       /*���������*/
                printf("��ʼ����\r\n");
                OLED_Clear();
                OLED_ShowString(12, 12, "Backward", 24);
                OLED_Refresh_Gram();//������ʾ��OLED
                Speak(DaoChe, strlen(DaoChe));
                Back();
                RunFlag = 1;
                break;
            case ERROR: /*����ָ��*/
                printf("ָ�����\r\n");
                break;
            case KouLing: /*����ָ��*/
                printf("������һ������\r\n");
                break;
        }
        BLUE_RX_STA = 0;
    }
}
