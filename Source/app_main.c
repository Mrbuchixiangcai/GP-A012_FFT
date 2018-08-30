//头文件header file//
#include "app_main.h"

//宏定义macro definition//


//类型定义byte definition//
PLAY_MODE PlayMode; //关机，开机，开机&蓝牙开启
FIRE_SIZE FireSize1;//火焰的大小
FIRE_SIZE  FireSize1_bk;

//变量定义variable definition//
uint8_t  idle_f;
uint16_t  cntIdle;
uint8_t  cntAppTick;
uint8_t  electricityBrightness;//电流亮度，改变3232芯片26H-49H寄存器的bit1和bit2可以改变电流，进而改变亮度
uint8_t  PWMBrightness;//PWM亮度，改变PWM亮度改变
//uint8_t  keyBT;
//uint8_t  keyBT_bk;



//标志位定义flags definetion//
uint8_t  AppTick1ms;
uint8_t  AppTick0;
uint8_t  AppTick1;
uint8_t  AppTick2;
uint8_t  AppTick3;
uint8_t  AppTick4;
uint8_t  AppTick5;
uint8_t  brightness1;
uint8_t  fireSpeed;
uint8_t  fireSpeed_Small;
uint8_t  fireSpeed_Big;
uint8_t  fireSpeed_Flashing;
uint8_t  bt_fire;

//函数定义function definetion//
/*******************************************************************
函数原型：
输入参数：
输出参数：
函数功能：
*******************************************************************/
void User_GPIO_DeInit(void) //端口初始化函数
{
	GPIO_InitTypeDef GPIO_InitStruct; //定义一个端口初始化结构体变量类型，用以初始化需要用到的端口

	// GPIO Ports Clock Enable
	__HAL_RCC_GPIOF_CLK_ENABLE(); //使能按键对应IO口时钟
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

//	//从低功耗唤醒端口配置
//	GPIO_InitStruct.Pin  = GPIO_PIN_All;
//	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	GPIO_InitStruct.Pin  = GPIO_PIN_All;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//	/*Configure GPIO pin : PB4 */
//	GPIO_InitStruct.Pin  = GPIO_PIN_4;
//	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING; //外部中断模式下降沿触发
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//	
//	GPIO_InitStruct.Pin  = GPIO_PIN_0;
//	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING; //外部中断模式下降沿触发
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//	/* EXTI interrupt init*/
//	HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
//	HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
//	HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_1_IRQn);

  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);
}

/*******************************************************************
函数原型：
输入参数：
输出参数：
函数功能：
*******************************************************************/
//void SysEnter_Idle(void)
//{
//	if(PlayMode==PLAY_OFF)
//	{
//		if(++cntIdle>200)
//		{
//			cntIdle=0;
//			if(HAL_ADC_DeInit(&hadc)!= HAL_OK)
//			{
//				Error_Handler();
//			}
//			if(HAL_UART_DeInit(&huart1)!= HAL_OK)
//			{
//				Error_Handler();
//			}
//			User_GPIO_DeInit();
////			HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN4);
//			HAL_RCC_DeInit();
//			HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN2); 
//			__NOP();__NOP();__NOP();__NOP();
//			HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);//IO重置后20.1uA
//			__NOP();__NOP();__NOP();__NOP();
//			SystemClock_Config();
//			MX_GPIO_Init();
//			MX_DMA_Init();
//			MX_ADC_Init();
//			MX_USART1_UART_Init();
//		}
//	}  
//	else
//	 	cntIdle=0;
//}

