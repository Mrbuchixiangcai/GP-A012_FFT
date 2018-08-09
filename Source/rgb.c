//头文件header file//
#include "app_main.h"



uint8_t  RGB_Work;
uint8_t  step;
uint16_t num_Delay;//亮一圈灯光在切换到下一帧时延迟时间
uint16_t num_Delay2;//灯光切换到地下一圈亮时延时1s
uint8_t  num_Delay3;//脉动火焰灯光在切换到下一帧时延迟时间
uint16_t num_Delay4;
uint8_t  flashZero_Fade_Out;//灯光在闪动模式没有音乐时灯光亮度渐弱使用变量
uint16_t volValueData[50];		  //采集到的初步电压值
uint16_t ADCVolValue;
uint16_t ADCVolValue_bk;
uint16_t ADCDifferenceValue;
uint8_t  GetVoltageValue_bk;
uint8_t  LEDChangeDelay;


uint8_t  Flag_ADCGetFinished;//ADC数据获得之后求平均完成标志位
uint8_t  Flag_LEDSwitchover;//在亮一圈和整个图像切换，脉动模式
uint8_t  Flag_Start_DMA;

typedef struct
{
	uint8_t  path; 
	uint8_t  step; 
	uint8_t  data[3][36]; 
}LED_CAMPFIRE_TypeDef;	
LED_CAMPFIRE_TypeDef campFire1;
LED_CAMPFIRE_TypeDef campFire2;

u8 data1[2][36];
u8 data2[20][2][36];
u8 data3[36]={5,6,11,12,17,18,23,24,27,28,31,32,35,36,3,4,9,10,15,16,21,22,25,26,29,30,33,34,1,2,7,8,13,14,19,20};
u8 data4[36]={1,2,7,8,13,14,19,20,25,26,29,30,33,34,3,4,9,10,15,16,21,22,27,28,31,32,35,36,5,6,11,32,17,18,23,24};
	
	
//函数声明
void Array_CampFire3(void);


void GetVoltageValue(void)
{
//	uint8_t i;
//	if(Flag_ADCGetFinished==1)
//	{
//		Flag_ADCGetFinished=0;
//		GetVoltageValue_bk=(ADCVolValue & 0x000F);
//	}
//	return GetVoltageValue_bk;
//	if(FireSize1==MODE4_FLASHING)
//	{
//		uint8_t zero;
//		zero=ADCVolValue;
//		if(zero!=0)
//		{
//			num_Delay4++;
//			if(num_Delay4>6)
//			{
//				num_Delay4=0;
//				flashZero_Fade_Out=0;
//				Array_CampFire3();//(GetVoltageValue());
//				if(num_Delay3>5)
//				{
//					num_Delay3=0;
//					for(i=0;i<36;i++)
//					{
//						SN3236_Pwm1_1[i]=data1[PWM1][i];
//						SN3236_Pwm1_2[i]=data1[PWM2][i];
//						SN3236_Pwm2_1[i]=data1[PWM1][i];
//						SN3236_Pwm2_2[i]=data1[PWM2][i];
//						SN3236_Pwm3_1[i]=data1[PWM1][i];
//						SN3236_Pwm3_2[i]=data1[PWM2][i];
//						SN3236_Pwm4_1[i]=data1[PWM1][i];
//						SN3236_Pwm4_2[i]=data1[PWM2][i];
//					}
//					if(HAL_ADC_Start_DMA(&hadc, (uint32_t*)volValueData, 50) != HAL_OK)
//					{
//						_Error_Handler(__FILE__, __LINE__);
//					}
//				}
//				
//			}
//		}
//		else
//		{
//			if(flashZero_Fade_Out==0)//ad采集为0时进入这里，但是不立马就灭灯开启最底层的灯，先让最后亮的灯慢慢渐弱，然后渐弱都
//			{						 //为0时（事实是不是很好），然后再亮最底层的一圈，当flashZero_Fade_Out为1时最底层亮
//				flashZero_Fade_Out=1;
//				for(i=0;i<36;i++)
//				{
//					if(data1[PWM1][i]>=2)
//					{
//						data1[PWM1][i]-=2;
//						data1[PWM2][i]-=2;
//						flashZero_Fade_Out=0;
//					}
//					else if(data1[PWM1][i]==1)
//					{
//						data1[PWM1][i]=0;
//						data1[PWM2][i]=0;
//						flashZero_Fade_Out=0;
//					}
//				}
//				for(i=0;i<36;i++)
//				{
//					SN3236_Pwm1_1[i]=data1[PWM1][i];
//					SN3236_Pwm1_2[i]=data1[PWM2][i];
//					SN3236_Pwm2_1[i]=data1[PWM1][i];
//					SN3236_Pwm2_2[i]=data1[PWM2][i];
//					SN3236_Pwm3_1[i]=data1[PWM1][i];
//					SN3236_Pwm3_2[i]=data1[PWM2][i];
//					SN3236_Pwm4_1[i]=data1[PWM1][i];
//					SN3236_Pwm4_2[i]=data1[PWM2][i];
//				}
//			}
//			else //当flashZero_Fade_Out为1时最底层一圈亮
//			{
//				Array_CampFire3();//(GetVoltageValue());
//				for(i=0;i<36;i++)
//				{
//					SN3236_Pwm1_1[i]=data1[PWM1][i]/1;
//					SN3236_Pwm1_2[i]=data1[PWM2][i]/1;
//					SN3236_Pwm2_1[i]=data1[PWM1][i]/4;
//					SN3236_Pwm2_2[i]=data1[PWM2][i]/4;
//					SN3236_Pwm3_1[i]=data1[PWM1][i]/2;
//					SN3236_Pwm3_2[i]=data1[PWM2][i]/2;
//					SN3236_Pwm4_1[i]=data1[PWM1][i]/3;
//					SN3236_Pwm4_2[i]=data1[PWM2][i]/3;
//				}
//				if(HAL_ADC_Start_DMA(&hadc, (uint32_t*)volValueData, 50) != HAL_OK)
//				{
//					_Error_Handler(__FILE__, __LINE__);
//				}
//			}
//		}
//		
//		
//	}
	//SN3236_Init1();
}

