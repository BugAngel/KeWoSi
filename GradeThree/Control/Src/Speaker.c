/**
  ******************************************************************************
  * @file    Speaker.c
  * @author  WangRong
  * @version V1.0
  * @date    2017.2.2
  * @note    оƬSYN6288
  �Ա�����https://detail.tmall.com/item.htm?id=41363263226&spm=a1z09.2.0.0.57hs6J&_u=m23aecgaa2d6
  ******************************************************************************
  */

#include "Speaker.h"

extern UART_HandleTypeDef huart2;

/**
* @brief  ��������ʹ����˵��
* @param  *test  Ҫ������˵�Ļ�
* @param  length ������˵�Ļ��ĳ���  ���ַ������鶨�崦ʹ��length=strlen(test);���ɵó�
* @retval NONE
* @attention lengthһ�����ܳ���
*/
void Speak(uint8_t *test, uint8_t length)
{
    /********��Ҫ���͵��ı�********/
    uint8_t HeadOfFrame[5];
    uint8_t ecc = 0;
    uint8_t i = 0;
    /********֡ͷ��У��λ��ֵ********/
    HeadOfFrame[0] = 0XFD; //֡ͷ
    HeadOfFrame[1] =
        0X00; //���������ȸ��ֽ�  ���û��Ҫ��255���ϵ��ֽڣ�����ֱ��Ū��0
    HeadOfFrame[2] = length +
                     3; //���������ȵ��ֽ�  test���ȼ������֡�������������У��
    HeadOfFrame[3] = 0X01; //����������  �����ϳɲ�������
    HeadOfFrame[4] =
        0X00; //�����������  �����ʽΪGB2312���˹���ʹ�õı�����������������ֱ��1

    for (i = 0; i < 5; i++)
    {
        ecc = ecc ^ (HeadOfFrame[i]);
    }

    for (i = 0; i < length; i++)
    {
        ecc = ecc ^ (test[i]);
    }
    /********����********/
    HAL_UART_Transmit(&huart2 , HeadOfFrame, 5, 0xff);
    HAL_UART_Transmit(&huart2 , test, length, 0xff);
    HAL_UART_Transmit(&huart2 , &ecc, 1, 0xff);
}
