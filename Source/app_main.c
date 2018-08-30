//ͷ�ļ�header file//
#include "app_main.h"

//�궨��macro definition//


//���Ͷ���byte definition//
PLAY_MODE PlayMode; //�ػ�������������&��������
FIRE_SIZE FireSize1;//����Ĵ�С
FIRE_SIZE  FireSize1_bk;

//��������variable definition//
uint8_t  idle_f;
uint16_t  cntIdle;
uint8_t  cntAppTick;
uint8_t  electricityBrightness;//�������ȣ��ı�3232оƬ26H-49H�Ĵ�����bit1��bit2���Ըı�����������ı�����
uint8_t  PWMBrightness;//PWM���ȣ��ı�PWM���ȸı�
//uint8_t  keyBT;
//uint8_t  keyBT_bk;



//��־λ����flags definetion//
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

//��������function definetion//
/*******************************************************************
����ԭ�ͣ�
���������
���������
�������ܣ�
*******************************************************************/
void User_GPIO_DeInit(void) //�˿ڳ�ʼ������
{
	GPIO_InitTypeDef GPIO_InitStruct; //����һ���˿ڳ�ʼ���ṹ��������ͣ����Գ�ʼ����Ҫ�õ��Ķ˿�

	// GPIO Ports Clock Enable
	__HAL_RCC_GPIOF_CLK_ENABLE(); //ʹ�ܰ�����ӦIO��ʱ��
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

//	//�ӵ͹��Ļ��Ѷ˿�����
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
//	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING; //�ⲿ�ж�ģʽ�½��ش���
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//	
//	GPIO_InitStruct.Pin  = GPIO_PIN_0;
//	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING; //�ⲿ�ж�ģʽ�½��ش���
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
����ԭ�ͣ�
���������
���������
�������ܣ�
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
//			HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);//IO���ú�20.1uA
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
����ԭ�ͣ�
���������
���������
�������ܣ�
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
			//HAL_PWR_EnterSTOPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);//IO���ú�20.1uA
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
����ԭ�ͣ�
���������
���������
�������ܣ������������PA0�ڽ��յ��ߵ�ƽ
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
����ԭ�ͣ�
���������
���������
�������ܣ�
*******************************************************************/
void IoT_OFF(void)
{
	PlayMode = PLAY_OFF;
	FireSize1 = MODE0_OFF_FIRE;
	keyNum = 0;
}

/*******************************************************************
����ԭ�ͣ�
���������
���������
�������ܣ�
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
����ԭ�ͣ�
���������
���������
�������ܣ�
*******************************************************************/
void PowerON_Reset(void)
{
	HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,GPIO_PIN_SET);
	brightness1=1;//��electricityBrightness(������������)��ͬ����
	electricityBrightness=0x07;//brightness1(PWM��������)��ͬ����
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
����ԭ�ͣ�
���������
���������
�������ܣ�
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
//		if(AppTick3)// ||��AppTick4��//��Ϊfftת��ʱ�䳤������Ҫ����ռ��2��ms
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