uint16_t DivideValue(void)
{
	uint8_t  LEDChangeSpeed;
	LEDChangeSpeed=GetVoltageValue_bk;//ADCDifferenceValue;//GetVoltageValue_bk是上一个LEDChangeSpeed的值
	if(ADCDifferenceValue<0x30)
	{
		LEDChangeSpeed=0;
	}
	else if((ADCDifferenceValue>=0x30)  && (ADCDifferenceValue<0x318))
	{
		LEDChangeSpeed=1;
	}
	else if((ADCDifferenceValue>=0x318) && (ADCDifferenceValue<0x600))
	{
		LEDChangeSpeed=2;
	}
	else if((ADCDifferenceValue>=0x600) && (ADCDifferenceValue<=0x8E8))
	{
		LEDChangeSpeed=3;
	}
	else if((ADCDifferenceValue>=0x8E8) && (ADCDifferenceValue<0xBD0))
	{
		LEDChangeSpeed=4;
	}
	else if((ADCDifferenceValue>=0xBD0) && (ADCDifferenceValue<0xC82))
	{
		LEDChangeSpeed=5;
	}
	else if((ADCDifferenceValue>=0xC82) && (ADCDifferenceValue<0xD34))
	{
		LEDChangeSpeed=6;
	}
	else if((ADCDifferenceValue>=0xD34) && (ADCDifferenceValue<0xDE6))
	{
		LEDChangeSpeed=7;
	}
	else if((ADCDifferenceValue>=0xDE6) && (ADCDifferenceValue<0xE98))
	{
		LEDChangeSpeed=8;
	}
	else if((ADCDifferenceValue>=0xE98) && (ADCDifferenceValue<0xF4A))
	{
		LEDChangeSpeed=9;
	}
	else if((ADCDifferenceValue>=0xF4A) && (ADCDifferenceValue<=0xFFFF))
	{
		LEDChangeSpeed=10;
	}
//	else if((ADCDifferenceValue>=0x30)  && (ADCDifferenceValue<0x318))
//	{
//		if(LEDChangeSpeed>1)
//			LEDChangeSpeed=1;
//		LEDChangeDelay++;
//		if(LEDChangeDelay>100)
//		{
//			LEDChangeDelay=0;
//			LEDChangeSpeed=1;
//		}
//	}
//	else if((ADCDifferenceValue>=0x318) && (ADCDifferenceValue<0x600))
//	{
//		if(LEDChangeSpeed>2)
//			LEDChangeSpeed=2;
//		LEDChangeDelay++;
//		if(LEDChangeDelay>100)
//		{
//			LEDChangeDelay=0;
//			LEDChangeSpeed=2;
//		}
//	}
//	else if((ADCDifferenceValue>=0x600) && (ADCDifferenceValue<=0x8E8))
//	{
//		if(LEDChangeSpeed>3)
//			LEDChangeSpeed=3;
//		LEDChangeDelay++;
//		if(LEDChangeDelay>100)
//		{
//			LEDChangeDelay=0;
//			LEDChangeSpeed=3;
//		}
//	}
//	else if((ADCDifferenceValue>=0x8E8) && (ADCDifferenceValue<0xBD0))
//	{
//		if(LEDChangeSpeed>4)
//			LEDChangeSpeed=4;
//		LEDChangeDelay++;
//		if(LEDChangeDelay>100)
//		{
//			LEDChangeDelay=0;
//			LEDChangeSpeed=4;
//		}
//	}
//	else if((ADCDifferenceValue>=0xBD0) && (ADCDifferenceValue<0xC82))
//	{
//		if(LEDChangeSpeed>5)
//			LEDChangeSpeed=5;
//		LEDChangeDelay++;
//		if(LEDChangeDelay>100)
//		{
//			LEDChangeDelay=0;
//			LEDChangeSpeed=5;
//		}
//	}
//	else if((ADCDifferenceValue>=0xC82) && (ADCDifferenceValue<0xD34))
//	{
//		if(LEDChangeSpeed>6)
//			LEDChangeSpeed=6;
//		LEDChangeDelay++;
//		if(LEDChangeDelay>100)
//		{
//			LEDChangeDelay=0;
//			LEDChangeSpeed=6;
//		}
//	}
//	else if((ADCDifferenceValue>=0xD34) && (ADCDifferenceValue<0xDE6))
//	{
//		if(LEDChangeSpeed>7)
//			LEDChangeSpeed=7;
//		LEDChangeDelay++;
//		if(LEDChangeDelay>100)
//		{
//			LEDChangeDelay=0;
//			LEDChangeSpeed=7;
//		}
//	}
//	else if((ADCDifferenceValue>=0xDE6) && (ADCDifferenceValue<0xE98))
//	{
//		if(LEDChangeSpeed>8)
//			LEDChangeSpeed=8;
//		LEDChangeDelay++;
//		if(LEDChangeDelay>100)
//		{
//			LEDChangeDelay=0;
//			LEDChangeSpeed=8;
//		}
//	}
//	else if((ADCDifferenceValue>=0xE98) && (ADCDifferenceValue<0xF4A))
//	{
//		if(LEDChangeSpeed>9)
//			LEDChangeSpeed=9;
//		LEDChangeDelay++;
//		if(LEDChangeDelay>100)
//		{
//			LEDChangeDelay=0;
//			LEDChangeSpeed=9;
//		}
//	}
//	else if((ADCDifferenceValue>=0xF4A) && (ADCDifferenceValue<=0xFFFF))
//	{
//		if(LEDChangeSpeed>10)
//			LEDChangeSpeed=10;
//		LEDChangeDelay++;
//		if(LEDChangeDelay>100)
//		{
//			LEDChangeDelay=0;
//			LEDChangeSpeed=10;
//		}
//	}

	return LEDChangeSpeed;
}


