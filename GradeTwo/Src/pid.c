/*********************************************************************************
 *@FileName   pid.c
 *@Version    V1
 *@Author     TracyW
 *@Date       2015/04/09
 *@Brief      PID��������������ٶȵ���˫�ջ�
 *********************************************************************************/

#include "pid.h"
#include "stdio.h"
#include "String.h"
//��ʼ��PID
void PID_Init(PidTypeDef * pid)
{
    memset(pid, 0, sizeof(PidTypeDef));
}

//���ò���
void PID_SetParam(PidTypeDef * pid, float p, float i, float d, float beta,
                  float dif_prior, float kaff, float kvff)
{
    pid->Kp = p;
    pid->Ki = i;
    pid->Kd = d;
    pid->beta = beta;
    pid->dif_prior = dif_prior;
    pid->Kaff = kaff;
    pid->Kvff = kvff;

    pid->delta_U = 0;
    pid->U = 0;
    pid->last_U = 0;
    pid->e[0] = 0;
    pid->e[1] = 0;
    pid->e[2] = 0;
    pid->r[0] = 0;
    pid->r[1] = 0;
    pid->r[2] = 0;
    pid->s[0] = 0;
    pid->s[1] = 0;
    pid->s[2] = 0;

}

void PID_CurrentParam(PidCurrentTypeDef * pid, float p, float i, float d)
{
    pid->Kp_C = p;
    pid->Ki_C = i;
    pid->Kd_C = d;
}

//PID����
void PID_SpeedCalc(PidTypeDef * pid, float rel_val, float set_val)
{
    float p = 0,
          i = 0,
          d = 0;
    pid->s[2] = set_val;
    pid->e[2] = set_val - rel_val; //��ȡ��ǰ���
    pid->r[2] = rel_val; //��ȡ��ǰֵ


    /*��������*/
    //p = pid->Kp * pid->e[2]; //λ��ʽp
    p = pid->Kp * (pid->e[2] - pid->e[1]); //����ʽP
    /*���ַ���*/
    if (pid->beta == 0)
    {
        i = pid->Ki * (pid->e[2]);
    }
    else
    {
        if (pid->e[2] <= pid->beta && pid->e[2] >= -pid->beta)
            i = pid->Ki * (pid->e[2]);
        else
            i = 0;
    }

    if (i > 4000)
        i = 4000;
    else if (i < -4000)
        i = -4000;

    /*΢������*/
    if (pid->dif_prior)
    {
        d = pid->Kd * (pid->r[2] - 2 * pid->r[1] + pid->r[0]);
    }
    else
    {
        d = pid->Kd * (pid->e[2] - 2 * pid->e[1] + pid->e[0]);
    }

//  kvff = (pid->s[2] - pid->s[1]) * pid->Kvff;//�ٶ�ǰ��
//  kaff = (pid->s[2] - 2 * pid->s[1] + pid->s[0]) * pid->Kaff;//���ٶ�ǰ��

    pid->delta_U = p + i + d; //+ kvff + kaff; //����ʽPID
    pid->U = pid->last_U + pid->delta_U; //λ��ʽPID

    if (pid->U > 8000)
    {
        pid->U = 8000;
    }
    else if (pid->U < -8000)
    {
        pid->U = -8000;
    }

    /*��¼��һ�����*/
    pid->last_U = pid->U;
    /*�����趨ֵ*/
    pid->s[0] = pid->s[1];
    pid->s[1] = pid->s[2];
    /*�������*/
    pid->e[0] = pid->e[1];
    pid->e[1] = pid->e[2];
    /*����ʵ��ֵ*/
    pid->r[0] = pid->r[1];
    pid->r[1] = pid->r[2];
}

