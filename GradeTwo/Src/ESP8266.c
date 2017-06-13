/**
******************************************************************************
* @file    esp8266.c
* @author  WangRong
* @version V1.0
* @date    2015-12-25
* @brief   WIFI¿ØÖÆ
******************************************************************************
* @attention
*
******************************************************************************
*/

#include "esp8266.h"
#include "cmsis_os.h"
#include "status.h"
#include "Motor.h"
#include "Blue_Tooth.h"
uint8_t usart3_temp;

void wifi_init(void)
{
    printf("AT+CIFSR\r\n");
    osDelay(500);

    printf("AT+CIPSTART=");
    printf("%c", 0x22);
    printf("TCP");
    printf("%c", 0x22);
    printf(",");
    printf("%c", 0x22);
    printf("192.168.1.145");
    printf("%c", 0x22);
    printf(",5566\r\n");
    osDelay(500);

    printf("AT+CIPMODE=1\r\n");
    osDelay(100);

    printf("AT+CIPSEND\r\n");
    osDelay(100);
}

 void ControlCar(void)
 {
	if(usart3_temp == 'A')
	{
				if((SPEEDBASE+800)<7000)
				{
				SPEEDBASE+=800;
				}		
	}
	if(usart3_temp == 'B')
	{
				if((SPEEDBASE+300)<7000)
				{				
				SPEEDBASE+=300;
				}	
	}
	if(usart3_temp == 'C')
	{
				if((SPEEDBASE-800)>0)
				{
				SPEEDBASE-=800;
				}	
	}
	if(usart3_temp == 'D')
	{
				if((SPEEDBASE-300)>0)
				{				
				SPEEDBASE-=300;
				}	
	}
	if(usart3_temp == 'E')
	{
                MotorOutputFlag = 1;	
	}
	if(usart3_temp == 'F')
	{
                MotorOutputFlag = 0;
                MotorSpeedR(0);
                MotorSpeedL(0);
                SteerChange(0);	
	}

	if(usart3_temp == 'G')
	{
                BlueToothChexk[0] = 0;
                if (!MotorOutputFlag)
                {
                    MotorSpeedR(SPEEDBASE);
                    MotorSpeedL(SPEEDBASE);
                    SteerChange(0);
                }	
	}
	if(usart3_temp == 'H')
	{
                BlueToothChexk[1] = 0;
                if (!MotorOutputFlag)
                {
                    MotorSpeedL(-SPEEDBASE);
                    MotorSpeedR(-SPEEDBASE);
                    SteerChange(0);
                }	
	}
	if(usart3_temp == 'I')
	{
               BlueToothChexk[2] = 0;
                if (!MotorOutputFlag)
                {
                    MotorSpeedR(SPEEDBASE);
                    MotorSpeedL(SPEEDBASE-800);
                    SteerChange(STEER_MIN);
                }	
	}
	if(usart3_temp == 'J')
	{
                BlueToothChexk[3] = 0;
                if (!MotorOutputFlag)
                {
                    MotorSpeedR(SPEEDBASE-800);
                    MotorSpeedL(SPEEDBASE);
                    SteerChange(STEER_MAX);
                }	
	}	
 }
