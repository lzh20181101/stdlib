/**
  ******************************************************************************
  * @file    hal_ssi.c
  * @author  lzh
  * @version 
  * @date    11/1/2018
  * @brief   This file provides SSI HAL functions.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "hal_ssi.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define HAL_SSI_PIN_CLK     GPIO_Pin_15
#define HAL_SSI_GPIO_CLK    GPIOB

#define HAL_SSI_PIN_DATA    GPIO_Pin_14
#define HAL_SSI_GPIO_DATA   GPIOB

#define HAL_SSI_CLK_SET     HAL_SSI_GPIO_CLK->BSRR = HAL_SSI_PIN_CLK
#define HAL_SSI_CLK_CLR     HAL_SSI_GPIO_CLK->BRR = HAL_SSI_PIN_CLK

#define HAL_SSI_DATA_IN     HAL_SSI_GPIO_DATA->IDR & HAL_SSI_PIN_DATA
/* Private macro -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void hal_ssi_delay_us(uint16_t us); 
/* Public functions ----------------------------------------------------------*/

/**
  * @brief   Initializes the simulated SSI.
  * @param   None
  * @retval  None
  */
void hal_ssi_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = HAL_SSI_PIN_CLK;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(HAL_SSI_GPIO_CLK, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = HAL_SSI_PIN_DATA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(HAL_SSI_GPIO_DATA, &GPIO_InitStructure);

    HAL_SSI_CLK_SET;
}

/**
  * @brief   Receives n bits data by SSI.
  * @param   nbit: n bits data.
  * @retval  n-bit-data
  */
uint32_t hal_ssi_readbit(uint8_t nbit)
{
    uint32_t temp = 0; uint8_t i;
    HAL_SSI_CLK_CLR;
    hal_ssi_delay_us(1);
    for (i = nbit; i > 0; i--)
    {
        HAL_SSI_CLK_SET;
        hal_ssi_delay_us(1);

        HAL_SSI_CLK_CLR;
        temp <<= 1;
        if ((HAL_SSI_DATA_IN) != 0)
        {
            temp |= 0x01;
        }
        hal_ssi_delay_us(1);
    }
    HAL_SSI_CLK_SET;

    return temp;
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   delay function
  * @param   us: delay time in us(Inaccurate)
  * @retval  None
  */
static void hal_ssi_delay_us(uint16_t us)
{
    while (us--);
}

/**********************************END OF FILE*********************************/
