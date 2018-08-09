#ifndef  __RGB_H__
#define  __RGB_H__

//ͷ�ļ�header file//
#include "app_main.h"

//�궨��macro definition//
#define  PWM1  0
#define  PWM2  1
#define  PWM3  2

#define  GRADE0   0
#define  GRADE1   1
#define  GRADE2   2
#define  GRADE3   3
#define  GRADE4   4
#define  GRADE5   5
#define  GRADE6   6
#define  GRADE7   7
#define  GRADE8   8
#define  GRADE9   9
#define  GRADE10  10
#define  GRADE11  11
#define  GRADE12  12
#define  GRADE13  13
#define  GRADE14  14
#define  GRADE15  15

//���Ͷ���byte definition//
typedef struct
{
	uint8_t  path;
	uint8_t  step;
	uint8_t  data[2][6];
}LED_CAMPFIRE_TYPEDEF;


//��������variable definition//


//��־λ����flags definetion//


//��������function definetion//
void RGBMode_Handle(void);
void FireMode_Handle(void);

//�ⲿ����_�궨��macro definition//


//�ⲿ����_���Ͷ���byte definition//


//�ⲿ����_��������variable definition//
extern uint16_t volValueData[50];		  //�ɼ����ĳ�����ѹֵ
extern uint16_t ADCVolValue;
extern uint16_t ADCVolValue_bk;
extern uint16_t ADCDifferenceValue;
extern uint16_t num_Delay;//�ƹ����л�����һ֡ʱ�ӳ�ʱ��
extern uint8_t  step;
extern uint8_t  data1[2][36];
extern uint8_t  data2[20][2][36];
extern uint8_t  data3[36];
extern uint8_t  data4[36];
extern uint16_t adc_pj_data;

//�ⲿ����_��־λ����flags definetion//
extern uint8_t  Flag_ADCGetFinished;//ADC���ݻ��֮����ƽ����ɱ�־λ

//�ⲿ����_��������function definetion//
extern void GetVoltageValue(void);







#endif









