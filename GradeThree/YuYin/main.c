/***************************�����Ƶ���****************************
**  �������ƣ�YS-V0.7����ʶ��ģ����������
**	CPU: STC11L08XE
**	����22.1184MHZ
**	�����ʣ�9600 bit/S
**	���ײ�Ʒ��Ϣ��YS-V0.7����ʶ�𿪷���
**                http://yuesheng001.taobao.com
**  ���ߣ�zdings
**  ��ϵ��751956552@qq.com
**  �޸����ڣ�2013.9.13
**  ˵��������ģʽ�� ��ÿ��ʶ��ʱ����Ҫ˵��С�ܡ�������� �����ܹ�������һ����ʶ��
/***************************�����Ƶ���******************************/
#include "config.h"
/************************************************************************************/
//	nAsrStatus ������main�������б�ʾ�������е�״̬������LD3320оƬ�ڲ���״̬�Ĵ���
//	LD_ASR_NONE:		��ʾû������ASRʶ��
//	LD_ASR_RUNING��		��ʾLD3320������ASRʶ����
//	LD_ASR_FOUNDOK:		��ʾһ��ʶ�����̽�������һ��ʶ����
//	LD_ASR_FOUNDZERO:	��ʾһ��ʶ�����̽�����û��ʶ����
//	LD_ASR_ERROR:		��ʾһ��ʶ��������LD3320оƬ�ڲ����ֲ���ȷ��״̬
/***********************************************************************************/
uint8 idata nAsrStatus = 0;
void MCU_init();
void ProcessInt0(); //ʶ������
void delay(unsigned long uldata);
void User_handle(uint8 dat);//�û�ִ�в�������
void Delay200ms();
void Led_test(void);//��Ƭ������ָʾ
uint8_t G0_flag = DISABLE; //���б�־��ENABLE:���С�DISABLE:��ֹ����
sbit LED = P4 ^ 2; //�ź�ָʾ��


uint8 DZKD = 0X00  ; //��������0x00�û����ɽ����޸ġ�һ��������ӿƼ���ѧ �������������ʼʶ����
uint8 KC=	0x01;		//����
uint8 KWS=	0x02;	//�������� ����˹ ������ͣ��������Ҫ�ٺ����ӿƼ���ѧ�ſ�ʼʶ������
uint8 TC= 0x03	;		//ͣ��
uint8 ZZ =0x04	;		//��ת
uint8 YZ =0x05	;		//��ת
uint8 DAOCHE =0x06;			//����
uint8 JIASU= 0x07;			//����
uint8 JIANSU=	0x08;			//����
uint8 ERROR =	0x09 ;
uint8 KouLing =	0x10 ;

/***********************************************************
* ��    �ƣ� void  main(void)
* ��    �ܣ� ������	�������
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
**********************************************************/
void  main(void)
{
    uint8 idata nAsrRes;
    uint8 i = 0;
    Led_test();
    MCU_init();
    LD_Reset();
    UartIni(); /*���ڳ�ʼ��*/
    nAsrStatus = LD_ASR_NONE;		//	��ʼ״̬��û������ASR


    while (1)
    {
        switch (nAsrStatus)
        {
            case LD_ASR_RUNING:
            case LD_ASR_ERROR:
                break;
            case LD_ASR_NONE:
                {
                    nAsrStatus = LD_ASR_RUNING;
                    if (RunASR() ==
                        0)	/*	����һ��ASRʶ�����̣�ASR��ʼ����ASR��ӹؼ��������ASR����*/
                    {
                        nAsrStatus = LD_ASR_ERROR;
                    }
                    break;
                }
            case LD_ASR_FOUNDOK: /*	һ��ASRʶ�����̽�����ȥȡASRʶ����*/
                {
                    nAsrRes = LD_GetResult();		/*��ȡ���*/
                    User_handle(nAsrRes);//�û�ִ�к���
                    nAsrStatus = LD_ASR_NONE;
                    break;
                }
            case LD_ASR_FOUNDZERO:
            default:
                {
                    nAsrStatus = LD_ASR_NONE;
                    break;
                }
        }// switch
    }// while

}
/***********************************************************
* ��    �ƣ� 	 LED�Ʋ���
* ��    �ܣ� ��Ƭ���Ƿ���ָʾ
* ��ڲ����� ��
* ���ڲ�������
* ˵    ����
**********************************************************/
void Led_test(void)
{
    LED = ~ LED;
    Delay200ms();
    LED = ~ LED;
    Delay200ms();
    LED = ~ LED;
    Delay200ms();
    LED = ~ LED;
    Delay200ms();
    LED = ~ LED;
    Delay200ms();
    LED = ~ LED;
}
/***********************************************************
* ��    �ƣ� void MCU_init()
* ��    �ܣ� ��Ƭ����ʼ��
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
**********************************************************/
void MCU_init()
{
    P0 = 0xff;
    P1 = 0xff;
    P2 = 0xff;
    P3 = 0xff;
    P4 = 0xff;


    LD_MODE = 0;		//	����MD�ܽ�Ϊ�ͣ�����ģʽ��д
    IE0 = 1;
    EX0 = 1;
    EA = 1;
}
/***********************************************************
* ��    �ƣ�	��ʱ����
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
**********************************************************/
void Delay200us()		//@22.1184MHz
{
    unsigned char i, j;
    _nop_();
    _nop_();
    i = 5;
    j = 73;
    do
    {
        while (--j);
    }
    while (--i);
}

