#ifndef __FFT_H__
#define __FFT_H__

#include "app_main.h"

#define NUM_FFT  ADC_DMA_SIZE     //����Ҫ����ٵ��fft�͸�ֵ���٣�ֵֻ����2��N�η�   ADC_DMA_SIZE=64����rgb.h�ж���
//#define L       6      //2^L=NUM_FFT,������Ϊ128��2��7�η�������Ǽ���256�㣬����2��8�η���N����8�������512����N��9���������
#if (NUM_FFT == 4)     //2^L=NUM_FFT,������Ϊ128��2��7�η�������Ǽ���256�㣬����2��8�η���N����8�������512����N��9���������
	#define L   2      //L�Ķ�������L=log2(NUM_FFT) 
#elif (NUM_FFT == 8) 
	#define L   3      //L�Ķ�������L=log2(NUM_FFT) 
#elif (NUM_FFT == 16) 
	#define L   4      //L�Ķ�������L=log2(NNUM_FFT 
#elif (NUM_FFT == 32) 
	#define L   5      //L�Ķ�������L=log2(NUM_FFT) 
#elif (NUM_FFT == 64) 
	#define L   6      //L�Ķ�������L=log2(NNUM_FFT 
#elif (NUM_FFT == 128) 
	#define L   7      //L�Ķ�������L=log2(NUM_FFT) 
#elif (NUM_FFT == 256) 
	#define L   8      //L�Ķ�������L=log2(NNUM_FFT 
#elif (NUM_FFT == 512) 
	#define L   9      //L�Ķ�������L=log2(NUM_FFT) 
#elif (NUM_FFT == 1024) 
	#define L   10     //L�Ķ�������L=log2(NUM_FFT) 
#endif

//ͷ�ļ�header file//

//�궨��macro definition//

//���Ͷ���byte definition//

//��������variable definition//

//��־δ����flags definetion//

//��������Function declaration//

//��������function definetion//

//�ⲿ����_�궨��macro definition//

//�ⲿ����_���Ͷ���byte definition//

//�ⲿ����_��������variable definition//

//�ⲿ����_��־λ����flags definetion//
extern uint8_t  Flag_FFTSwitch;     //FFTת������

//�ⲿ����_��������function definetion//
extern void FFT(void);
extern void FFT_Data_Handle(void);

extern void ScanFFT(void);
extern void AD_Assignment(void);


#endif




