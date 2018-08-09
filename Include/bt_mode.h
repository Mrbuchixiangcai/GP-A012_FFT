#ifndef  __BT_MODE_H__
#define  __BT_MODE_H__

//头文件header file//
#include "app_main.h"

//宏定义macro definition//


//类型定义byte definition//


//变量定义variable definition//


//标志位定义flags definetion//


//函数定义function definetion//


//外部调用_宏定义macro definition//


//外部调用_类型定义byte definition//


//外部调用_变量定义variable definition//
extern uint8_t  Uart1_ReceiveBuffer[RECEIVELEN];
extern uint8_t  Uart1_TransmitBuffer[RECEIVELEN];
extern uint8_t  BT_ReceiveBuffer_A[RECEIVELEN];
extern uint8_t  BT_ReceiveBuffer_B[RECEIVELEN];
extern uint8_t  BT_TransmitBuffer[RECEIVELEN];

//外部调用_标志位定义flags definetion//
extern uint8_t  Uart1_ReceiveBuffer_A_B;
extern uint8_t  Uart1_RX_Finish_A;
extern uint8_t  Uart1_RX_Finish_B;

//外部调用_函数定义function definetion//
extern void BlueMode_Handle(void);
extern void BlueMode_Receive(void);



#endif








