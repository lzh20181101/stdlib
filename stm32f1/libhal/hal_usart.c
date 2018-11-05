/**
  ******************************************************************************
  * @file    hal_usart.c
  * @author  lzh
  * @version 
  * @date    10/31/2018
  * @brief   This file provides USARTS HAL functions.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hal_usart.h"

#include "stm32f10x_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define HAL_USART1_PIN_CK   GPIO_Pin_8
#define HAL_USART1_GPIO_CK  GPIOA

#define HAL_USART1_PIN_TX   GPIO_Pin_9
#define HAL_USART1_GPIO_TX  GPIOA

#define HAL_USART1_PIN_RX   GPIO_Pin_10
#define HAL_USART1_GPIO_RX  GPIOA

/* Private macro -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void hal_usart1_config(void);
static void hal_usart2_config(void);
static void hal_usart3_config(void);
static void hal_uart4_config(void);
static void hal_uart5_config(void);
/* Public functions ----------------------------------------------------------*/

/**
  * @brief   Initializes the USARTx according to hal_usartx_config() or 
  *          hal_uartx_config().
  * @param   USARTx: where x can be 1 to 3 or (UART4 or UART5) to select the 
  *                USART peripheral.
  * @retval  None
  */
void hal_usart_init(USART_TypeDef *USARTx)
{
    if (USARTx == USART1)
    {
        hal_usart1_config();
    }
    else if (USARTx == USART2)
    {
        hal_usart2_config();
    }
    else if (USARTx == USART3)
    {
        hal_usart3_config();
    }
    else if (USARTx == UART4)
    {
        hal_uart4_config();
    }
    else if (USARTx == UART5)
    {
        hal_uart5_config();
    }
    else
    {
        /* User can add here some code to deal with parameter false */
    }
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Initializes the USART1. 
  * @param   None
  * @retval  None
  */
static void hal_usart1_config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef  USART_InitStructure;
    USART_ClockInitTypeDef USART_ClockInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = HAL_USART1_PIN_CK;
    GPIO_Init(HAL_USART1_GPIO_CK, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = HAL_USART1_PIN_TX;
    GPIO_Init(HAL_USART1_GPIO_TX, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = HAL_USART1_PIN_RX;
    GPIO_Init(HAL_USART1_GPIO_RX, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 600000;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_0_5;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);

    USART_ClockInitStructure.USART_Clock = USART_Clock_Enable;
    USART_ClockInitStructure.USART_CPHA = USART_CPOL_High;
    USART_ClockInitStructure.USART_CPOL = USART_CPHA_1Edge;
    USART_ClockInitStructure.USART_LastBit = USART_LastBit_Enable;
    USART_ClockInit(USART1, &USART_ClockInitStructure);

    USART_Cmd(USART1, ENABLE);
}

/**
  * @brief   Initializes the USART2. 
  * @param   None
  * @retval  None
  */
static void hal_usart2_config(void)
{

}

/**
  * @brief   Initializes the USART3. 
  * @param   None
  * @retval  None
  */
static void hal_usart3_config(void)
{

}

/**
  * @brief   Initializes the UART4. 
  * @param   None
  * @retval  None
  */
static void hal_uart4_config(void)
{

}

/**
  * @brief   Initializes the UART5. 
  * @param   None
  * @retval  None
  */
static void hal_uart5_config(void)
{

}

/**********************************END OF FILE*********************************/
