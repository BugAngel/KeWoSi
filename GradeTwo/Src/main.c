/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */
#include "ccd.h"
#include "ImageHandle.h"
#include "Blue_Tooth.h"
#include "Control.h"
#include "Motor.h"
#include "esp8266.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc1;

TIM_HandleTypeDef htim4;
TIM_HandleTypeDef htim5;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart3;

osThreadId defaultTaskHandle;
osThreadId BlueToothHandle;
osThreadId StartHandle;
osThreadId StatusHandle;
osThreadId ControlHandle;
osThreadId EnvironmentHandle;
osThreadId WIFIHandle;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
volatile  unsigned int OSIdleCtr;    /* 空闲计数器  */
unsigned int OSIdleCtrMax;             /* 一秒最大计数值    */
unsigned int OSIdleCtrRun;             /* 运行时一秒计数值  */
float     OSCPUUsage;               /* CPU占用率  */
uint32_t FreeHeapSpace;

CCD_Info CCD;
uint8_t Line;
uint8_t Left_Scan_Value;
uint8_t Right_Scan_Value;
uint8_t GAS_Value;
uint8_t HCSR_Value;
uint8_t Light_Value;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_TIM4_Init(void);
static void MX_TIM5_Init(void);
static void MX_USART3_UART_Init(void);
void StartDefaultTask(void const * argument);
void StartBlueTooth(void const * argument);
void StartTask(void const * argument);
void StartStatus(void const * argument);
void StartControl(void const * argument);
void StartEnvironment(void const * argument);
void StartWIFI(void const * argument);

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);


/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
#include "stdio.h"
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart3 , (uint8_t *)&ch, 1 , 0xffff);
    return ch;
}
/* USER CODE END 0 */

int main(void)
{

    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration----------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_USART1_UART_Init();
    MX_TIM4_Init();
    MX_TIM5_Init();
    MX_USART3_UART_Init();

    /* USER CODE BEGIN 2 */
HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2); //舵机
TIM5->CCR2=1499;
    /* USER CODE END 2 */

    /* USER CODE BEGIN RTOS_MUTEX */
    /* add mutexes, ... */
    /* USER CODE END RTOS_MUTEX */

    /* USER CODE BEGIN RTOS_SEMAPHORES */
    /* add semaphores, ... */
    /* USER CODE END RTOS_SEMAPHORES */

    /* USER CODE BEGIN RTOS_TIMERS */
    /* start timers, add new ones, ... */
    /* USER CODE END RTOS_TIMERS */

    /* Create the thread(s) */
    /* definition and creation of defaultTask */
    osThreadDef(defaultTask, StartDefaultTask, osPriorityIdle, 0, 128);
    defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

    /* definition and creation of BlueTooth */
    osThreadDef(BlueTooth, StartBlueTooth, osPriorityNormal, 0, 512);
    BlueToothHandle = osThreadCreate(osThread(BlueTooth), NULL);

    /* definition and creation of Start */
    osThreadDef(Start, StartTask, osPriorityRealtime, 0, 128);
    StartHandle = osThreadCreate(osThread(Start), NULL);

    /* definition and creation of Status */
    osThreadDef(Status, StartStatus, osPriorityBelowNormal, 0, 128);
    StatusHandle = osThreadCreate(osThread(Status), NULL);

    /* definition and creation of Control */
    osThreadDef(Control, StartControl, osPriorityHigh, 0, 256);
    ControlHandle = osThreadCreate(osThread(Control), NULL);

    /* definition and creation of Environment */
    osThreadDef(Environment, StartEnvironment, osPriorityAboveNormal, 0, 256);
    EnvironmentHandle = osThreadCreate(osThread(Environment), NULL);

    /* definition and creation of WIFI */
    osThreadDef(WIFI, StartWIFI, osPriorityNormal, 0, 512);
    WIFIHandle = osThreadCreate(osThread(WIFI), NULL);

    /* USER CODE BEGIN RTOS_THREADS */
    /* add threads, ... */
    /* USER CODE END RTOS_THREADS */

    /* USER CODE BEGIN RTOS_QUEUES */
    /* add queues, ... */
    /* USER CODE END RTOS_QUEUES */


    /* Start scheduler */
    osKernelStart();

    /* We should never get here as control is now taken by the scheduler */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInit;

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

    HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    /* SysTick_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}

/* ADC1 init function */
void MX_ADC1_Init(void)
{

    ADC_ChannelConfTypeDef sConfig;

    /**Common config
    */
    hadc1.Instance = ADC1;
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    HAL_ADC_Init(&hadc1);

    /**Configure Regular Channel
    */
    sConfig.Channel = ADC_CHANNEL_0;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

}

