/**
  ******************************************************************************
  * @file    hal_usart_dma.c
  * @author  lzh
  * @version 
  * @date    11/1/2018
  * @brief   This file provides USART-DMA HAL functions.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hal_usart_dma.h"

#include "stm32f10x_dma.h"

#include "string.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define HAL_USART1_DMA_BufferSize      3
/* Private macro -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t hal_usart1_dma_buffer_tx[HAL_USART1_DMA_BufferSize];
uint8_t hal_usart1_dma_buffer_rx[HAL_USART1_DMA_BufferSize];
/* Private function prototypes -----------------------------------------------*/
static void hal_usart1_dma_config(void);
static void hal_usart2_dma_config(void);
static void hal_usart3_dma_config(void);
static void hal_uart4_dma_config(void);
static void hal_uart5_dma_config(void);
/* Public functions ----------------------------------------------------------*/

/**
  * @brief   Initializes the USARTx-DMAx according to hal_usartx_dma_config() or 
  *          hal_uartx_dma_config().
  * @param   USARTx: where x can be 1 to 3 or (UART4 or UART5) to select the 
  *                USART peripheral.
  * @retval  None   
  */
void hal_usart_dma_init(USART_TypeDef *USARTx)
{
    if (USARTx == USART1)
    {
        hal_usart1_dma_config();
    }
    else if (USARTx == USART2)
    {
        hal_usart2_dma_config();
    }
    else if (USARTx == USART3)
    {
        hal_usart3_dma_config();
    }
    else if (USARTx == UART4)
    {
        hal_uart4_dma_config();
    }
    else if (USARTx == UART5)
    {
        hal_uart5_dma_config();
    }
    else
    {
        /* User can add here some code to deal with parameter false */
    }
}

/**
  * @brief   Transmits a message by USART-DMA(block).  
  * @param   USARTx: where x can be 1 to 3 or (UART4 or UART5) to select the 
  *                USART peripheral.
  * @param   len: specifies the length of a message to be transmitted.
  * @param   ptx: pionter to the buffer where  message is transmitted.
  * @param   prx: pointer to the buffer where  message is received. 
  * @retval  None  
  */
void hal_usart_dma_write_block(USART_TypeDef *USARTx, uint16_t len, uint8_t *ptx, uint8_t *prx)
{
    if (USARTx == USART1)
    {
        DMA_Cmd(DMA1_Channel4, DISABLE);
        DMA_Cmd(DMA1_Channel5, DISABLE);
        memcpy(hal_usart1_dma_buffer_tx, ptx, len);
        DMA_SetCurrDataCounter(DMA1_Channel4, len);
        DMA_SetCurrDataCounter(DMA1_Channel5, len);
        DMA_Cmd(DMA1_Channel4, ENABLE);
        DMA_Cmd(DMA1_Channel5, ENABLE);
        while (!hal_usart_dma_istxcp(USART1));
        memcpy(prx, hal_usart1_dma_buffer_rx, len);
    }
    else if (USARTx == USART2)
    {}
    else if (USARTx == USART3)
    {}
    else if (USARTx == UART4)
    {}
    else if (USARTx == UART5)
    {}
    else
    {
        /* User can add here some code to deal with parameter false */
    }
}

/**
  * @brief  Check whether transmission is complete. 
  * @param  USARTx: where x can be 1 to 3 or (UART4 or UART5) to select the 
  *                USART peripheral.
  * @retval Indicates whether transmission was complete. 
  *         @arg 0: not complete
  *         @arg 1: complete
  */
uint8_t hal_usart_dma_istxcp(USART_TypeDef *USARTx)
{
    if (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == SET)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Initializes the USART1-DMA1 
  * @param   None  
  * @retval  None
  */
static void hal_usart1_dma_config(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    /*!< USART_tx DMA configuration */
    DMA_DeInit(DMA1_Channel4);
    DMA_InitStructure.DMA_BufferSize = HAL_USART1_DMA_BufferSize;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)(hal_usart1_dma_buffer_tx);
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(USART1->DR);
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_Init(DMA1_Channel4, &DMA_InitStructure);
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

    /*!< USART_rx DMA configuration */
    DMA_DeInit(DMA1_Channel5);
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)(hal_usart1_dma_buffer_rx);
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    DMA_Init(DMA1_Channel5, &DMA_InitStructure);
    USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);

    DMA_Cmd(DMA1_Channel4, ENABLE);
    DMA_Cmd(DMA1_Channel5, ENABLE);
}

/**
  * @brief   Initializes the USART2-DMAx 
  * @param   None  
  * @retval  None
  */
static void hal_usart2_dma_config(void)
{

}

/**
  * @brief   Initializes the USART3-DMAx 
  * @param   None  
  * @retval  None
  */
static void hal_usart3_dma_config(void)
{

}

/**
  * @brief   Initializes the UART4-DMAx 
  * @param   None  
  * @retval  None
  */
static void hal_uart4_dma_config(void)
{

}

/**
  * @brief   Initializes the UART5-DMAx 
  * @param   None  
  * @retval  None
  */
static void hal_uart5_dma_config(void)
{

}


/**********************************END OF FILE*********************************/
