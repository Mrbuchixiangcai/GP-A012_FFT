#ifndef  __APP_MAIN_H__
#define  __APP_MAIN_H__

//头文件header file//
#include <string.h>
#include "dma.h"
#include "usart.h"
#include "gpio.h"
#include "adc.h"
#include "bt_mode.h"
#include "rgb.h"
#include "user_uart_dma.h"
#include "IO_IIC.h"
#include "SN3236.h"
#include "Key.h"
#include "rgb_array.h"
//#include "adc_data_js.h"
#include "fft.h"

//宏定义macro definition//


//类型定义byte definition//
typedef enum
{
	MODE0_OFF_FIRE   =0,
	MODE1_SMALL_FIRE1  ,
	MODE3_BIG_FIRE1    ,
	MODE4_FLASHING     ,//随音乐闪动
}FIRE_SIZE;

typedef enum
{
	PLAY_OFF  = 0,//关机
	PLAY_ON      ,//开机
	PLAY_BT      ,//开机且蓝牙开
}PLAY_MODE;

//变量定义variable definition//


//标志位定义flags definetion//


//函数定义function definetion//


//外部调用_宏定义macro definition//


//外部调用_类型定义byte definition//
extern PLAY_MODE  PlayMode; //关机，开机，开机&蓝牙开启
extern FIRE_SIZE  FireSize1;//火焰的大小
extern FIRE_SIZE  FireSize1_bk;

//外部调用_变量定义variable definition//
extern uint16_t  cntIdle;
extern uint8_t   cntAppTick;
extern uint8_t   Uart1_RX_Timeout;
extern uint8_t   brightness1;
extern uint8_t   fireSpeed;
extern uint8_t   fireSpeed_Small;
extern uint8_t   fireSpeed_Big;
extern uint8_t   fireSpeed_Flashing;
extern uint8_t   electricityBrightness;
extern uint8_t   PWMBrightness;
//extern uint8_t   keyBT;

//
//外部调用_标志位定义flags definetion//
extern uint8_t   AppTick1ms;
extern uint8_t   AppTick0;
extern uint8_t   AppTick1;
extern uint8_t   AppTick2;
extern uint8_t   AppTick3;
extern uint8_t   AppTick4;
extern uint8_t   AppTick5;
extern uint8_t   bt_fire;


//外部调用_函数定义function definetion//
extern void app_main(void);
extern void SystemClock_Config(void);


#endif