/* TIM4 init function */
void MX_TIM4_Init(void)
{

    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;

    htim4.Instance = TIM4;
    htim4.Init.Prescaler = 0;
    htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim4.Init.Period = 7199;
    htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&htim4);

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig);

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1);

    HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2);

    HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3);

    HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4);

    HAL_TIM_MspPostInit(&htim4);

}

/* TIM5 init function */
void MX_TIM5_Init(void)
{

    TIM_MasterConfigTypeDef sMasterConfig;
    TIM_OC_InitTypeDef sConfigOC;

    htim5.Instance = TIM5;
    htim5.Init.Prescaler = 71;
    htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim5.Init.Period = 9999;
    htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&htim5);

    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig);

    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 1499;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2);

    HAL_TIM_MspPostInit(&htim5);

}

/* USART1 init function */
void MX_USART1_UART_Init(void)
{

    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart1);

}

/* USART3 init function */
void MX_USART3_UART_Init(void)
{

    huart3.Instance = USART3;
    huart3.Init.BaudRate = 115200;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart3);

}

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    /*Configure GPIO pins : Left_Scan_Pin Right_Scan_Pin */
    GPIO_InitStruct.Pin = Left_Scan_Pin | Right_Scan_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pins : SI_Pin CLK_Pin */
    GPIO_InitStruct.Pin = SI_Pin | CLK_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /*Configure GPIO pins : GAS_Pin HCSR_Pin Light_Pin */
    GPIO_InitStruct.Pin = GAS_Pin | HCSR_Pin | Light_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /*Configure GPIO pin : BEEP_Pin */
    GPIO_InitStruct.Pin = BEEP_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(BEEP_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOC, SI_Pin | CLK_Pin, GPIO_PIN_RESET);

    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

    /* USER CODE BEGIN 5 */
    /* Infinite loop */
    for (;;)
    {
        osDelay(1);
    }
    /* USER CODE END 5 */
}

/* StartBlueTooth function */
void StartBlueTooth(void const * argument)
{
    /* USER CODE BEGIN StartBlueTooth */
    /* Infinite loop */
    for (;;)
    {
        Send_Data(OSCPUUsage, Send_CPUProcesse);
        Send_Data(FreeHeapSpace, Send_FreeHeap);
        Send_Data(Left_Scan_Value, Send_Number1);
        Send_Data(Right_Scan_Value, Send_Number2);
        Send_Data(Line, Send_MidValue);
        Send_Data(GAS_Value, Send_LSpeed);
        Send_Data(HCSR_Value, Send_RSpeed);
        Send_Data(Light_Value, Send_Pitch);
        osDelay(200);
    }
    /* USER CODE END StartBlueTooth */
}

/* StartTask function */
void StartTask(void const * argument)
{
    /* USER CODE BEGIN StartTask */
    /* Infinite loop */
    for (;;)
    {
        osThreadSuspend(EnvironmentHandle);
        osThreadSuspend(WIFIHandle);
        osThreadSuspend(BlueToothHandle);
        osThreadSuspend(StatusHandle);
        osThreadSuspend(ControlHandle);   //任务挂起

        taskENTER_CRITICAL();  //进入临界区
        OSIdleCtr = 0;
        taskEXIT_CRITICAL();  //退出临界区

        osDelay(1000);

        taskENTER_CRITICAL();
        OSIdleCtrMax = OSIdleCtr;//延时一秒后取得一秒运行次数最大值
        taskEXIT_CRITICAL();

        OSIdleCtrMax /= 100;  //方便算百分率
        if (OSIdleCtrMax == 0)
        {
            OSCPUUsage = 0;
        }

        HAL_ADCEx_Calibration_Start(&hadc1);      //ADC校准
        HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1); //右轮正转
        HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2); //右轮反转
        HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3); //左轮正转
        HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4); //左轮反转
        HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2); //舵机

        CCD_Init();

        PID_init();  //PID初始化

        while (HAL_UART_Receive_IT(&huart1, &usart1_temp,
                                   sizeof(usart1_temp)) != HAL_OK);//开启串口中断
        while (HAL_UART_Receive_IT(&huart3, &usart3_temp,
                                   sizeof(usart3_temp)) != HAL_OK);
        wifi_init();

        osThreadResume(EnvironmentHandle);
        osThreadResume(WIFIHandle);
        osThreadResume(BlueToothHandle);
        osThreadResume(StatusHandle);
        osThreadResume(ControlHandle);       //被挂起任务的恢复

        osThreadTerminate( NULL);    //任务删除

        printf("不知不觉不问不痛不痒多少的时光\r\n");
        printf("不确定的夜晚小巷泪悄悄流淌\r\n");

        osDelay(1);
    }
    /* USER CODE END StartTask */
}

