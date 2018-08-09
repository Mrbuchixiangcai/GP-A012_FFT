/**
 ******************************************************************************
 * File Name          : USART.c
 * Description        : This file provides code for the configuration
 *                      of the USART instances.
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
//#include "usart.h"

//#include "gpio.h"
//#include "dma.h"

/* USER CODE BEGIN 0 */
#include "app_main.h"
USART_RECEIVETYPE UsartType1;
/* USER CODE END 0 */

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

/* USART1 init function */

void MX_USART1_UART_Init(void) {
  // DMA controller click enable
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

  // USART1_init
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK) {
    _Error_Handler(__FILE__, __LINE__);
  }
  // Program the Reception process
  __HAL_UART_DISABLE_IT(&huart1, UART_IT_RXNE); //
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);
  __HAL_UART_ENABLE_IT(&huart1, UART_IT_ERR);
  if (HAL_UART_Receive_DMA(&huart1, (uint8_t *)UsartType1.usartDMA_rxBuf,
                           RECEIVELEN) != HAL_OK) {
    Error_Handler();
  }
}

void HAL_UART_MspInit(UART_HandleTypeDef *uartHandle) {

  GPIO_InitTypeDef GPIO_InitStruct;
  if (uartHandle->Instance == USART1) {
    /* USER CODE BEGIN USART1_MspInit 0 */

    /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();

    /**USART1 GPIO Configuration
    PA2     ------> USART1_TX
    PA3     ------> USART1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF1_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 DMA Init */
    /* USART1_RX Init */
    hdma_usart1_rx.Instance = DMA1_Channel3;
    hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart1_rx) != HAL_OK) {
      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(uartHandle, hdmarx, hdma_usart1_rx);

    /* USART1_TX Init */
    hdma_usart1_tx.Instance = DMA1_Channel2;
    hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart1_tx.Init.Mode = DMA_NORMAL;
    hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_usart1_tx) != HAL_OK) {
      _Error_Handler(__FILE__, __LINE__);
    }

    __HAL_LINKDMA(uartHandle, hdmatx, hdma_usart1_tx);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    /* USER CODE BEGIN USART1_MspInit 1 */

    /* USER CODE END USART1_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef *uartHandle) {

  if (uartHandle->Instance == USART1) {
    /* USER CODE BEGIN USART1_MspDeInit 0 */

    /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA2     ------> USART1_TX
    PA3     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2 | GPIO_PIN_3);

    /* USART1 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);
    HAL_DMA_DeInit(uartHandle->hdmatx);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
    /* USER CODE BEGIN USART1_MspDeInit 1 */

    /* USER CODE END USART1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
// DMA发送函数
void Usart1SendData_DMA(uint8_t *pdata) {
  //	while(UsartType1.Flag_DMASend==USART_DMA_SENDING);
  //	UsartType1.Flag_DMASend=USART_DMA_SENDING;
  //	HAL_UART_Transmit_DMA(&huart1,pdata,Length);
  uint8_t len = 0;
  while (*pdata !=
         '\0') //字符串结束符，程序在见到第一个'\0'时就会认为该字符串结束了
  {            //没条字符串后面紧跟一个隐形 '\0'
    Uart1_TransmitBuffer[len] = *pdata; //一次只能赋值一个字符
    len++;
    pdata++;
  }
  //	if((*str == '\0') && (UsartType1.Flag_DMASend==USART_DMA_SENDING))
  //		UsartType1.Flag_DMASend=USART_DMA_SENDOVER;
  User_UART_Transmit_DMAStop(
      &huart1); //可能是判断此时是不是有数据发送，有就等下
  HAL_UART_Transmit_DMA(&huart1, Uart1_TransmitBuffer, len); //调用串口发送函数
}
// DMA发送完成中断回调函数
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
  __HAL_DMA_DISABLE(
      huart
          ->hdmatx); //发送完才能进入回调函数，不然进不了，所以设置为停止发送是可以的
  //	UsartType1.Flag_DMASend=USART_DMA_SENDOVER;
}

//串口接受空闲中断
void UsartReceive_IDLE(UART_HandleTypeDef *huart) {
  if ((__HAL_UART_GET_FLAG(&huart1, UART_FLAG_IDLE) != RESET) &&
      (__HAL_UART_GET_IT_SOURCE(&huart1, UART_IT_IDLE) !=
       RESET)) { //__HAL_UART_GET_FLAG获取到的是是否发生空闲中断标志
    __HAL_UART_CLEAR_IDLEFLAG(&huart1); //清标志位
    Uart1_RX_Timeout = 3;
    User_UART_Receive_DMAStop(&huart1);
    if (Uart1_ReceiveBuffer_A_B == 1) {
      UsartType1.rx_len = RECEIVELEN - huart1.hdmarx->Instance->CNDTR;
      for (uint8_t i = 0; i < UsartType1.rx_len; i++)
        BT_ReceiveBuffer_A[i] = UsartType1.usartDMA_rxBuf[i];
      memset(UsartType1.usartDMA_rxBuf, 0, sizeof(UsartType1.usartDMA_rxBuf));
      HAL_UART_Receive_DMA(&huart1, UsartType1.usartDMA_rxBuf, RECEIVELEN);
      Uart1_ReceiveBuffer_A_B = 0;
      Uart1_RX_Finish_A = 1;
    } else if (Uart1_ReceiveBuffer_A_B == 0) {
      UsartType1.rx_len = RECEIVELEN - huart1.hdmarx->Instance->CNDTR;
      for (uint8_t i = 0; i < UsartType1.rx_len; i++)
        BT_ReceiveBuffer_B[i] = UsartType1.usartDMA_rxBuf[i];
      memset(UsartType1.usartDMA_rxBuf, 0, sizeof(UsartType1.usartDMA_rxBuf));
      HAL_UART_Receive_DMA(&huart1, UsartType1.usartDMA_rxBuf, RECEIVELEN);
      Uart1_ReceiveBuffer_A_B = 1;
      Uart1_RX_Finish_B = 1;
    }

    //		HAL_UART_DMAStop(&huart1);
    //		temp=huart1.hdmarx->Instance->CNDTR;
    //		UsartType1.rx_len=RECEIVELEN - temp;
    //		UsartType1.Flag_Receive=1;
    //		HAL_UART_Receive_DMA(&huart1,UsartType1.usartDMA_rxBuf,RECEIVELEN);
    //		Usart1SendData_DMA("shoudao\r\n");
  }
}
/* USER CODE END 1 */

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