void PID_PositionCalc(PidTypeDef * pid, float rel_val, float set_val)
{
    float p = 0,
          i = 0,
          d = 0;

    pid->e[2] = set_val - rel_val; //��ȡ��ǰ���

    p = pid->Kp * pid->e[2];

    /*���ַ���*/
    if (pid->beta == 0)
    {
        i = pid->Ki * (pid->e[2]);
    }
    else
    {
        if (pid->e[2] <= pid->beta && pid->e[2] >= -pid->beta)
            i = pid->Ki * (pid->e[2]);
        else
            i = 0;
    }

    if (i > 3000)
        i = 3000;
    else if (i < -3000)
        i = -3000;

    d = pid->Kd * (pid->e[2] - pid->e[1]);

    pid->U = p + i + d;

    if (pid->U > 500)
    {
        pid->U = 500;
    }
    else if (pid->U < -500)
    {
        pid->U = -500;
    }

    /*��¼��һ�����*/
    pid->last_U = pid->U;
    /*�������*/
    pid->e[0] = pid->e[1];
    pid->e[1] = pid->e[2];
}

void PID_CurrentCalc(PidCurrentTypeDef * pid, float rel_val, float set_val)
{
    float p = 0,
          i = 0,
          d = 0;

    pid->s_C[2] = set_val;
    pid->e_C[2] = set_val - rel_val; //��ȡ��ǰ���
    pid->r_C[2] = rel_val; //��ȡ��ǰֵ

    /*��������*/
    p = pid->Kp_C * (pid->e_C[2] - pid->e_C[1]);

    i = pid->Ki_C * (pid->e_C[2]);

    pid->delta_U_C = p + i + d ; //����ʽPID

    pid->U_C = pid->last_U_C + pid->delta_U_C; //λ��ʽPID

//  if(pid->U_C > 5) pid->U_C = 5;
//  else if(pid->U_C < -5) pid->U_C = -5;
//  else pid->U_C = pid->U_C;

    /*��¼��һ�����*/
    pid->last_U_C = pid->U_C;
    /*�����趨ֵ*/
    pid->s_C[0] = pid->s_C[1];
    pid->s_C[1] = pid->s_C[2];
    /*�������*/
    pid->e_C[0] = pid->e_C[1];
    pid->e_C[1] = pid->e_C[2];
    /*����ʵ��ֵ*/
    pid->r_C[0] = pid->r_C[1];
    pid->r_C[1] = pid->r_C[2];
}

void nn_PID_Cal(nn_PidTypeDef * pid, float rel_val, float set_val)
{
    float w1, w2, w3;

    pid->x1[0] = pid->x1[1];
    pid->x2[0] = pid->x2[1];
    pid->x3[0] = pid->x3[1];

    pid->q1[0] = pid->q1[1];
    pid->q2[0] = pid->q2[1];
    pid->q3[0] = pid->q3[1];

    pid->x1[1] = pid->w11 * rel_val + pid->w12 * set_val;
    pid->x2[1] = pid->w21 * rel_val + pid->w22 * set_val;
    pid->x3[1] = pid->w31 * rel_val + pid->w32 * set_val;

    if (pid->x1[1] > 1)
    {
        pid->q1[1] = 1;
    }
    else if (pid->x1[1] < -1)
    {
        pid->q1[1] = -1;
    }
    else pid->q1[1] = pid->x1[1];

    pid->q2[1] = pid->x2[1] + pid->q2[0];
    if (pid->q2[1] > 1)
    {
        pid->q2[1] = 1;
    }
    else if (pid->q2[1] < -1)
    {
        pid->q2[1] = -1;
    }
    else pid->q2[1] = pid->q2[1];

    pid->q3[1] = pid->x3[1] - pid->x3[0];
    if (pid->q3[1] > 1)
    {
        pid->q3[1] = 1;
    }
    else if (pid->q3[1] < -1)
    {
        pid->q3[1] = -1;
    }
    else pid->q3[1] = pid->q3[1];

    pid->out = w1 * pid->q1[1] + w2 * pid->q2[1] + w3 * pid->q3[1];

}



/**************************End of this file***************************************/
