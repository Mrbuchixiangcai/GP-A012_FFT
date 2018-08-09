#include "app_main.h"



uint8_t  p;
uint16_t temp_Real, temp_Image, temp;

FFT_ImageClear();
for (i = 1; i <= N; i++)//for(1)
{
	b = 1;
	b <<= (i - 1);//蝶式运算，用于计算隔多少行计算，例如第一级，1和2行计算，第二级
	for (j = 0; j <= (b - 1); j++)//for(2)
	{
		p = 1;
		p <<= (N - i);
		p = p * j;
		for (k = j; k<NUM_FFT; k = (k + (2 * b)))//for(3)基二FFT
		{
			temp_Real = FFT_Real[k];
			temp_Image = FFT_Image[k];
			temp = FFT_Real[k + b];
			FFT_Real[k] = FFT_Real[k] + ((FFT_Real[k + b] * COS_TAB[p]) >> 7) + ((FFT_Image[k + b] * SIN_TAB[p]) >> 7);
			FFT_Image[k] = FFT_Image[k] - ((FFT_Real[k + b] * SIN_TAB[p]) >> 7) + ((FFT_Image[k + b] * COS_TAB[p]) >> 7);
			FFT_Real[k + b] = temp_Real - ((FFT_Real[k + b] * COS_TAB[p]) >> 7) - ((FFT_Image[k + b] * SIN_TAB[p]) >> 7);
			FFT_Image[k + b] = temp_Image + ((temp*SIN_TAB[p]) >> 7) - ((FFT_Image[k + b] * COS_TAB[p]) >> 7);
			//移位，防止溢出，结果已经是本值的1/64
			FFT_Real[k] >>= 1;
			FFT_Image[k] >>= 1;
			FFT_Real[k + b] >>= 1;
			FFT_Image[k + b] >>= 1;
		}
	}
}
//	for(uint8_t vpeakCnt=0;vpeakCnt<12;vpeakCnt++)//求对应点的模值
//	{
//		//Vpeak[vpeakCnt]=(uint16_t)(sqrt(pow(FFT_Real[vpeakCnt],2)+pow(FFT_Image[vpeakCnt],2)));
//		Vpeak[vpeakCnt]=sqrt((FFT_Real[vpeakCnt]*FFT_Real[vpeakCnt]) + (FFT_Image[vpeakCnt]*FFT_Image[vpeakCnt]));
//	}
//	for(uint8_t vpeakCnt=0;vpeakCnt<12;vpeakCnt++)//求对应点的波形峰值大小=模值/(N/2)
//	{
//		Vpeak[vpeakCnt]=Vpeak[vpeakCnt]/(NUM_FFT/2);
//	}
uint16_t Max, Min;
uint32_t sum;
static uint16_t Count = 0;
Vpeak[Count++] = (uint16_t)(100 * sqrt(FFT_Real[3] * FFT_Real[3] + FFT_Image[3] * FFT_Image[3]));
if (Count == 30)
{
	sum = 0;
	Max = Vpeak[0];
	Min = Vpeak[0];
	for (i = 0; i < Count; i++)
	{
		if (Vpeak[i] > Max)
			Max = Vpeak[i];
		if (Vpeak[i] < Min)
			Min = Vpeak[i];
		sum += Vpeak[i];
	}
	Vrms = (sum - Max - Min) / (Count - 2);
	Vrms = Vrms / 32 / 1.414;
	Count = 0;
}

if (Vrms <= 30)
{
	for (uint8_t j = 0; j<36; j++)
	{
		data1[PWM1][j] = campFire4_tab1[PWM1][j];
		data1[PWM2][j] = campFire4_tab1[PWM2][j];
	}
}
else if ((Vrms>30) && (Vrms <= 60))
{
	for (uint8_t j = 0; j<36; j++)
	{
		data1[PWM1][j] = campFire4_tab2[PWM1][j];
		data1[PWM2][j] = campFire4_tab2[PWM2][j];
	}
}
else if ((Vrms>60) && (Vrms <= 90))
{
	for (uint8_t j = 0; j<36; j++)
	{
		data1[PWM1][j] = campFire4_tab3[PWM1][j];
		data1[PWM2][j] = campFire4_tab3[PWM2][j];
	}
}
else if ((Vrms>90) && (Vrms <= 120))
{
	for (uint8_t j = 0; j<36; j++)
	{
		data1[PWM1][j] = campFire4_tab4[PWM1][j];
		data1[PWM2][j] = campFire4_tab4[PWM2][j];
	}
}
else if ((Vrms>120) && (Vrms <= 150))
{
	for (uint8_t j = 0; j<36; j++)
	{
		data1[PWM1][j] = campFire4_tab5[PWM1][j];
		data1[PWM2][j] = campFire4_tab5[PWM2][j];
	}
}
else if ((Vrms>150) && (Vrms <= 180))
{
	for (uint8_t j = 0; j<36; j++)
	{
		data1[PWM1][j] = campFire4_tab6[PWM1][j];
		data1[PWM2][j] = campFire4_tab6[PWM2][j];
	}
}
else if ((Vrms>180) && (Vrms <= 210))
{
	for (uint8_t j = 0; j<36; j++)
	{
		data1[PWM1][j] = campFire4_tab7[PWM1][j];
		data1[PWM2][j] = campFire4_tab7[PWM2][j];
	}
}
else
{
	if (Vrms>210)
	{
		for (uint8_t j = 0; j<36; j++)
		{
			data1[PWM1][j] = campFire4_tab8[PWM1][j];
			data1[PWM2][j] = campFire4_tab8[PWM2][j];
		}
	}
}
FFT_Real[0] = FFT_Image[0] = 0;  //去掉直流分量，也可以不去掉
}





