/**
  ******************************************************************************
  * @file    Speaker.c
  * @author  WangRong
  * @version V1.0
  * @date    2017.2.2
  * @note    芯片SYN6288
  淘宝链接https://detail.tmall.com/item.htm?id=41363263226&spm=a1z09.2.0.0.57hs6J&_u=m23aecgaa2d6
  ******************************************************************************
  */

#include "Speaker.h"

extern UART_HandleTypeDef huart2;

/**
* @brief  发送命令使喇叭说话
* @param  *test  要让喇叭说的话
* @param  length 让喇叭说的话的长度  在字符串数组定义处使用length=strlen(test);即可得出
* @retval NONE
* @attention length一定不能出错
*/
void Speak(uint8_t *test, uint8_t length)
{
    /********需要发送的文本********/
    uint8_t HeadOfFrame[5];
    uint8_t ecc = 0;
    uint8_t i = 0;
    /********帧头与校验位赋值********/
    HeadOfFrame[0] = 0XFD; //帧头
    HeadOfFrame[1] =
        0X00; //数据区长度高字节  这次没必要发255以上的字节，所以直接弄成0
    HeadOfFrame[2] = length +
                     3; //数据区长度低字节  test长度加命令字、命令参数、异或校验
    HeadOfFrame[3] = 0X01; //构造命令字  语音合成播放命令
    HeadOfFrame[4] =
        0X00; //构造命令参数  编码格式为GB2312（此工程使用的编码是这个）背景音乐编号1

    for (i = 0; i < 5; i++)
    {
        ecc = ecc ^ (HeadOfFrame[i]);
    }

    for (i = 0; i < length; i++)
    {
        ecc = ecc ^ (test[i]);
    }
    /********发送********/
    HAL_UART_Transmit(&huart2 , HeadOfFrame, 5, 0xff);
    HAL_UART_Transmit(&huart2 , test, length, 0xff);
    HAL_UART_Transmit(&huart2 , &ecc, 1, 0xff);
}
