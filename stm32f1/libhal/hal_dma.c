/**
  ******************************************************************************
  * @file    hal_dma.c
  * @author  lzh
  * @version 
  * @date    
  * @brief   This file provides DMA HAL functions.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hal_dma.h"
#include "stm32f10x_rcc.h"

/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Initializes the DMA.
  * @param  None. 
  * @retval None
  */
void hal_dma_init(void)
{
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
}

/**********************************END OF FILE*********************************/
