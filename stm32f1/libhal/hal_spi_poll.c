/**
  ******************************************************************************
  * @file    hal_spi_poll.c
  * @author  lzh
  * @version 
  * @date    
  * @brief   This file provides SPI-POLL HAL functions.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hal_spi_poll.h"
#include "stm32f10x_spi.h"

/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Transmits a message. 
  * @param  tx:  pointer to transmit buffer.
  * @param  rx:  pointer to receive buffer.
  * @param  len: specifies the length of a message to be transmitted. 
  * @retval None
  */
void hal_spi_poll_write(uint16_t len, uint8_t *tx, uint8_t *rx)
{
    int i;
    for (i = 0; i < len; i++)
    {
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == 0);
        SPI_I2S_SendData(SPI1, *(tx + i));
        while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == 0);
        *(rx + i) = SPI_I2S_ReceiveData(SPI1);
    }
}

/**********************************END OF FILE*********************************/
