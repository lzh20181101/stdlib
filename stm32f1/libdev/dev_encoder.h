/**
  ******************************************************************************
  * @file    dev_encoder.h
  * @author  lzh
  * @version 
  * @date    11/1/2018
  * @brief   This file provides encoder driver function prototypes.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEV_ENCODER_H
#define __DEV_ENCODER_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/

/* Public typedef ------------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/
/* Public macro --------------------------------------------------------------*/

/* Public variables declarations ---------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
void dev_encoder_read(float *pangle);
#ifdef __cplusplus
}
#endif

#endif	/* __DEV_ENCODER_H */

/**********************************END OF FILE*********************************/

