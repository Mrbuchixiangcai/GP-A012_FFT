/**
******************************************************************************
* File Name          : ADC.c
* Description        : This file provides code for the configuration
*                      of the ADC instances.
******************************************************************************
** This notice applies to any and all portions of this file
* that are not between comment pairs USER CODE BEGIN and
* USER CODE END. Other portions of this file, whether
* inserted by the user or by software development tools
* are owned by their respective copyright owners.
*
* COPYRIGHT(c) 2018 STMicroelectronics
*
* Redistribution and use in source and binary forms, with or without
*modification, are permitted provided that the following conditions are met:
*   1. Redistributions of source code must retain the above copyright notice,
*      this list of conditions and the following disclaimer.
*   2. Redistributions in binary form must reproduce the above copyright
*notice, this list of conditions and the following disclaimer in the
*documentation and/or other materials provided with the distribution.
*   3. Neither the name of STMicroelectronics nor the names of its contributors
*      may be used to endorse or promote products derived from this software
*      without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
*LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
*INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "adc.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */
#include "app_main.h"
#include <math.h>
#include <stdlib.h>

/* USER CODE END 0 */

ADC_HandleTypeDef hadc;
DMA_HandleTypeDef hdma_adc;

/* ADC init function */
void MX_ADC_Init(void) {
	ADC_ChannelConfTypeDef sConfig;

	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE();

	/* DMA1_Channel1_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

	/**Configure the global features of the ADC (Clock, Resolution, Data Alignment
	* and number of conversion)
	*/
	hadc.Instance = ADC1;
	hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
	hadc.Init.Resolution = ADC_RESOLUTION_12B;
	hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;//对齐方式,ADC为12位中，右对齐方式 ADC_ALIGN=0;
	hadc.Init.ScanConvMode = DISABLE;////关闭扫描模式 因为只有一个通道,ADC_SCAN_DIRECTION_FORWARD;
	hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
	hadc.Init.LowPowerAutoWait = DISABLE;
	hadc.Init.LowPowerAutoPowerOff = DISABLE;
	hadc.Init.ContinuousConvMode = ENABLE; //触发一次，后续的转换就会永不停歇（除非CONT清0），
	hadc.Init.DiscontinuousConvMode = DISABLE;
	hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;//软件转换模式
	hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc.Init.DMAContinuousRequests = ENABLE;
	hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
	if (HAL_ADC_Init(&hadc) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	/**Configure for the selected ADC regular channel to be converted.
	*/
	sConfig.Channel = ADC_CHANNEL_1;
	sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
	sConfig.SamplingTime = ADC_SAMPLETIME_7CYCLES_5;
	if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	// ADC校准
	if (HAL_ADCEx_Calibration_Start(&hadc) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}
	if (HAL_ADC_Start_DMA(&hadc, (uint32_t*)AdcDma_Buf, ADC_DMA_SIZE) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}
}

void HAL_ADC_MspInit(ADC_HandleTypeDef *adcHandle) {

	GPIO_InitTypeDef GPIO_InitStruct;
	if (adcHandle->Instance == ADC1) {
		/* USER CODE BEGIN ADC1_MspInit 0 */

		/* USER CODE END ADC1_MspInit 0 */
		/* ADC1 clock enable */
		__HAL_RCC_ADC1_CLK_ENABLE();

		/**ADC GPIO Configuration
		PA1     ------> ADC_IN1
		*/
		GPIO_InitStruct.Pin = GPIO_PIN_1;
		GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

		/* USER CODE BEGIN ADC1_MspInit 1 */
		/* Peripheral DMA init*/

		hdma_adc.Instance = DMA1_Channel1;
		hdma_adc.Init.Direction = DMA_PERIPH_TO_MEMORY;
		hdma_adc.Init.PeriphInc = DMA_PINC_DISABLE;//接收一次数据后，设备地址禁止后移
		hdma_adc.Init.MemInc = DMA_MINC_ENABLE;//关闭接收一次数据后，目标内存地址后移
		hdma_adc.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;//定义外设数据宽度为16位
		hdma_adc.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;//DMA搬移数据尺寸，HalfWord就是为16位
		hdma_adc.Init.Mode = DMA_CIRCULAR;  //循环转换模式
		hdma_adc.Init.Priority = DMA_PRIORITY_MEDIUM; //DMA优先级
		if (HAL_DMA_Init(&hdma_adc) != HAL_OK) {
			_Error_Handler(__FILE__, __LINE__);
		}

		__HAL_LINKDMA(adcHandle, DMA_Handle, hdma_adc);

		/* USER CODE END ADC1_MspInit 1 */
	}
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef *adcHandle) {

	if (adcHandle->Instance == ADC1) {
		/* USER CODE BEGIN ADC1_MspDeInit 0 */

		/* USER CODE END ADC1_MspDeInit 0 */
		/* Peripheral clock disable */
		__HAL_RCC_ADC1_CLK_DISABLE();

		/**ADC GPIO Configuration
		PA1     ------> ADC_IN1
		*/
		HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1);

		/* USER CODE BEGIN ADC1_MspDeInit 1 */

		/* USER CODE END ADC1_MspDeInit 1 */
	}
}

