/**
  ******************************************************************************
  * @file    hal_nvic.c
  * @author  lzh
  * @version 
  * @date    
  * @brief   This file provides NVIC HAL functions.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hal_nvic.h"
#include "misc.h"

/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Sets NVIC priority group.
  * @param  None. 
  * @retval None
  */
void hal_nvic_init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
}

/**********************************END OF FILE*********************************/
