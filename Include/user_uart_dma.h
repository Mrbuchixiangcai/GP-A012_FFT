#ifndef USER_UART_DMA_A_H
#define USER_UART_DMA_A_H

#include "stm32f0xx_hal.h"


typedef unsigned         char uint8_t;
typedef unsigned short   int  uint16_t;
typedef unsigned         int  uint32_t;

#define uchar uint8_t
#define uint  uint16_t
#define ulong uint32_t

#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t


extern UART_HandleTypeDef huart1;
extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart1_tx;

void User_USART1_UART_Init(void);



extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_rx;
extern DMA_HandleTypeDef hdma_usart2_tx;

void User_USART2_UART_Init(void);



HAL_StatusTypeDef User_UART_Transmit_DMAStop(UART_HandleTypeDef *huart);
HAL_StatusTypeDef User_UART_Receive_DMAStop(UART_HandleTypeDef *huart);


void HAL_UART_MspInit(UART_HandleTypeDef* huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart);


#endif








