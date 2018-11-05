/**
  ******************************************************************************
  * @file    dev_ADS8688.c
  * @author  lzh
  * @version 
  * @date    10/26/2018
  * @brief   This file provides ads8688 driver functions. 
  * @note    data is set at falling edge of SCLK
  *          MSB is transmitted first.
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "dev_ADS8688.h"
#include <string.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "hal_spi_dma.h"
#include "hal_spi_poll.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define DEV_ADS8688_GPIO_CS     GPIOA
#define DEV_ADS8688_GPIO_RST    GPIOA
#define DEV_ADS8688_PIN_CS      GPIO_Pin_4
#define DEV_ADS8688_PIN_RST     GPIO_Pin_3
/* Private macro -------------------------------------------------------------*/

/* Public variables ----------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void dev_ads8688_hd_config(void);
void dev_ads8688_cs(uint8_t state);
void dev_ads8688_hw_rst(void);
/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Initializes ads8688. 
  * @param  None 
  * @retval None
  */
void dev_ads8688_init(void)
{
    uint8_t i = 0;
    dev_ads8688_hd_config();
    dev_ads8688_hw_rst();
    dev_ads8688_cmd(DEV_ADS8688_CMD_RST);
//  dev_ads8688_cmd(DEV_ADS8688_CMD_AUTORST);
//  for (i = 0; i < 200; i++);
//  dev_ads8688_prog_write(DEV_ADS8688_PROG_ADDR_ATUOSEQEN, DEV_ADS8688_PROG_ATUOSEQEN_CHxEN(7));
//  dev_ads8688_prog_read(DEV_ADS8688_PROG_ADDR_CMDREAD, &i);
    dev_ads8688_prog_write(DEV_ADS8688_PROG_ADDR_ATUOSEQEN,  DEV_ADS8688_PROG_ATUOSEQEN_CHxEN(4) | DEV_ADS8688_PROG_ATUOSEQEN_CHxEN(5));
    dev_ads8688_prog_read(DEV_ADS8688_PROG_ADDR_ATUOSEQEN, &i);
    dev_ads8688_cmd(DEV_ADS8688_CMD_AUTORST);
//  dev_ads8688_cmd(DEV_ADS8688_CMD_MANCHx(7));
//
//  dev_ads8688_prog_read(DEV_ADS8688_PROG_ADDR_CMDREAD, &i);
}

/**
  * @brief  Command register Write Operation. 
  * @param  cmd: command used to set the operating modes of the ads8688. 
  * @retval None
  */
void dev_ads8688_cmd(uint8_t cmd)
{

    uint8_t tx[4] = { cmd, 0x00, 0x00, 0x00 };
    uint8_t rx[4] = { 0x00, 0x00, 0x00, 0x00 };
    dev_ads8688_cs(ENABLE);
    hal_spi_dma_write_block(0x04, tx, rx);
//  hal_spi_poll_write(0x04, tx, rx);
    dev_ads8688_cs(DISABLE);
}

/**
  * @brief  Program register Write Operation. 
  * @param  addr: Program Register address 
  * @param  data: data written into Program Register.
  * @retval Initiates whether the write was successful. 
  *         @arg 0: successful
  *         @arg 1: failed
  */
uint8_t dev_ads8688_prog_write(uint8_t addr, uint8_t data)
{
    uint8_t tx[4] = { addr | DEV_ADS8688_PROG_WR, data, 0x00, 0x00 };
    uint8_t rx[4] = { 0x00, 0x00, 0x00, 0x00 };
    dev_ads8688_cs(ENABLE);
    hal_spi_dma_write_block(0x04, tx, rx);
//  hal_spi_poll_write(0x04, tx, rx);
    dev_ads8688_cs(DISABLE);
    if (rx[2] == data)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

/**
  * @brief  Program register Read Operation. 
  * @param  addr:   Program Register address 
  * @param  pdata:  data read from Program Register. 
  * @retval None
  */
void dev_ads8688_prog_read(uint8_t addr, uint8_t *pdata)
{
    uint8_t tx[4] = { addr | DEV_ADS8688_PROG_RD, 0x00, 0x00, 0x00 };
    uint8_t rx[4] = { 0x00, 0x00, 0x00, 0x00 };
    dev_ads8688_cs(ENABLE);
    hal_spi_dma_write_block(0x04, tx, rx);
//  hal_spi_poll_write(0x04, tx, rx);
    dev_ads8688_cs(DISABLE);
    *pdata = rx[2];
}

/**
  * @brief  Conversion result Read Operation. 
  * @param  addr:   Program Register address 
  * @param  pdata:  Conversion result. 
  * @retval None
  */
void dev_ads8688_data_read(uint16_t *pdata)
{
    uint8_t tx[4] = { 0x00, 0x00, 0x00, 0x00 };
    uint8_t rx[4] = { 0x00, 0x00, 0x00, 0x00 };
    dev_ads8688_cs(ENABLE);
    hal_spi_dma_write_block(0x04, tx, rx);
//  hal_spi_poll_write(0x04, tx, rx);
    dev_ads8688_cs(DISABLE);
    *pdata = ((uint16_t)(rx[2]) << 8) | (uint16_t)(rx[3]);
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  ads8688 hardware configuration.  
  * @param  None 
  * @retval None
  */
static void dev_ads8688_hd_config(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = DEV_ADS8688_PIN_CS;
    GPIO_Init(DEV_ADS8688_GPIO_CS, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Pin = DEV_ADS8688_PIN_RST;
    GPIO_Init(DEV_ADS8688_GPIO_RST, &GPIO_InitStructure);

    GPIO_SetBits(DEV_ADS8688_GPIO_CS, DEV_ADS8688_PIN_CS);
    GPIO_SetBits(DEV_ADS8688_GPIO_RST, DEV_ADS8688_PIN_RST);
}

/**
  * @brief  ads8688 chip-select function(active low logic). 
  * @param  state:  select or deselect ads8688. 
  *         @arg ENABLE:    select
  *         @arg DISABLE:   deselect
  *  
  * @retval None
  */
__inline void dev_ads8688_cs(uint8_t state)
{
    if (state == ENABLE)
        GPIO_ResetBits(DEV_ADS8688_GPIO_CS, DEV_ADS8688_PIN_CS);
    else
        GPIO_SetBits(DEV_ADS8688_GPIO_CS, DEV_ADS8688_PIN_CS);
}

/**
  * @brief  Resets ads8688 and palces it into power down mode. 
  * @param  None 
  * @retval None
  */
__inline void dev_ads8688_hw_rst(void)
{
    uint8_t i = 0;
    GPIO_ResetBits(DEV_ADS8688_GPIO_RST, DEV_ADS8688_PIN_RST);
    for (i = 0; i < 5; i++);
    GPIO_SetBits(DEV_ADS8688_GPIO_RST, DEV_ADS8688_PIN_RST);
}

/**********************************END OF FILE*********************************/
