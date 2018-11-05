/**
  ******************************************************************************
  * @file    hal_usart_dma.h
  * @author  lzh
  * @version 
  * @date    11/1/2018
  * @brief   This file provides USART-DMA HAL functions prototypes.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_USART_DMA_H
#define __HAL_USART_DMA_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_usart.h"
/* Public typedef ------------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public macro --------------------------------------------------------------*/

/* Public variables declarations ---------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
void hal_usart_dma_init(USART_TypeDef *USARTx);
void hal_usart_dma_write_block(USART_TypeDef *USARTx, uint16_t len, uint8_t *ptx, uint8_t *prx);
uint8_t hal_usart_dma_istxcp(USART_TypeDef *USARTx);

#ifdef __cplusplus
}
#endif

#endif	/* __HAL_USART_DMA_H */

/**********************************END OF FILE*********************************/