void  delay(unsigned long uldata)
{
    unsigned int j  =  0;
    unsigned int g  =  0;
    while (uldata--)
        Delay200us();
}

void Delay200ms()		//@22.1184MHz
{
    unsigned char i, j, k;

    i = 17;
    j = 208;
    k = 27;
    do
    {
        do
        {
            while (--k);
        }
        while (--j);
    }
    while (--i);
}

/***********************************************************
* ��    �ƣ� �жϴ�����
* ��    �ܣ�
* ��ڲ�����
* ���ڲ�����
* ˵    ����
* ���÷�����
**********************************************************/
void ExtInt0Handler(void) interrupt 0
{
    ProcessInt0();
}
/***********************************************************
* ��    �ƣ��û�ִ�к���
* ��    �ܣ�ʶ��ɹ���ִ�ж������ڴ˽����޸�
* ��ڲ����� ��
* ���ڲ�������
* ˵    ����
**********************************************************/
void 	User_handle(uint8 dat)
{
	int i;
    //UARTSendByte(dat);//����ʶ���루ʮ�����ƣ�
    if (0 == dat)
    {
        G0_flag = ENABLE;
        LED = 0;
        UARTSendByte(DZKD);
        UARTSendByte(0x0d);
        UARTSendByte(0x0a);
		PrintCom("׼����ʼ\r\n"); /*text.....*/
    }
    else if (ENABLE == G0_flag)
    {
        //G0_flag=DISABLE;
        LED = 1;
        switch (dat)		  /*�Խ��ִ����ز���,�ͻ���ɾ��Printcom �����������滻Ϊ������Ҫ���ƵĴ���*/
        {
            case CODE_KWS:			/*�������˹��*/
                UARTSendByte(KWS);
                UARTSendByte(0x0d);
                UARTSendByte(0x0a);
                G0_flag = DISABLE;
				PrintCom("������\r\n");
                break;

            case CODE_KC:	 /*���������*/
                UARTSendByte(KC);
                UARTSendByte(0x0d);
                UARTSendByte(0x0a);
				PrintCom("�ܳ�\r\n");
                break;

            case CODE_TC:		/*���ͣ����*/
                UARTSendByte(TC);
                UARTSendByte(0x0d);
                UARTSendByte(0x0a);
				PrintCom("����\r\n");
                break;

            case CODE_ZZ:		/*�����ת��*/
                UARTSendByte(ZZ);
                UARTSendByte(0x0d);
                UARTSendByte(0x0a);
				PrintCom("��ת\r\n");
                break;

            case CODE_YZ:		/*�����ת��*/
                UARTSendByte(YZ);
                UARTSendByte(0x0d);
                UARTSendByte(0x0a);
				PrintCom("�ҹ�\r\n");
                break;

            case CODE_JIASU:		/*������١�*/
                UARTSendByte(JIASU);
                UARTSendByte(0x0d);
                UARTSendByte(0x0a);
				PrintCom("����\r\n");
                break;

		   case CODE_DAOCHE:		/*���������*/
                UARTSendByte(DAOCHE);
                UARTSendByte(0x0d);
                UARTSendByte(0x0a);
				PrintCom("����\r\n");
                break;

            case CODE_JIANSU:		/*������١�*/
                UARTSendByte(JIANSU);
                UARTSendByte(0x0d);
                UARTSendByte(0x0a);
                PrintCom("����\r\n");
                break;

            case CODE_ERROR:		/*�������*/
			    i=i+1;
                PrintCom("����ָ��\r\n"); /*text.....*/
				UARTSendByte(ERROR);
                UARTSendByte(0x0d);
                UARTSendByte(0x0a);
                //PrintCom("\r\n"); /*text.....*/
                break;

            default:
                PrintCom("������ʶ�𷢿���\r\n"); /*text.....*/
                break;
        }
    }
    else
    {
				UARTSendByte(KouLing);
                UARTSendByte(0x0d);
                UARTSendByte(0x0a);
        PrintCom("��˵��һ������\r\n"); /*text.....*/
    }
}