/*******************************************************************
函数原型：
输入参数：
输出参数：
函数功能：
*******************************************************************/
void SysEnter_Idle(void)
{
	if(PlayMode==PLAY_OFF)
	{
		if(++cntIdle>500)
		{
			cntIdle=0;
			//HAL_NVIC_DisableIRQ(DMA1_Channel2_3_IRQn);	
			if(HAL_ADC_DeInit(&hadc)!= HAL_OK)
			{
				Error_Handler();
			}
			
			
			if(HAL_UART_DeInit(&huart1)!= HAL_OK)
			{
				Error_Handler();
			}
			User_GPIO_DeInit();
			HAL_RCC_DeInit();
			__NOP();__NOP();__NOP();__NOP();
			//HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);//IO重置后20.1uA
			//HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
			HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);	
			//idle_f=1;
			//while(idle_f==1);
			__NOP();__NOP();__NOP();__NOP();
			SystemClock_Config();
			MX_GPIO_Init();
			MX_DMA_Init();
			MX_ADC_Init();
			MX_USART1_UART_Init();
		}
	}  
	else
	 	cntIdle=0;
}

/*******************************************************************
函数原型：
输入参数：
输出参数：
函数功能：如果开机会在PA0口接收到高电平
*******************************************************************/
void IoT_ON(void)
{
	/*keyBT = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
	if (keyBT_bk != keyBT)
	{
		keyBT_bk = keyBT;
		if (keyBT == 1)
			PlayMode = PLAY_BT;
		else
		{
			PlayMode = PLAY_OFF;
			FireSize1 = MODE0_OFF_FIRE;
		}
	}*/
}

/*******************************************************************
函数原型：
输入参数：
输出参数：
函数功能：
*******************************************************************/
void IoT_OFF(void)
{
	PlayMode = PLAY_OFF;
	FireSize1 = MODE0_OFF_FIRE;
	keyNum = 0;
}

/*******************************************************************
函数原型：
输入参数：
输出参数：
函数功能：
*******************************************************************/
void Scan_IoT_OFF(void)
{
	if (PlayMode == PLAY_OFF)
	{
		FireSize1 = MODE0_OFF_FIRE;
		keyNum = 0;
	}
}

/*******************************************************************
函数原型：
输入参数：
输出参数：
函数功能：
*******************************************************************/
void PowerON_Reset(void)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
	brightness1=1;//与electricityBrightness(电流控制亮度)共同控制
	electricityBrightness=0x07;//brightness1(PWM控制亮度)共同控制
	SDA5_OUT();
	SDA6_OUT();
	SDA7_OUT();
	SDA8_OUT();
	SDA9_OUT();
	SDA10_OUT();
	SDA11_OUT();
	SDA12_OUT();
	FireSize1=MODE0_OFF_FIRE;
	PlayMode=PLAY_ON;
}

/*******************************************************************
函数原型：
输入参数：
输出参数：
函数功能：
*******************************************************************/
void app_main(void)
{
	PowerON_Reset();
	while(1)
	{
		if(AppTick1ms)
		{
			AppTick1ms=0;
			IoT_ON();
			ADCGetBuffer();
		}
		if(AppTick0)
		{
			AppTick0=0;
			KeyScan();
			KeyComMsg();
		}
		if(AppTick1)
		{
			AppTick1=0;
			BlueMode_Handle();
		}
		if(AppTick2)
		{
			AppTick2=0;
			FireMode_Handle();
		}
		if(AppTick3 )
		{
			AppTick3=0;
			RGBMode_Handle();
			Scan_IoT_OFF();
		}
		if(AppTick5)
		{
			AppTick5 = 0;
			ScanFFT();
		}
//		if(AppTick1ms)
//		{
//			AppTick1ms=0;
//			ADCGetBuffer();
//		}
//		if(AppTick0)
//		{
//			AppTick0=0;
//		}
//		if(AppTick1)
//		{
//			AppTick1=0;
//		}
//		if(AppTick2)
//		{
//			AppTick2=0;
//		}
//		if(AppTick3)// ||（AppTick4）//因为fft转换时间长，所以要单独占用2个ms
//		{
//			AppTick3=0;
//		}
//		if (AppTick5)
//		{
//		}
//		FFT();
//		FFT_Data_Handle();
	}
}


