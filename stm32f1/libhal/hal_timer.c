/**
  ******************************************************************************
  * @file    hal_timer.c
  * @author  lzh
  * @version 
  * @date    
  * @brief   This file provides ssi HAL functions prototypes.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hal_timer.h"

/* Private function prototypes -----------------------------------------------*/
static void hal_t1_config(void);
static void hal_t2_config(void);
static void hal_t3_config(void);
static void hal_t4_config(void);


/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Initializes the TIMx according to hal_tx_config().
  * @param  TIMx: where x can be 1 to 4 to select the TIM peripheral. 
  * @retval None
  */
void hal_timer_init(TIM_TypeDef *TIMx)
{
    if (TIMx == TIM1)
    {
        hal_t1_config();
    }
    else if (TIMx == TIM2)
    {
        hal_t2_config();
    }
    else if (TIMx == TIM3)
    {
        hal_t3_config();
    }
    else if (TIMx == TIM4)
    {
        /* TIM4 is used to generate alarm for canfestival*/
        hal_t4_config();
    }
    else
    {
        /* User can add here some code to deal with parameter false */
    }
}

/**
  * @brief  Sets the TIMx trigger value. 
  * @param  TIMx:       where x can be 1 to 4 to select the TIM peripheral. 
  * @param  trigvalue:  specifies the trigger value of TIMx. 
  *                     This parameter can be a value between 0x0000 to 0xFFFF.
  * @retval None
  */
void hal_timer_set(TIM_TypeDef *TIMx, uint16_t trigvalue)
{
    if (TIMx == TIM1)
    {
        /* User can add here some code */
    }
    else if (TIMx == TIM2)
    {
        /* User can add here some code */
    }
    else if (TIMx == TIM3)
    {
        /* User can add here some code */
    }
    else if (TIMx == TIM4)
    {
        TIM_SetAutoreload(TIM4, trigvalue - 1);
    }
    else
    {
        /* User can add here some code to deal with parameter false */
    }
}

/**
  * @brief  Enables or disables the specified TIM peripheral. 
  * @param  TIMx:       where x can be 1 to 4 to select the TIM peripheral. 
  * @param  NewState:   new state of the TIMx. 
  *                     @arg ENABLE: enable the TIMx
  *                     @arg DISABLE:disable the TIMx
  * @retval None
  */
void hal_timer_cmd(TIM_TypeDef *TIMx, FunctionalState NewState)
{
    if (TIMx == TIM1)
    {
        TIM_Cmd(TIM1, NewState);
    }
    else if (TIMx == TIM2)
    {
        TIM_Cmd(TIM2, NewState);
    }
    else if (TIMx == TIM3)
    {
        TIM_Cmd(TIM3, NewState);
    }
    else if (TIMx == TIM4)
    {
        TIM_Cmd(TIM4, NewState);
    }
    else
    {
        /* User can add here some code to deal with parameter false */
    }
}

/**
  * @brief  Gets the TIMx Counter value. 
  * @param  TIMx: where x can be 1 to 4 to select the TIM peripheral.
  * @retval TIMx Counter value.
  */
uint16_t hal_timer_getcnt(TIM_TypeDef *TIMx)
{
    if (TIMx == TIM1)
    {
        return TIM_GetCounter(TIM1);
    }
    else if (TIMx == TIM2)
    {
        return TIM_GetCounter(TIM2);
    }
    else if (TIMx == TIM3)
    {
        return TIM_GetCounter(TIM3);
    }
    else if (TIMx == TIM4)
    {
        return TIM_GetCounter(TIM4);
    }
    else
    {
        /* User can add here some code to deal with parameter false */
		return 0;
    }
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the TIM1. 
  * @param  None
  * @retval None
  */
static void hal_t1_config(void)
{
    /* User can add here some code to initialize TIM1 */
}

/**
  * @brief  Initializes the TIM2. 
  * @param  None
  * @retval None
  */
static void hal_t2_config(void)
{
    /* User can add here some code to initialize TIM2*/
}

/**
  * @brief  Initializes the TIM3. 
  * @param  None
  * @retval None
  */
static void hal_t3_config(void)
{
    /* User can add here some code to initialize TIM3*/
}

/**
  * @brief  Initializes the TIM4. 
  * @param  None
  * @retval None
  */
static void hal_t4_config(void)
{
    /* User can add here some code to initialize TIM4*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    /* Count up every microsecond
       T=(TIM_Period + 1)*(TIM_Prescaler + 1)/fTIMXCLK.*/
    TIM_TimeBaseInitStructure.TIM_Period = 9;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 71;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

    /* Auto-reoad register updates immediately after TIM_SetAutoreload() */
    TIM_ARRPreloadConfig(TIM4, DISABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM4, DISABLE);
}

/**********************************END OF FILE*********************************/
