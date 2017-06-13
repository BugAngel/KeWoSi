/**
  ******************************************************************************
  * @file    esp8266.h
  * @author  WangRong
  * @version V1.0
  * @date    2015-12-25
  * @brief   WIFI¿ØÖÆ
  ******************************************************************************
  * @attention
	*
  ******************************************************************************
  */

#ifndef __ESP8266_H
#define	__ESP8266_H

#include "stm32f1xx_hal.h"
extern uint8_t usart3_temp;
void wifi_init(void);
 void ControlCar(void);
#endif /* __ESP8266_H */
