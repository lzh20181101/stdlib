/**
  ******************************************************************************
  * @file    hal_can.c
  * @author  lzh
  * @version 
  * @date    
  * @brief   This file provides can HAL functions.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hal_can.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include <string.h>

/* Private define ------------------------------------------------------------*/
#define HAL_CAN_PIN_TX  GPIO_Pin_12
#define HAL_CAN_GPIO_TX GPIOA

#define HAL_CAN_PIN_RX  GPIO_Pin_11
#define HAL_CAN_GPIO_RX GPIOA

/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Initializes the CANx(CAN1). 
  * @param  None 
  * @retval None
  */
void hal_can_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    CAN_InitTypeDef CAN_InitStructure;
    CAN_FilterInitTypeDef CAN_FilterInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    GPIO_InitStructure.GPIO_Pin = HAL_CAN_PIN_TX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(HAL_CAN_GPIO_TX, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = HAL_CAN_PIN_RX;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(HAL_CAN_GPIO_RX, &GPIO_InitStructure);

    CAN_DeInit(CAN1);
    CAN_InitStructure.CAN_TTCM = DISABLE;
    CAN_InitStructure.CAN_ABOM = DISABLE;
    CAN_InitStructure.CAN_AWUM = DISABLE;
    CAN_InitStructure.CAN_NART = ENABLE;
    CAN_InitStructure.CAN_RFLM = DISABLE;
    CAN_InitStructure.CAN_TXFP = DISABLE;
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_2tq;
    CAN_InitStructure.CAN_Prescaler = 6;
    CAN_Init(CAN1, &CAN_InitStructure);

    CAN_FilterInitStructure.CAN_FilterNumber = 0x00;
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
    CAN_FilterInitStructure.CAN_FilterIdLow =  0x0000;
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_FilterFIFO0;
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
    CAN_FilterInit(&CAN_FilterInitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}

/**
  * @brief  Initiates the transmission of a message.  
  * @param  CANx:   where x can be 1 or 2 to to select the CAN peripheral. 
  * @param  StdId:  Standard identifier. 
  *                 This parameter can be a value between 0 to 0x7FF. 
  * @param  ExtId:  Extended identifier. 
  *                 This parameter can be a value between 0 to 0x1FFFFFFF. 
  * @param  IDE:    Type of identifier. 
  *                 This parameter can be one of the following values:
  *                 @arg 0: Standard ID
  *                 @arg 1: Extended ID
  * @param  RTR:    Type of frame. 
  *                 This parameter can be one of the following values:
  *                 @arg 0: Data frame
  *                 @arg 1: Remote frame
  * @param  DLC:    Length of the frame. 
  *                 This parameter can be a value between 0 to 8. 
  * @param  pdata:  Pointer of data to be transmitted. 
  *                 It ranges from 0 to 0xFF. 
  * @retval Initiates whether the transmission was successful. 
  *                 @arg 0: successful
  *                 @arg 1: failed due to the lack of an empty mailbox
  */
uint8_t hal_can_write(CAN_TypeDef *CANx, uint32_t StdId, uint32_t ExtId, uint8_t isExtId, uint8_t isRTF, uint8_t DLC, uint8_t *pdata)
{
    uint8_t ret;
    CanTxMsg TxMessage;
    TxMessage.StdId = StdId;
    TxMessage.ExtId = ExtId;
    TxMessage.RTR = isRTF ? CAN_RTR_Remote : CAN_RTR_Data;
    TxMessage.IDE = isExtId ? CAN_Id_Extended : CAN_Id_Standard;
    TxMessage.DLC = DLC;
    memcpy(TxMessage.Data, pdata, DLC);
    ret = CAN_Transmit(CANx, &TxMessage);
    if (ret == CAN_TxStatus_NoMailBox)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/**
  * @brief  Receives a message.  
  * @param  CANx:   where x can be 1 or 2 to to select the CAN peripheral. 
  * @param  pStdId: pointer to standard identifier. 
  *                 Standard identifier can be a value between 0 to 0x7FF. 
  * @param  pExtId: pointer to extended identifier. 
  *                 Extended identifier can be a value between 0 to 0x1FFFFFFF. 
  * @param  pIDE:   pointer to type of identifier. 
  *                 Type of identifier can be one of the following values:
  *                 @arg 0: Standard ID
  *                 @arg 1: Extended ID
  * @param  pRTR:   pointer to type of frame. 
  *                 Type of frame can be one of the following values:
  *                 @arg 0: Data frame
  *                 @arg 1: Remote frame
  * @param  pDLC:   pointer to length of the frame. 
  *                 Length of the frame can be a value between 0 to 8. 
  * @param  pdata:  Pointer of data to be received. 
  *                 Data ranges from 0 to 0xFF. 
  * @retval None
  */
void hal_can_read(CAN_TypeDef *CANx, uint16_t *pStdId, uint32_t *pExtId, uint8_t *pisExtId, uint8_t *pisRTF, uint8_t *pDLC, uint8_t *pdata, uint8_t *pFMI)
{
    CanRxMsg RxMessage;
    CAN_Receive(CANx, CAN_FIFO0, &RxMessage);
    if (pStdId != NULL)
    {
        *pStdId = RxMessage.StdId;
    }
    if (pExtId != NULL)
    {
        *pExtId = RxMessage.ExtId;
    }
    if (pisExtId != NULL)
    {
        if (RxMessage.IDE == CAN_Id_Standard)
        {
            *pisExtId = 0;
        }
        else
        {
            *pisExtId = 1;
        }
    }
    if (pisRTF != NULL)
    {
        if (RxMessage.RTR == CAN_RTR_Remote)
        {
            *pisRTF = 1;
        }
        else
        {
            *pisRTF = 0;
        }
        *pDLC = RxMessage.DLC;
    }
    if (pFMI != NULL)
    {
        *pFMI = RxMessage.FMI;
    }
    if (pdata != NULL)
    {
        memcpy(pdata, RxMessage.Data, *pDLC);
    }
}

//void hal_can_read(CAN_TypeDef *CANx, uint16_t *pStdId, uint8_t *pisRTF, uint8_t *pDLC, uint8_t *pdata)
//{
//    CanRxMsg RxMessage;
//    CAN_Receive(CANx, CAN_FIFO0, &RxMessage);
//    *pStdId = RxMessage.StdId;
//    if (RxMessage.RTR == CAN_RTR_Remote)
//    {
//        *pisRTF = 1;
//    }
//    else
//    {
//        *pisRTF = 0;
//    }
//    *pDLC = RxMessage.DLC;
//    memcpy(pdata, RxMessage.Data, *pDLC);
//}

/**********************************END OF FILE*********************************/


