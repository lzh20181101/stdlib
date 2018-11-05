/**
  ******************************************************************************
  * @file    hal_spi_dma.c
  * @author  lzh
  * @version 
  * @date    
  * @brief   This file provides SPI-DMA HAL functions.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hal_spi_dma.h"
#include "stm32f10x_spi.h"
#include "stm32f10x_dma.h"

#include <string.h>

/* Private define ------------------------------------------------------------*/
#define HAL_SPI1_DMA_BufferSize      4
/* Public variables ----------------------------------------------------------*/
uint8_t hal_spi1_dma_buffer_tx[HAL_SPI1_DMA_BufferSize];
uint8_t hal_spi1_dma_buffer_rx[HAL_SPI1_DMA_BufferSize];

/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Initializes SPIx-DMAx interface.(SPI1-DMA1)  
  * @param  None 
  * @retval None
  */
void hal_spi_dma_init(void)
{
    DMA_InitTypeDef  DMA_InitStructure;

    DMA_DeInit(DMA1_Channel3);
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&(SPI1->DR);
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)hal_spi1_dma_buffer_tx;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
    DMA_InitStructure.DMA_BufferSize = HAL_SPI1_DMA_BufferSize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel3, &DMA_InitStructure);
    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx, ENABLE);

    DMA_DeInit(DMA1_Channel2);
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)hal_spi1_dma_buffer_rx;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_Init(DMA1_Channel2, &DMA_InitStructure);
    SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Rx, ENABLE);
}

/**
  * @brief  Transmits a message by SPI-DMA(block). 
  * @param  len: specifies the length of a message to be transmitted. 
  * @param  ptx: pionter of the message to be transmitted.
  * @param  prx: pointer of the message to be received.
  * @retval None
  */
void hal_spi_dma_write_block(uint16_t len, uint8_t *ptx, uint8_t *prx)
{
    memcpy(hal_spi1_dma_buffer_tx, ptx, len);
    DMA_Cmd(DMA1_Channel3, DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel3, len);
    DMA_Cmd(DMA1_Channel2, DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel2, len);
    DMA_Cmd(DMA1_Channel2, ENABLE);
    DMA_Cmd(DMA1_Channel3, ENABLE);
    while (!hal_spi_dma_istxcp());
    memcpy(prx, hal_spi1_dma_buffer_rx, len);
}

/**
  * @brief  Transmits a message by SPI-DMA(unblock). 
  * @param  len: specifies the length of a message to be transmitted. 
  * @param  ptx: pionter of the message to be transmitted.
  * @param  prx: pointer of the message to be received.
  * @retval None
  */
void hal_spi_dma_write_unblock(uint16_t len, uint8_t *ptx)
{
    memcpy(hal_spi1_dma_buffer_tx, ptx, len);
    DMA_Cmd(DMA1_Channel3, DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel3, len);
    DMA_Cmd(DMA1_Channel2, DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel2, len);
    DMA_Cmd(DMA1_Channel2, ENABLE);
    DMA_Cmd(DMA1_Channel3, ENABLE);
//  while (!hal_spi_dma_istxcp());
//  memcpy(prx, SPI_Buffer_Rx, len);
}

/**
  * @brief  irq handle function which is used to receives messages. 
  *         call it in SPI1_IRQHandler().
  * @param  len: specifies the length of a message to be transmitted. 
  * @param  prx: pointer of the message to be received.
  * @retval None
  */
void hal_spi_dma_write_unblock_irq(uint16_t len, uint8_t *prx)
{
    if (SPI_I2S_GetITStatus(SPI1, SPI_I2S_IT_TXE) == SET)
    {
        SPI_I2S_ClearITPendingBit(SPI1, SPI_I2S_IT_TXE);
        if (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == RESET)
        {
            memcpy(prx, hal_spi1_dma_buffer_rx, len);
        }
    }
}

//uint8_t hal_spi_dma_istxcp(void)
//{
//    if (DMA_GetFlagStatus(DMA1_FLAG_TC3) == SET)
//        return 1;
//    else
//        return 0;
//}

/**
  * @brief  Check whether transmission is complete. 
  * @param  None 
  * @retval Indicates whether transmission was complete. 
  *         @arg 0: not complete
  *         @arg 1: complete
  */
uint8_t hal_spi_dma_istxcp(void)
{
    if ((SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == SET)
        && (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == RESET))
        return 1;
    else
        return 0;
}

/**
  * @brief  Check whether reception is complete. 
  * @param  None 
  * @retval Indicates whether reception was complete. 
  *         @arg 0: not complete
  *         @arg 1: complete
  */
uint8_t hal_spi_dma_isrxcp(void)
{
    if (DMA_GetFlagStatus(DMA1_FLAG_TC2) == SET)
        return 1;
    else
        return 0;
}

/**********************************END OF FILE*********************************/