void Array_CampFire3(void)
{
	uint8_t temp_FireSpeed_Flashing;
	temp_FireSpeed_Flashing=DivideValue();
	GetVoltageValue_bk=temp_FireSpeed_Flashing;
	if((temp_FireSpeed_Flashing==0) || (temp_FireSpeed_Flashing==1) || (temp_FireSpeed_Flashing==2))
		fireSpeed_Flashing=20;
	else if((temp_FireSpeed_Flashing==3) || (temp_FireSpeed_Flashing==4))
		fireSpeed_Flashing=15;
	else if((temp_FireSpeed_Flashing==5) || (temp_FireSpeed_Flashing==6))
		fireSpeed_Flashing=10;
	else if((temp_FireSpeed_Flashing==7) || (temp_FireSpeed_Flashing==8))
		fireSpeed_Flashing=5;
	else if((temp_FireSpeed_Flashing==9) || (temp_FireSpeed_Flashing==10))
		fireSpeed_Flashing=0;
//	fireSpeed_Flashing=temp_FireSpeed_Flashing+10;//(11-temp_FireSpeed_Flashing);//因为返回的是变化越大，DivideValue()返回的越大，速度越慢，要越小速度才快，所以"10-",
										   //但因为0-10变化太快，其他连个模式都是15或者22，所以又加10
	if(ADCVolValue==0)
	{
		num_Delay2++;
		if(num_Delay2>=100)
		{
			num_Delay2=100;
			Flag_LEDSwitchover=0;
		}
		else 
			Flag_LEDSwitchover=1;
	}
	else
	{
		num_Delay2=0;
		Flag_LEDSwitchover=1;
	}
	
	if(Flag_LEDSwitchover==0)
	{
		num_Delay3=0;
		num_Delay++;
		if(num_Delay==39)//上下跳动
		{
			for(uint8_t j=0;j<36;j++)
			{
				data1[PWM1][j]=campFire3_tab1[PWM1][j];
				data1[PWM2][j]=campFire3_tab1[PWM2][j];
			}
		}
		else if(num_Delay==78)
		{
			for(uint8_t j=0;j<36;j++)
			{
				data1[PWM1][j]=campFire3_tab2[PWM1][j];
				data1[PWM2][j]=campFire3_tab2[PWM2][j];;
			}
		}
		else if(num_Delay>=117)
		{
			num_Delay=0;
			for(uint8_t j=0;j<36;j++)
			{
				data1[PWM1][j]=campFire3_tab3[PWM1][j];
				data1[PWM2][j]=campFire3_tab3[PWM2][j];;
			}
		}
		Flag_Start_DMA=1;
//		if(num_Delay==50)//一直循环212121
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab1[PWM1][j];
//				data1[PWM2][j]=campFire3_tab1[PWM2][j];
//			}
//		}
//		else if(num_Delay==100)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab2[PWM1][j];
//				data1[PWM2][j]=campFire3_tab2[PWM2][j];;
//			}
//		}
//		else if(num_Delay==150)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab3[PWM1][j];
//				data1[PWM2][j]=campFire3_tab3[PWM2][j];;
//			}
//		}
//		else if(num_Delay==200)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab4[PWM1][j];
//				data1[PWM2][j]=campFire3_tab4[PWM2][j];
//			}
//		}
//		else if(num_Delay==250)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab5[PWM1][j];
//				data1[PWM2][j]=campFire3_tab5[PWM2][j];;
//			}
//		}
//		else if(num_Delay==300)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab6[PWM1][j];
//				data1[PWM2][j]=campFire3_tab6[PWM2][j];;
//			}
//		}
//		else if(num_Delay==350)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab7[PWM1][j];
//				data1[PWM2][j]=campFire3_tab7[PWM2][j];
//			}
//		}
//		else if(num_Delay==400)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab8[PWM1][j];
//				data1[PWM2][j]=campFire3_tab8[PWM2][j];;
//			}
//		}
//		else if(num_Delay==450)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab9[PWM1][j];
//				data1[PWM2][j]=campFire3_tab9[PWM2][j];;
//			}
//		}
//		else if(num_Delay==500)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab10[PWM1][j];
//				data1[PWM2][j]=campFire3_tab10[PWM2][j];
//			}
//		}
//		else if(num_Delay==550)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab11[PWM1][j];
//				data1[PWM2][j]=campFire3_tab11[PWM2][j];;
//			}
//		}
//		else if(num_Delay==600)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab12[PWM1][j];
//				data1[PWM2][j]=campFire3_tab12[PWM2][j];;
//			}
//		}
//		else if(num_Delay==650)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab13[PWM1][j];
//				data1[PWM2][j]=campFire3_tab13[PWM2][j];
//			}
//		}
//		else if(num_Delay==700)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab14[PWM1][j];
//				data1[PWM2][j]=campFire3_tab14[PWM2][j];;
//			}
//		}
//		else if(num_Delay==750)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab15[PWM1][j];
//				data1[PWM2][j]=campFire3_tab15[PWM2][j];;
//			}
//		}
//		else if(num_Delay==800)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab16[PWM1][j];
//				data1[PWM2][j]=campFire3_tab16[PWM2][j];
//			}
//		}
//		else if(num_Delay==850)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab17[PWM1][j];
//				data1[PWM2][j]=campFire3_tab17[PWM2][j];;
//			}
//		}
//		else if(num_Delay==900)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab18[PWM1][j];
//				data1[PWM2][j]=campFire3_tab18[PWM2][j];;
//			}
//		}
//		else if(num_Delay==950)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab19[PWM1][j];
//				data1[PWM2][j]=campFire3_tab19[PWM2][j];
//			}
//		}
//		else if(num_Delay==1000)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab20[PWM1][j];
//				data1[PWM2][j]=campFire3_tab20[PWM2][j];;
//			}
//		}
//		else if(num_Delay==1050)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab21[PWM1][j];
//				data1[PWM2][j]=campFire3_tab21[PWM2][j];;
//			}
//		}
//		else if(num_Delay==1100)
//		{
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab22[PWM1][j];
//				data1[PWM2][j]=campFire3_tab22[PWM2][j];
//			}
//		}
//		else if(num_Delay>=1150)
//		{
//			num_Delay=0;
//			for(uint8_t j=0;j<36;j++)
//			{
//				data1[PWM1][j]=campFire3_tab23[PWM1][j];
//				data1[PWM2][j]=campFire3_tab23[PWM2][j];;
//			}
//		}
	}
	else
	{
		num_Delay=0;
		num_Delay3++;
		if(num_Delay3>fireSpeed_Flashing)//fireSpeed_Flashing)//(num_Delay>5)
		{
			num_Delay3=0;
			Flag_Start_DMA=1;
			if(step==0)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab1[PWM1][j];
					data1[PWM2][j]=campFire1_tab1[PWM2][j];
				}
			}
			if(step==1)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab2[PWM1][j];
					data1[PWM2][j]=campFire1_tab2[PWM2][j];
				}
			}
			if(step==2)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab3[PWM1][j];
					data1[PWM2][j]=campFire1_tab3[PWM2][j];
				}
			}
			if(step==3)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab4[PWM1][j];
					data1[PWM2][j]=campFire1_tab4[PWM2][j];
				}
			}
			if(step==4)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab5[PWM1][j];
					data1[PWM2][j]=campFire1_tab6[PWM2][j];
				}
			}
			if(step==5)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab6[PWM1][j];
					data1[PWM2][j]=campFire1_tab6[PWM2][j];
				}
			}
			if(step==6)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab7[PWM1][j];
					data1[PWM2][j]=campFire1_tab7[PWM2][j];
				}
			}
			if(step==7)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab8[PWM1][j];
					data1[PWM2][j]=campFire1_tab8[PWM2][j];
				}
			}
			if(step==8)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab9[PWM1][j];
					data1[PWM2][j]=campFire1_tab9[PWM2][j];
				}
			}
			if(step==9)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab10[PWM1][j];
					data1[PWM2][j]=campFire1_tab10[PWM2][j];
				}
			}
			if(step==10)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab11[PWM1][j];
					data1[PWM2][j]=campFire1_tab11[PWM2][j];
				}
			}
			if(step==11)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab12[PWM1][j];
					data1[PWM2][j]=campFire1_tab12[PWM2][j];
				}
			}
			if(step==12)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab13[PWM1][j];
					data1[PWM2][j]=campFire1_tab13[PWM2][j];
				}
			}
			if(step==13)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab14[PWM1][j];
					data1[PWM2][j]=campFire1_tab14[PWM2][j];
				}
			}
			if(step==14)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab15[PWM1][j];
					data1[PWM2][j]=campFire1_tab15[PWM2][j];
				}
			}
			if(step==15)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab16[PWM1][j];
					data1[PWM2][j]=campFire1_tab16[PWM2][j];
				}
			}
			if(step==16)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab17[PWM1][j];
					data1[PWM2][j]=campFire1_tab17[PWM2][j];
				}
			}
			if(step==17)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab18[PWM1][j];
					data1[PWM2][j]=campFire1_tab18[PWM2][j];
				}
			}
			if(step==18)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab19[PWM1][j];
					data1[PWM2][j]=campFire1_tab19[PWM2][j];
				}
			}
			if(step==19)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab20[PWM1][j];
					data1[PWM2][j]=campFire1_tab20[PWM2][j];
				}
			}
			if(step==20)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab21[PWM1][j];
					data1[PWM2][j]=campFire1_tab21[PWM2][j];
				}
			}
			if(step==21)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab22[PWM1][j];
					data1[PWM2][j]=campFire1_tab22[PWM2][j];
				}
			}
			if(step==22)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab23[PWM1][j];
					data1[PWM2][j]=campFire1_tab23[PWM2][j];
				}
			}
			if(step==23)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab24[PWM1][j];
					data1[PWM2][j]=campFire1_tab24[PWM2][j];
				}
			}
			if(step==24)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab25[PWM1][j];
					data1[PWM2][j]=campFire1_tab25[PWM2][j];
				}
			}
			if(step==25)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab26[PWM1][j];
					data1[PWM2][j]=campFire1_tab26[PWM2][j];
				}
			}
			if(step==26)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab27[PWM1][j];
					data1[PWM2][j]=campFire1_tab27[PWM2][j];
				}
			}
			if(step==27)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab28[PWM1][j];
					data1[PWM2][j]=campFire1_tab28[PWM2][j];
				}
			}
			if(step==28)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab29[PWM1][j];
					data1[PWM2][j]=campFire1_tab29[PWM2][j];
				}
			}
			if(step==29)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab30[PWM1][j];
					data1[PWM2][j]=campFire1_tab30[PWM2][j];
				}
			}
			if(step==30)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab31[PWM1][j];
					data1[PWM2][j]=campFire1_tab31[PWM2][j];
				}
			}
			if(step==31)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab32[PWM1][j];
					data1[PWM2][j]=campFire1_tab32[PWM2][j];
				}
			}
			if(step==32)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab33[PWM1][j];
					data1[PWM2][j]=campFire1_tab33[PWM2][j];
				}
			}
			if(step==33)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab34[PWM1][j];
					data1[PWM2][j]=campFire1_tab34[PWM2][j];
				}
			}
			if(step==34)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab35[PWM1][j];
					data1[PWM2][j]=campFire1_tab35[PWM2][j];
				}
			}
			if(step==35)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab36[PWM1][j];
					data1[PWM2][j]=campFire1_tab36[PWM2][j];
				}
			}
			if(step==36)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab37[PWM1][j];
					data1[PWM2][j]=campFire1_tab37[PWM2][j];
				}
			}
			if(step==37)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab38[PWM1][j];
					data1[PWM2][j]=campFire1_tab38[PWM2][j];
				}
			}
			if(step==38)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab39[PWM1][j];
					data1[PWM2][j]=campFire1_tab39[PWM2][j];
				}
			}
			if(step==39)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab40[PWM1][j];
					data1[PWM2][j]=campFire1_tab40[PWM2][j];
				}
			}
			if(step==40)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab41[PWM1][j];
					data1[PWM2][j]=campFire1_tab41[PWM2][j];
				}
			}
			if(step==41)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab42[PWM1][j];
					data1[PWM2][j]=campFire1_tab42[PWM2][j];
				}
			}
			if(step==42)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab43[PWM1][j];
					data1[PWM2][j]=campFire1_tab43[PWM2][j];
				}
			}
			if(step==43)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab44[PWM1][j];
					data1[PWM2][j]=campFire1_tab44[PWM2][j];
				}
			}
			if(step==44)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab45[PWM1][j];
					data1[PWM2][j]=campFire1_tab45[PWM2][j];
				}
			}
			if(step==45)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab46[PWM1][j];
					data1[PWM2][j]=campFire1_tab46[PWM2][j];
				}
			}
			if(step==46)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab47[PWM1][j];
					data1[PWM2][j]=campFire1_tab47[PWM2][j];
				}
			}
			if(step==47)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab48[PWM1][j];
					data1[PWM2][j]=campFire1_tab48[PWM2][j];
				}
			}
			if(step==48)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab49[PWM1][j];
					data1[PWM2][j]=campFire1_tab49[PWM2][j];
				}
			}
			if(step==49)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab50[PWM1][j];
					data1[PWM2][j]=campFire1_tab50[PWM2][j];
				}
			}
			if(step==50)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab51[PWM1][j];
					data1[PWM2][j]=campFire1_tab51[PWM2][j];
				}
			}
			if(step==51)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab52[PWM1][j];
					data1[PWM2][j]=campFire1_tab52[PWM2][j];
				}
			}
			if(step==52)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab53[PWM1][j];
					data1[PWM2][j]=campFire1_tab53[PWM2][j];
				}
			}
			if(step==53)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab54[PWM1][j];
					data1[PWM2][j]=campFire1_tab54[PWM2][j];
				}
			}
			if(step==54)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab55[PWM1][j];
					data1[PWM2][j]=campFire1_tab55[PWM2][j];
				}
			}
			if(step==55)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab56[PWM1][j];
					data1[PWM2][j]=campFire1_tab56[PWM2][j];
				}
			}
			if(step==56)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab57[PWM1][j];
					data1[PWM2][j]=campFire1_tab57[PWM2][j];
				}
			}
			if(step==57)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab58[PWM1][j];
					data1[PWM2][j]=campFire1_tab58[PWM2][j];
				}
			}
			if(step==58)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab59[PWM1][j];
					data1[PWM2][j]=campFire1_tab59[PWM2][j];
				}
			}
			if(step==59)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab60[PWM1][j];
					data1[PWM2][j]=campFire1_tab60[PWM2][j];
				}
			}
			if(step==60)
			{
				for(uint8_t j=0;j<36;j++)
				{
					data1[PWM1][j]=campFire1_tab61[PWM1][j];
					data1[PWM2][j]=campFire1_tab61[PWM2][j];
				}
			}
			if(++step>=61)
				step=0;
			
		}
	}
}

