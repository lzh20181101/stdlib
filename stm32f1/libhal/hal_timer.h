/**
  ******************************************************************************
  * @file    hal_timer.h
  * @author  lzh
  * @version 
  * @date    
  * @brief   This file provides timer HAL functions prototypes.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_TIMER_H
#define __HAL_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_tim.h"

/* Public function prototypes ------------------------------------------------*/
void hal_timer_init(TIM_TypeDef *TIMx);
void hal_timer_set(TIM_TypeDef *TIMx, uint16_t trigvalue);
void hal_timer_cmd(TIM_TypeDef *TIMx, FunctionalState NewState);
uint16_t hal_timer_getcnt(TIM_TypeDef *TIMx);

#ifdef __cplusplus
}
#endif

#endif  /* __HAL_timer_H */

/**********************************END OF FILE*********************************/
