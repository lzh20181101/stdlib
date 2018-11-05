/**
  ******************************************************************************
  * @file    dev_encoder.c
  * @author  lzh
  * @version 
  * @date    11/1/2018
  * @brief   This file provides encoder driver functions.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "dev_encoder.h"
#include "hal_ssi.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static uint32_t GraytoNatural(uint32_t x);
/* Public functions ----------------------------------------------------------*/

/**
  * @brief   read angle from encoder
  * @param   pangle: pointer to the var where angle is saved.
  * @retval  None
  */
void dev_encoder_read(float *pangle)
{
    uint32_t binary_code = GraytoNatural(hal_ssi_readbit(21));
    *pangle = (float)(binary_code) / 2097152 * 360;
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Convert Gray code to natural code. 
  * @param   x: Gray code
  * @retval  natural code
  */
static uint32_t GraytoNatural(uint32_t gary)
{
    uint32_t natural = gary;
    while (gary != 0)
    {
        gary = gary >> 1;
        natural ^= gary;
    }
    return natural;
}


/**********************************END OF FILE*********************************/
