#ifndef __LISTENER_H
#define __LISTENER_H

#include "stm32f1xx_hal.h"

#define BLUE_REC_LEN  			20  

#define CODE_DZKD  0X00   //该命令码0x00用户不可进行修改。一级命令电子科技大学 喊出这句口令程序开始识别别的
#define CODE_KC	0x01		//开车
#define CODE_KWS	0x02	//结束命令 科沃斯 喊出后停车并且需要再喊电子科技大学才开始识别命令
#define CODE_TC 0x03			//停车
#define CODE_ZZ 0x04			//左转
#define CODE_YZ 0x05			//右转
#define CODE_DAOCHE 0x06			//倒车
#define CODE_JIASU 0x07			//加速
#define CODE_JIANSU	0x08			//减速
#define ERROR 	0x09
#define KouLing 	0x10
void Receive(uint8_t *usart_receive);
#endif
