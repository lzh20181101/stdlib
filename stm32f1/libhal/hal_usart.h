/**
  ******************************************************************************
  * @file    hal_usart.h
  * @author  lzh
  * @version 
  * @date    10/31/2018
  * @brief   This file provides USART HAL functions prototypes.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_USART_H
#define __HAL_USART_H

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
void hal_usart_init(USART_TypeDef* USARTx);
#ifdef __cplusplus
}
#endif

#endif	/* __HAL_USART_H */

/**********************************END OF FILE*********************************/

