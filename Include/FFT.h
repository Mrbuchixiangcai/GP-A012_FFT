#ifndef __FFT_H__
#define __FFT_H__

#include "app_main.h"

#define NUM_FFT  ADC_DMA_SIZE     //这里要算多少点的fft就赋值多少，值只能是2的N次方   ADC_DMA_SIZE=64，在rgb.h中定义
//#define L       6      //2^L=NUM_FFT,这里因为128是2的7次方，如果是计算256点，则是2的8次方，N就是8，如果是512点则N＝9，如此类推
#if (NUM_FFT == 4)     //2^L=NUM_FFT,这里因为128是2的7次方，如果是计算256点，则是2的8次方，N就是8，如果是512点则N＝9，如此类推
	#define L   2      //L的定义满足L=log2(NUM_FFT) 
#elif (NUM_FFT == 8) 
	#define L   3      //L的定义满足L=log2(NUM_FFT) 
#elif (NUM_FFT == 16) 
	#define L   4      //L的定义满足L=log2(NNUM_FFT 
#elif (NUM_FFT == 32) 
	#define L   5      //L的定义满足L=log2(NUM_FFT) 
#elif (NUM_FFT == 64) 
	#define L   6      //L的定义满足L=log2(NNUM_FFT 
#elif (NUM_FFT == 128) 
	#define L   7      //L的定义满足L=log2(NUM_FFT) 
#elif (NUM_FFT == 256) 
	#define L   8      //L的定义满足L=log2(NNUM_FFT 
#elif (NUM_FFT == 512) 
	#define L   9      //L的定义满足L=log2(NUM_FFT) 
#elif (NUM_FFT == 1024) 
	#define L   10     //L的定义满足L=log2(NUM_FFT) 
#endif

//头文件header file//

//宏定义macro definition//

//类型定义byte definition//

//变量定义variable definition//

//标志未定义flags definetion//

//函数声明Function declaration//

//函数定义function definetion//

//外部调用_宏定义macro definition//

//外部调用_类型定义byte definition//

//外部调用_变量定义variable definition//

//外部调用_标志位定义flags definetion//
extern uint8_t  Flag_FFTSwitch;     //FFT转换开关

//外部调用_函数定义function definetion//
extern void FFT(void);
extern void FFT_Data_Handle(void);

extern void ScanFFT(void);
extern void AD_Assignment(void);


#endif




