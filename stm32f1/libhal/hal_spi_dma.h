/**
  ******************************************************************************
  * @file    hal_spi_dma.h
  * @author  lzh
  * @version 
  * @date    
  * @brief   This file provides SPI-DMA HAL functions prototypes.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_SPI_DMA_H
#define __HAL_SPI_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Public define -------------------------------------------------------------*/
/* Public variables declarations ---------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
void hal_spi_dma_init(void);
void hal_spi_dma_write_block(uint16_t len, uint8_t *ptx, uint8_t *prx);
void hal_spi_dma_write_unblock(uint16_t len, uint8_t *ptx);
void hal_spi_dma_write_unblock_irq(uint16_t len, uint8_t *prx);
uint8_t hal_spi_dma_istxcp(void);
uint8_t hal_spi_dma_isrxcp(void); 

#ifdef __cplusplus
}
#endif

#endif  /* __HAL_SPI_DMA_H */

/**********************************END OF FILE*********************************/
