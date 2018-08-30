#include "app_main.h"

uint8_t audio_01_index;
uint16_t audio_01_buf[audio_01_max_index];
uint32_t audio_01_data;
uint16_t audio_01_pj_data;

//陈工传过来的，基本不变_begin
uint8_t Music_Tick;
//ADC数据计算
#define ADC_BUF_LEN 10
typedef struct
{	
 uint16_t max;	//??
 uint16_t mean; //??
 uint16_t mini;	//??
 uint16_t index;
 uint16_t Data[ADC_BUF_LEN];
}ADC_VAL_TypeDef;
ADC_VAL_TypeDef audio_adc_1;
ADC_VAL_TypeDef audio_adc_2;
ADC_VAL_TypeDef audio_adc_3;
ADC_VAL_TypeDef audio_adc_4;
ADC_VAL_TypeDef audio_adc_5;
ADC_VAL_TypeDef audio_adc_6;
ADC_VAL_TypeDef audio_adc_7;
ADC_VAL_TypeDef audio_adc_8;


void Audio_Average(ADC_VAL_TypeDef *audio_adc, uint16_t adc_val) 
{
	uint8_t  i;
	uint32_t sum=0;
	audio_adc->max=0; 
	audio_adc->mini=0xffff; 
	audio_adc->Data[audio_adc->index]=adc_val;
	if(++audio_adc->index>=ADC_BUF_LEN)
		audio_adc->index=0;
	for(i=0;i<ADC_BUF_LEN;i++)
	{
		if(audio_adc->Data[i] > audio_adc->max)
			audio_adc->max=audio_adc->Data[i];
		if(audio_adc->Data[i] < audio_adc->mini)
			audio_adc->mini=audio_adc->Data[i];
		sum += audio_adc->Data[i];
	}
	audio_adc->mean = sum / ADC_BUF_LEN;	
}

void Audio_Level_Deal(void)
{
	uint16_t tmp,i;
	static uint16_t audio_none_cnt;	//检测无信号时计数
	if(Music_Tick==0)//4ms
		return;
	Music_Tick=0;
	Audio_Average(&audio_adc_1, ADCVolValue); //adc_04_pj_data是获取的平均值，作为输入
	Audio_Average(&audio_adc_2, audio_adc_1.max); 
	Audio_Average(&audio_adc_3, audio_adc_2.mean); 
	Audio_Average(&audio_adc_4, audio_adc_3.mean); 	
	Audio_Average(&audio_adc_5, audio_adc_4.mean); 
	Audio_Average(&audio_adc_6, audio_adc_5.mean);
	Audio_Average(&audio_adc_7, audio_adc_6.mean); 
	Audio_Average(&audio_adc_8, audio_adc_7.mean);
	if(audio_adc_1.max>((audio_adc_8.max)+(audio_adc_8.max/10)))
	{
		tmp=(audio_adc_1.max-audio_adc_8.max)*16;
		if(tmp>=255)
			tmp=255;
	}
	else
	{
		tmp=0;	
	}		

	if(audio_adc_8.max)
	{
		audio_none_cnt=0;
	}
	else
	{
		if(audio_none_cnt>=1000)
			tmp=255;
		else
			audio_none_cnt++;	 
	}
//	if(DengGuang_JieZou_LiangDu != tmp)//节奏呼吸渐变
//	{
//		for(i=0;i<8;i++)
//		{
//			if(DengGuang_JieZou_LiangDu < tmp)	
//				DengGuang_JieZou_LiangDu++;
//		}	
//		for(i=0;i<4;i++)
//		{
//			if(DengGuang_JieZou_LiangDu > tmp)	
//				DengGuang_JieZou_LiangDu--;
//		}	
//	}
	//DengGuang_JieZou_LiangDu是最终输出值，作亮度信号
}
//陈工传过来的，基本不变_end









