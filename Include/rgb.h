#ifndef  __RGB_H__
#define  __RGB_H__

//头文件header file//
#include "app_main.h"

//宏定义macro definition//
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

//类型定义byte definition//
typedef struct
{
	uint8_t  path;
	uint8_t  step;
	uint8_t  data[2][6];
}LED_CAMPFIRE_TYPEDEF;


//变量定义variable definition//


//标志位定义flags definetion//


//函数定义function definetion//
void RGBMode_Handle(void);
void FireMode_Handle(void);

//外部调用_宏定义macro definition//


//外部调用_类型定义byte definition//


//外部调用_变量定义variable definition//
extern uint16_t volValueData[50];		  //采集到的初步电压值
extern uint16_t ADCVolValue;
extern uint16_t ADCVolValue_bk;
extern uint16_t ADCDifferenceValue;
extern uint16_t num_Delay;//灯光在切换到下一帧时延迟时间
extern uint8_t  step;
extern uint8_t  data1[2][36];
extern uint8_t  data2[20][2][36];
extern uint8_t  data3[36];
extern uint8_t  data4[36];
extern uint16_t adc_pj_data;

//外部调用_标志位定义flags definetion//
extern uint8_t  Flag_ADCGetFinished;//ADC数据获得之后求平均完成标志位

//外部调用_函数定义function definetion//
extern void GetVoltageValue(void);







#endif









