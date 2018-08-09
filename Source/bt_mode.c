#include "app_main.h"

//宏定义macro definition//


//类型定义byte definition//


//变量定义variable definition//
uint8_t  BT_Work;
uint8_t  Uart1_TransmitBuffer[RECEIVELEN];
uint8_t  BT_ReceiveBuffer_A[RECEIVELEN];
uint8_t  BT_ReceiveBuffer_B[RECEIVELEN];
uint8_t  BT_TransmitBuffer[RECEIVELEN];
uint8_t  Uart1_RX_Timeout;

//标志位定义flags definetion//
uint8_t  Uart1_ReceiveBuffer_A_B;//用两个缓存来交替接收数据
uint8_t  Uart1_RX_Finish_A;
uint8_t  Uart1_RX_Finish_B;

//函数定义function definetion//
void hex_to_char(uint8_t *p,uint8_t indata)
{
	uint8_t tmp;
	tmp=indata>>4;
	if(tmp>=0x0A)
	 *p=((tmp-0x0A)+'A'); 
	else
	 *p=(tmp+'0');
	p++;
	tmp=indata&0x0F;
	if(tmp>=0x0A)
		*p=((tmp-0x0A)+'A'); 
	else
		*p=(tmp+'0');
}
char char_to_bcd(char indata1,char indata2)
{
	if(indata1>='A')
		indata1=((indata1-'A')+0x0A);
	else
		indata1=(indata1-'0');
	if(indata2>='A')
		indata2=((indata2-'A')+0x0A);
	else
		indata2=(indata2-'0');
	return (indata1*10+indata2);
}

///start void BlueMode_Receive(void)
///....................(功能说明)
///....................
void BT_Send_Command(uint8_t cmd)
{
//	switch(cmd)
//	{
//		
//	}
}	
///end void BlueMode_Receive(void)