void FireMode_Handle(void)
{
	u8 i;	
	if(RGB_Work==0)
	{
//			if(FireSize1!=MODE4_FLASHING)
			SN3236_Init1();
	}
	//RGB_Work=1;
	if(FireSize1==MODE0_OFF_FIRE)
	{
		for(i=0;i<0x4B;i++)
			SN3236_RegBuffer[i]=0;
		SN3236_RegBuffer[REG_00H_TURN_ON]=0x00;
	}
	else if(FireSize1==MODE1_SMALL_FIRE1)
	{
		Array_CampFire();
		for(i=0;i<36;i++)
		{
			SN3236_Pwm1_1[i]=data1[PWM1][i]/brightness1;
			SN3236_Pwm1_2[i]=data1[PWM2][i]/brightness1;
			SN3236_Pwm2_1[i]=data1[PWM1][i]/brightness1;
			SN3236_Pwm2_2[i]=data1[PWM2][i]/brightness1;
			SN3236_Pwm3_1[i]=data1[PWM1][i]/brightness1;
			SN3236_Pwm3_2[i]=data1[PWM2][i]/brightness1;
			SN3236_Pwm4_1[i]=data1[PWM1][i]/brightness1;
			SN3236_Pwm4_2[i]=data1[PWM2][i]/brightness1;
		}
	}
	else if(FireSize1==MODE3_BIG_FIRE1)
	{
		Array_CampFire2();
		for(i=0;i<36;i++)
		{
			SN3236_Pwm1_1[i]=data1[PWM1][i]/brightness1;
			SN3236_Pwm1_2[i]=data1[PWM2][i]/brightness1;
			SN3236_Pwm2_1[i]=data1[PWM1][i]/brightness1;
			SN3236_Pwm2_2[i]=data1[PWM2][i]/brightness1;
			SN3236_Pwm3_1[i]=data1[PWM1][i]/brightness1;
			SN3236_Pwm3_2[i]=data1[PWM2][i]/brightness1;
			SN3236_Pwm4_1[i]=data1[PWM1][i]/brightness1;
			SN3236_Pwm4_2[i]=data1[PWM2][i]/brightness1;
		}
	}
	else if(FireSize1==MODE4_FLASHING)
	{
		uint16_t zero;
		zero=ADCVolValue;
		if(zero!=0)
		{
			flashZero_Fade_Out=0;
			Array_CampFire3();
			for(i=0;i<36;i++)
			{
				SN3236_Pwm1_1[i]=data1[PWM1][i]/brightness1;
				SN3236_Pwm1_2[i]=data1[PWM2][i]/brightness1;
				SN3236_Pwm2_1[i]=data1[PWM1][i]/brightness1;
				SN3236_Pwm2_2[i]=data1[PWM2][i]/brightness1;
				SN3236_Pwm3_1[i]=data1[PWM1][i]/brightness1;
				SN3236_Pwm3_2[i]=data1[PWM2][i]/brightness1;
				SN3236_Pwm4_1[i]=data1[PWM1][i]/brightness1;
				SN3236_Pwm4_2[i]=data1[PWM2][i]/brightness1;
			}
//			if(HAL_ADC_Start_DMA(&hadc, (uint32_t*)volValueData, 50) != HAL_OK)
//			{
//				_Error_Handler(__FILE__, __LINE__);
//			}
		}
		else
		{
			if(flashZero_Fade_Out==0)//ad采集为0时进入这里，但是不立马就灭灯开启最底层的灯，先让最后亮的灯慢慢渐弱，然后渐弱都
			{						 //为0时（事实是不是很好），然后再亮最底层的一圈，当flashZero_Fade_Out为1时最底层亮
				flashZero_Fade_Out=1;
				for(i=0;i<36;i++)
				{
					if(data1[PWM1][i]>=2)
					{
						data1[PWM1][i]-=2;
						data1[PWM2][i]-=2;
						flashZero_Fade_Out=0;
					}
					else if(data1[PWM1][i]==1)
					{
						data1[PWM1][i]=0;
						data1[PWM2][i]=0;
						flashZero_Fade_Out=0;
					}
				}
				for(i=0;i<36;i++)
				{
					SN3236_Pwm1_1[i]=data1[PWM1][i];
					SN3236_Pwm1_2[i]=data1[PWM2][i];
					SN3236_Pwm2_1[i]=data1[PWM1][i];
					SN3236_Pwm2_2[i]=data1[PWM2][i];
					SN3236_Pwm3_1[i]=data1[PWM1][i];
					SN3236_Pwm3_2[i]=data1[PWM2][i];
					SN3236_Pwm4_1[i]=data1[PWM1][i];
					SN3236_Pwm4_2[i]=data1[PWM2][i];
				}
			}
			else //当flashZero_Fade_Out为1时最底层一圈亮
			{
				Array_CampFire3();//(GetVoltageValue());
				for(i=0;i<36;i++)
				{
					SN3236_Pwm1_1[i]=data1[PWM1][i]/1;
					SN3236_Pwm1_2[i]=data1[PWM2][i]/1;
					SN3236_Pwm2_1[i]=data1[PWM1][i]/4;
					SN3236_Pwm2_2[i]=data1[PWM2][i]/4;
					SN3236_Pwm3_1[i]=data1[PWM1][i]/2;
					SN3236_Pwm3_2[i]=data1[PWM2][i]/2;
					SN3236_Pwm4_1[i]=data1[PWM1][i]/3;
					SN3236_Pwm4_2[i]=data1[PWM2][i]/3;
				}
//				if(HAL_ADC_Start_DMA(&hadc, (uint32_t*)volValueData, 50) != HAL_OK)
//				{
//					_Error_Handler(__FILE__, __LINE__);
//				}
			}
		}
		if(Flag_Start_DMA==1)
		{
			Flag_Start_DMA=0;
			if(HAL_ADC_Start_DMA(&hadc, (uint32_t*)volValueData, 10) != HAL_OK)
			{
				_Error_Handler(__FILE__, __LINE__);
			}
		}
	}
//	{
//		uint8_t zero;
//		zero=ADCVolValue;
//		if(zero!=0)
//		{
//			num_Delay4++;
//			if(num_Delay4>6)
//			{
//				num_Delay4=0;
//				flashZero_Fade_Out=0;
//				Array_CampFire3();//(GetVoltageValue());
//				if(num_Delay3>fireSpeed_Flashing)
//				{
//					num_Delay3=0;
//					for(i=0;i<36;i++)
//					{
//						SN3236_Pwm1_1[i]=data1[PWM1][i];
//						SN3236_Pwm1_2[i]=data1[PWM2][i];
//						SN3236_Pwm2_1[i]=data1[PWM1][i];
//						SN3236_Pwm2_2[i]=data1[PWM2][i];
//						SN3236_Pwm3_1[i]=data1[PWM1][i];
//						SN3236_Pwm3_2[i]=data1[PWM2][i];
//						SN3236_Pwm4_1[i]=data1[PWM1][i];
//						SN3236_Pwm4_2[i]=data1[PWM2][i];
//					}
//					if(HAL_ADC_Start_DMA(&hadc, (uint32_t*)volValueData, 50) != HAL_OK)
//					{
//						_Error_Handler(__FILE__, __LINE__);
//					}
//				}
//				
//			}
//		}
//		else
//		{
//			if(flashZero_Fade_Out==0)//ad采集为0时进入这里，但是不立马就灭灯开启最底层的灯，先让最后亮的灯慢慢渐弱，然后渐弱都
//			{						 //为0时（事实是不是很好），然后再亮最底层的一圈，当flashZero_Fade_Out为1时最底层亮
//				flashZero_Fade_Out=1;
//				for(i=0;i<36;i++)
//				{
//					if(data1[PWM1][i]>=2)
//					{
//						data1[PWM1][i]-=2;
//						data1[PWM2][i]-=2;
//						flashZero_Fade_Out=0;
//					}
//					else if(data1[PWM1][i]==1)
//					{
//						data1[PWM1][i]=0;
//						data1[PWM2][i]=0;
//						flashZero_Fade_Out=0;
//					}
//				}
//				for(i=0;i<36;i++)
//				{
//					SN3236_Pwm1_1[i]=data1[PWM1][i];
//					SN3236_Pwm1_2[i]=data1[PWM2][i];
//					SN3236_Pwm2_1[i]=data1[PWM1][i];
//					SN3236_Pwm2_2[i]=data1[PWM2][i];
//					SN3236_Pwm3_1[i]=data1[PWM1][i];
//					SN3236_Pwm3_2[i]=data1[PWM2][i];
//					SN3236_Pwm4_1[i]=data1[PWM1][i];
//					SN3236_Pwm4_2[i]=data1[PWM2][i];
//				}
//			}
//			else //当flashZero_Fade_Out为1时最底层一圈亮
//			{
//				Array_CampFire3();//(GetVoltageValue());
//				for(i=0;i<36;i++)
//				{
//					SN3236_Pwm1_1[i]=data1[PWM1][i]/1;
//					SN3236_Pwm1_2[i]=data1[PWM2][i]/1;
//					SN3236_Pwm2_1[i]=data1[PWM1][i]/4;
//					SN3236_Pwm2_2[i]=data1[PWM2][i]/4;
//					SN3236_Pwm3_1[i]=data1[PWM1][i]/2;
//					SN3236_Pwm3_2[i]=data1[PWM2][i]/2;
//					SN3236_Pwm4_1[i]=data1[PWM1][i]/3;
//					SN3236_Pwm4_2[i]=data1[PWM2][i]/3;
//				}
//				if(HAL_ADC_Start_DMA(&hadc, (uint32_t*)volValueData, 50) != HAL_OK)
//				{
//					_Error_Handler(__FILE__, __LINE__);
//				}
//			}
//		}
//		if(HAL_ADC_Start_DMA(&hadc, (uint32_t*)volValueData, 50) != HAL_OK)
//					{
//						_Error_Handler(__FILE__, __LINE__);
//					}
//	}
}

void RGBMode_Handle(void)
{
	SN3236_Driver();
}






























