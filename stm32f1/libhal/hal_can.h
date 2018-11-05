/**
  ******************************************************************************
  * @file    hal_can.h
  * @author  lzh
  * @version 
  * @date    
  * @brief   This file provides can HAL functions prototypes.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __HAL_CAN_H
#define __HAL_CAN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_can.h"

/* Public function prototypes ------------------------------------------------*/
void hal_can_init(void);
uint8_t hal_can_write(CAN_TypeDef *CANx, uint32_t StdId, uint32_t ExtId, uint8_t isExtId, uint8_t isRTF, uint8_t DLC, uint8_t *pdata);
void hal_can_read(CAN_TypeDef *CANx, uint16_t *pStdId, uint32_t *pExtId, uint8_t *pisExtId, uint8_t *pisRTF, uint8_t *pDLC, uint8_t *pdata, uint8_t *pFMI);
//void hal_can_read(CAN_TypeDef *CANx, uint16_t *pStdId, uint8_t *pisRTF, uint8_t *pDLC, uint8_t *pdata);
#ifdef __cplusplus
}
#endif

#endif  /* __HAL_CAN_H */

/**********************************END OF FILE*********************************/