///start void BlueMode_Receive(void)
///....................(功能说明)
///....................
void BlueMode_Receive(void)
{
	uint8_t  fireSize;
	uint8_t  temp_brightness;
	uint8_t  BT_ReceiveBuffer[RECEIVELEN];
//	if(Uart1_RX_Timeout != 0)
//	{//在中断里面置为3，并且前提是有空闲中断发生，空闲中断发生的原因是接收数据结束，
	 //IT从busy进入空闲，出发了IDLE(空闲中断))	
		//if(--Uart1_RX_Timeout==0)
		if((Uart1_RX_Finish_A) || (Uart1_RX_Finish_B))
		{
			memset(BT_ReceiveBuffer,0,sizeof(BT_ReceiveBuffer));
			if(Uart1_RX_Finish_A)
			{
				for(uint8_t i=0;i<UsartType1.rx_len;i++)
					BT_ReceiveBuffer[i]=BT_ReceiveBuffer_A[i];
				Uart1_RX_Finish_A=0;
			}
			else
			{
				for(uint8_t i=0;i<UsartType1.rx_len;i++)
					BT_ReceiveBuffer[i]=BT_ReceiveBuffer_B[i];
				Uart1_RX_Finish_B=0;
			}
//			memset(BT_ReceiveBuffer_A,0,sizeof(BT_ReceiveBuffer_A));
//			memset(BT_ReceiveBuffer_B,0,sizeof(BT_ReceiveBuffer_B));
			if((BT_ReceiveBuffer[0]=='A')&&(BT_ReceiveBuffer[1]=='0')&&(BT_ReceiveBuffer[2]=='0')&&
			   (BT_ReceiveBuffer[3]=='5')&&(BT_ReceiveBuffer[5]=='A')&&(BT_ReceiveBuffer[7]=='1'))
			{//开启彩灯   A005+A01\r\n
				FireSize1=(FireSize1==MODE0_OFF_FIRE)?MODE1_SMALL_FIRE1:FireSize1;
				FireSize1_bk=FireSize1;
				return;
			}
			if((BT_ReceiveBuffer[0]=='A')&&(BT_ReceiveBuffer[1]=='0')&&(BT_ReceiveBuffer[2]=='0')&&
			   (BT_ReceiveBuffer[3]=='5')&&(BT_ReceiveBuffer[5]=='A')&&(BT_ReceiveBuffer[7]=='0'))
			{//关闭彩灯   A005+A00\r\n
				FireSize1=MODE0_OFF_FIRE;
				if((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0))==1)
					PlayMode=PLAY_BT;
				else
					PlayMode=PLAY_OFF;
				FireSize1_bk=FireSize1;
				return;
			}
			if((BT_ReceiveBuffer[0]=='A')&&(BT_ReceiveBuffer[1]=='0')&&(BT_ReceiveBuffer[2]=='0')&&
			   (BT_ReceiveBuffer[3]=='5')&&(BT_ReceiveBuffer[5]=='B'))
			{//彩灯亮度调节   A005+Bxx\r\n
				temp_brightness=char_to_bcd(BT_ReceiveBuffer[6],BT_ReceiveBuffer[7]);
				if(temp_brightness==1)  //参考3236芯片手册的“呼吸灯非线性修正”
				{brightness1=5;electricityBrightness=0x07;}
				else if(temp_brightness==2)
				{brightness1=3;electricityBrightness=0x05;}
				else if(temp_brightness==3)
				{brightness1=2;electricityBrightness=0x03;}
				else if(temp_brightness==4)
				{brightness1=1;electricityBrightness=0x01;}
				return;
			}
			if((BT_ReceiveBuffer[0]=='A')&&(BT_ReceiveBuffer[1]=='0')&&(BT_ReceiveBuffer[2]=='0')&&
			   (BT_ReceiveBuffer[3]=='5')&&(BT_ReceiveBuffer[5]=='P'))
			{//火焰大小   A005+P06\r\n
				fireSize=char_to_bcd(BT_ReceiveBuffer[6],BT_ReceiveBuffer[7]);
				if(fireSize==1)
					FireSize1=MODE1_SMALL_FIRE1;
				else if(fireSize==2)
					FireSize1=MODE3_BIG_FIRE1;
				FireSize1_bk=FireSize1;
				return;
			}
			if((BT_ReceiveBuffer[0]=='A')&&(BT_ReceiveBuffer[1]=='0')&&(BT_ReceiveBuffer[2]=='0')&&
			   (BT_ReceiveBuffer[3]=='5')&&(BT_ReceiveBuffer[5]=='S'))
			{//火焰速度   A005+Sxx\r\n
				fireSpeed=char_to_bcd(BT_ReceiveBuffer[6],BT_ReceiveBuffer[7]);
				return;
			}
			if((BT_ReceiveBuffer[0]=='A')&&(BT_ReceiveBuffer[1]=='0')&&(BT_ReceiveBuffer[2]=='0')&&
			   (BT_ReceiveBuffer[3]=='5')&&(BT_ReceiveBuffer[5]=='D')&&(BT_ReceiveBuffer[6]=='T'))
			{//APP和蓝牙连接成功之后请求状态，返回此时状态
				uint8_t BTstaute[25]={"B005{00,00,00,00,00}\r\n"};//{"B005{00,00,00,00,00}\r\n"}
				hex_to_char(&BTstaute[5], FireSize1);
				hex_to_char(&BTstaute[8], temp_brightness);//
				hex_to_char(&BTstaute[11],brightness1);//
				hex_to_char(&BTstaute[14],FireSize1);
				hex_to_char(&BTstaute[17],fireSpeed);
				Usart1SendData_DMA(BTstaute);
				return;
			}
			if((BT_ReceiveBuffer[0]=='A')&&(BT_ReceiveBuffer[1]=='0')&&(BT_ReceiveBuffer[2]=='0')&&
			   (BT_ReceiveBuffer[3]=='5')&&(BT_ReceiveBuffer[5]=='T'))
			{//app到mcu随音乐闪动，脉动模式
				fireSize=char_to_bcd(BT_ReceiveBuffer[6],BT_ReceiveBuffer[7]);
				if(fireSize==1)
				{
					FireSize1_bk=FireSize1;
					FireSize1=MODE4_FLASHING;
					if(HAL_ADC_Start_DMA(&hadc, (uint32_t*)volValueData, 10) != HAL_OK)
					{
						_Error_Handler(__FILE__, __LINE__);
					}
				}
				else if(fireSize==0)
				{
					FireSize1=((FireSize1_bk==0)?MODE1_SMALL_FIRE1:FireSize1_bk);
					HAL_ADC_Stop_DMA(&hadc);
				}
				return;
			}
			if((BT_ReceiveBuffer[0]=='B')&&(BT_ReceiveBuffer[1]=='0') &&(BT_ReceiveBuffer[2]=='0')&&
			   (BT_ReceiveBuffer[3]=='5')&&((BT_ReceiveBuffer[5]=='K')||(BT_ReceiveBuffer[5]=='A')))
			{//按键传过来的火焰大小   B005+K0x\r\n || B005+A00\r\n
				fireSize=char_to_bcd(BT_ReceiveBuffer[6],BT_ReceiveBuffer[7]);
				if(fireSize==0)
				{
					FireSize1=MODE0_OFF_FIRE;
					keyNum=0;
					if((HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0))==1)
						PlayMode=PLAY_BT;
					else
						PlayMode=PLAY_OFF;
				}
				else if(fireSize==1)
				{
					FireSize1=MODE1_SMALL_FIRE1;
					keyNum=1;
				}
				else if(fireSize==2)
				{
					FireSize1=MODE3_BIG_FIRE1;
					keyNum=2;
				}
				else if(fireSize==3)
				{
					FireSize1=MODE4_FLASHING;
					keyNum=3;
				}
				FireSize1_bk=FireSize1;
				return;
			}
			if((BT_ReceiveBuffer[0]=='A')&&(BT_ReceiveBuffer[1]=='0') &&(BT_ReceiveBuffer[2]=='0')&&
			   (BT_ReceiveBuffer[3]=='5')&&((BT_ReceiveBuffer[5]=='C')&&(BT_ReceiveBuffer[6]=='O')))//CO：coverage覆盖
			{//app传过来的连续的几个数据  A005+CO{01040200FF}\r\n
				FireSize1=char_to_bcd(BT_ReceiveBuffer[8],BT_ReceiveBuffer[9]);//彩灯开关
				temp_brightness=char_to_bcd(BT_ReceiveBuffer[10],BT_ReceiveBuffer[11]);//彩灯亮度
					if(temp_brightness==1)  //参考3236芯片手册的“呼吸灯非线性修正”
					{brightness1=5;electricityBrightness=0x07;}
					else if(temp_brightness==2)
					{brightness1=3;electricityBrightness=0x05;}
					else if(temp_brightness==3)
					{brightness1=2;electricityBrightness=0x03;}
					else if(temp_brightness==4)
					{brightness1=1;electricityBrightness=0x01;}
				fireSize=char_to_bcd(BT_ReceiveBuffer[12],BT_ReceiveBuffer[13]);//彩灯（火焰）大小
					if(fireSize==1)
						FireSize1=MODE1_SMALL_FIRE1;
					else if(fireSize==2)
						FireSize1=MODE3_BIG_FIRE1;
					FireSize1_bk=FireSize1;
				fireSize=char_to_bcd(BT_ReceiveBuffer[14],BT_ReceiveBuffer[15]);//脉动状态
					if(fireSize==1)
					{
						FireSize1_bk=FireSize1;
						FireSize1=MODE4_FLASHING;
					}
					else if(fireSize==0)
					{
						FireSize1=((FireSize1_bk==0)?MODE1_SMALL_FIRE1:FireSize1_bk);
					}
				fireSpeed=char_to_bcd(BT_ReceiveBuffer[16],BT_ReceiveBuffer[17]);//彩灯速度
				return;
			}
		}
//	}
}
///end void BlueMode_Receive(void)

///start BlueMode_Handle(void)
///....................(功能说明)
///....................
void BlueMode_Handle(void)
{
	if(BT_Work==0)
	{
		MX_USART1_UART_Init();
	}
	BT_Work=1;
	//BlueMode_Receive();
//	Flag_BTProcessingTurnedOn=1;
}	
///end BlueMode_Handle(void)





