#ifndef __LISTENER_H
#define __LISTENER_H

#include "stm32f1xx_hal.h"

#define BLUE_REC_LEN  			20  

#define CODE_DZKD  0X00   //��������0x00�û����ɽ����޸ġ�һ��������ӿƼ���ѧ �������������ʼʶ����
#define CODE_KC	0x01		//����
#define CODE_KWS	0x02	//�������� ����˹ ������ͣ��������Ҫ�ٺ����ӿƼ���ѧ�ſ�ʼʶ������
#define CODE_TC 0x03			//ͣ��
#define CODE_ZZ 0x04			//��ת
#define CODE_YZ 0x05			//��ת
#define CODE_DAOCHE 0x06			//����
#define CODE_JIASU 0x07			//����
#define CODE_JIANSU	0x08			//����
#define ERROR 	0x09
#define KouLing 	0x10
void Receive(uint8_t *usart_receive);
#endif