/* StartStatus function */
void StartStatus(void const * argument)
{
    /* USER CODE BEGIN StartStatus */
    /* Infinite loop */
    for (;;)
    {
        taskENTER_CRITICAL();
        OSIdleCtrRun =
            OSIdleCtr;                /*获得上一秒运行数 */
        OSIdleCtr    =
            0;                      /* 下一秒清零 */
        taskEXIT_CRITICAL();
        OSCPUUsage   = (100 - OSIdleCtrRun / (float) OSIdleCtrMax) ;
        OSCPUUsage = ABS(OSCPUUsage); //取绝对值，防止意外产生

        osDelay(1000);       /* 1s统计一次   */
    }
    /* USER CODE END StartStatus */
}

/* StartControl function */
void StartControl(void const * argument)
{
    /* USER CODE BEGIN StartControl */
    /* Infinite loop */
    for (;;)
    {
        CCD_ImageCapture(&CCD);
        Line = GetLine(&CCD);
        Left_Scan_Value = HAL_GPIO_ReadPin(Left_Scan_GPIO_Port, Left_Scan_Pin);
        Right_Scan_Value = HAL_GPIO_ReadPin(Right_Scan_GPIO_Port, Right_Scan_Pin);
        if (MotorOutputFlag)
        {
            if ((!Left_Scan_Value) && (!Right_Scan_Value))
            {
                MotorSpeedR(0);
                MotorSpeedL(0);
                SteerChange(0);
            }
            else
            {
                Pid_Control(Line);
            }
        }
        else
        {
            BlueToothChexk[0]++;
            BlueToothChexk[1]++;
            BlueToothChexk[2]++;
            BlueToothChexk[3]++;
            if ((BlueToothChexk[0] == 50) || (BlueToothChexk[1] == 50)
                || (BlueToothChexk[2] == 50) || (BlueToothChexk[3] == 50))
            {

                BlueToothChexk[0] = 0;
                BlueToothChexk[1] = 0;
                BlueToothChexk[2] = 0;
                BlueToothChexk[3] = 0;
                MotorSpeedR(0);
                MotorSpeedL(0);
                SteerChange(0);

            }
        }
        osDelay(20);
    }
    /* USER CODE END StartControl */
}

/* StartEnvironment function */
void StartEnvironment(void const * argument)
{
    /* USER CODE BEGIN StartEnvironment */
    /* Infinite loop */
    for (;;)
    {
        GAS_Value = HAL_GPIO_ReadPin(GAS_GPIO_Port, GAS_Pin);
        HCSR_Value = HAL_GPIO_ReadPin(HCSR_GPIO_Port, HCSR_Pin);
        Light_Value = HAL_GPIO_ReadPin(Light_GPIO_Port, Light_Pin);
        if (!GAS_Value)
        {
            HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(BEEP_GPIO_Port, BEEP_Pin, GPIO_PIN_RESET);
        }
        osDelay(100);
    }
    /* USER CODE END StartEnvironment */
}

/* StartWIFI function */
void StartWIFI(void const * argument)
{
    /* USER CODE BEGIN StartWIFI */
    /* Infinite loop */
    for (;;)
    {

        printf("CPU占用率%f%%\r\n", OSCPUUsage);
        printf("内存占用率%d%%\r\n", FreeHeapSpace);
        if (Light_Value == 0)
        {
            printf("强光\r\n");
        }
        else
        {
            printf("弱光\r\n");
        }
        if (HCSR_Value == 0)
        {
            printf("无人\r\n");
        }
        else
        {
            printf("有人\r\n");
        }
        if (GAS_Value == 0)
        {
            printf( "气体有毒\r\n");
        }
        else
        {
            printf("气体无毒\r\n");
        }
        if (Left_Scan_Value == 0)
        {
            printf( "左边有障碍\r\n" );
        }
        else
        {
            printf( "左边无障碍\r\n" );
        }
        if (Right_Scan_Value == 0)
        {
            printf( "右边有障碍\r\n" );
        }
        else
        {
            printf( "右边无障碍\r\n" );
        }
        printf("中线坐标%d\r\n", Line);
        osDelay(1000);
    }
    /* USER CODE END StartWIFI */
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
      ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */

}

#endif

/**
  * @}
  */

/**
  * @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
