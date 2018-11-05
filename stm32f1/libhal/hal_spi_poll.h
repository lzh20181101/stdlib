/**
  ******************************************************************************
  * @file    hal_spi_poll.h
  * @author  lzh
  * @version 
  * @date    
  * @brief   This file provides SPI-POLL HAL functions prototypes.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_SPI_POLL_H
#define __HAL_SPI_POLL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Public function prototypes ------------------------------------------------*/
void hal_spi_poll_write(uint16_t len, uint8_t *tx, uint8_t *rx);

#ifdef __cplusplus
}
#endif

#endif  /* __HAL_SPI_POLL_H */

/**********************************END OF FILE*********************************/