/* USER CODE BEGIN 1 */
uint8_t Adc_Dma_Irq_f;
void ADCGetBuffer(void) //在中断里面调用，然后中断处理结束进入这里出具求平均
{
	uint16_t i;
	//uint32_t sumADC_Value; //
	if ((Adc_Dma_Irq_f) && (Flag_FFTSwitch == 0) && (FireSize1 == MODE4_FLASHING))
	{
		if (HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc), HAL_ADC_STATE_REG_EOC))
		{
			Adc_Dma_Irq_f = 0;
			if (HAL_ADC_Stop_DMA(&hadc) != HAL_OK)
			{
				_Error_Handler(__FILE__, __LINE__);
			}
			for (i = 0; i < ADC_DMA_SIZE; i++)
				AdcAudio_Buf[i] = AdcDma_Buf[i] - 0x0400;//减0x0400是因为最低音量时仍有0x0420左右
			AD_Assignment();
			if (HAL_ADC_Start_DMA(&hadc, (uint32_t*)AdcDma_Buf, ADC_DMA_SIZE) != HAL_OK)
			{
				_Error_Handler(__FILE__, __LINE__);
			}
		}
		
	}
	//kevin 	if((HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc), HAL_ADC_STATE_REG_EOC)) && (Flag_FFTSwitch==0))//Flag_FFTSwitch是fft转换完成开关
	//kevin 	{
	//kevin 		if (HAL_ADC_Stop_DMA(&hadc) != HAL_OK) 
	//kevin 		{
	//kevin 			_Error_Handler(__FILE__, __LINE__);
	//kevin 		}
	//kevin 		
	//kevin 		//for (i = 0; i < 6; i++) 
	//kevin 		//{
	//kevin 		//	sumADC_Value = volValueData[i] + sumADC_Value;
	//kevin 		//}
	//kevin 		//ADCVolValue = sumADC_Value / 6;
	//kevin 		//// ADCVolValue=(ADCVolValue<=0x0030)?0:ADCVolValue;
	//kevin 		////		adc_pj_data=ADCVolValue;
	//kevin 		//ADCDifferenceValue = ADCVolValue; // abs((ADCVolValue-ADCVolValue_bk));
	//kevin 		//ADCVolValue_bk = ADCVolValue;
	//kevin 		Flag_FFTSwitch = 1;
	//kevin 		if (HAL_ADC_Start_DMA(&hadc, (uint32_t*)volValueData, 64) != HAL_OK)
	//kevin 		{
	//kevin 			_Error_Handler(__FILE__, __LINE__);
	//kevin 		}
	//kevin 	}
}
/* USER CODE END 1 */

/**
* @}
*/

/**
* @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
