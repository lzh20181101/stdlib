/**
  ******************************************************************************
  * @file    hal_ssi.h
  * @author  lzh
  * @version 
  * @date    11/1/2018
  * @brief   This file provides SSI HAL functions prototypes.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_SSI_H
#define __HAL_SSI_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
/* Public typedef ------------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public macro --------------------------------------------------------------*/

/* Public variables declarations ---------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
void hal_ssi_init(void);
uint32_t hal_ssi_readbit(uint8_t nbit);

#ifdef __cplusplus
}
#endif

#endif	/* __HAL_SSI_H */

/**********************************END OF FILE*********************************/

