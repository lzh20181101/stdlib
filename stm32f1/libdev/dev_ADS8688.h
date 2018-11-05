/**
  ******************************************************************************
  * @file    dev_ADS8688.h
  * @author  lzh
  * @version 
  * @date    10/26/2018
  * @brief   This file provides ads8688 driver function prototypes.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEV_ADS8688_H
#define __DEV_ADS8688_H

#ifdef __cplusplus
extern "C"
{
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
/* Public typedef ------------------------------------------------------------*/
/* Public define -------------------------------------------------------------*/

/** 
 **************** ADS8688 command Register Description *************************
 */
#define DEV_ADS8688_CMD_NOOP        0x00    /*!< Continued Operation */
#define DEV_ADS8688_CMD_STDBY       0x82    /*!< Standby */
#define DEV_ADS8688_CMD_PWRDN       0x83    /*!< Power Down */
#define DEV_ADS8688_CMD_RST         0x85    /*!< Reset program registers */
#define DEV_ADS8688_CMD_AUTORST     0xA0    /*!< Auto Ch. Sequence with Reset */
#define DEV_ADS8688_CMD_MANCHx(x)   (0xC0 | (4 * x))    /*!< Manual Ch x Selection */
#define DEV_ADS8688_CMD_MANCHAUX    0xE0    /*!< Manual AUX Selection */
/**
 *******************************************************************************
 */

/**
 ******************* ADS8688 Program Register Description **********************
 */

/**
 *      ****************   Program Register address   ****************
 */
#define DEV_ADS8688_PROG_ADDR_ATUOSEQEN     0x02    /*!< AUTO_SEQ_EN */
#define DEV_ADS8688_PROG_ADDR_CHPWRDN       0x04    /*!< Channel Power Down */
#define DEV_ADS8688_PROG_ADDR_FS            0x06    /*!< Feature Select */
#define DEV_ADS8688_PROG_ADDR_CHxRAN(x)     (0x0A + 2 * x) /*!< Channel x Input Range */
#define DEV_ADS8688_PROG_ADDR_CMDREAD       0x7E    /*!< Command Read Back */

#define DEV_ADS8688_PROG_WR     0x01    /*!< Program Register Write */
#define DEV_ADS8688_PROG_RD     0x00    /*!< Program Register Read */
#define DEV_ADS8688_PROG_MASK   0xFE    /*!< Program Register Mask */

/**
 *      **************  Program Register configuration  **************
 */
#define DEV_ADS8688_PROG_ATUOSEQEN_CHxEN(x)     (1 << x)  /*!< AUTO_SEQ_CHx_EN */

#define DEV_ADS8688_PROG_CHxPWRDN(x)            (1 << x)  /*!< CHx Power Down */

#define DEV_ADS8688_PROG_PLUSMINUS25VREF        0x00    /*!< Input range ¡À2.5 x VREF */
#define DEV_ADS8688_PROG_PLUSMINUS125VREF       0x01    /*!< Input range ¡À1.25 x VREF */
#define DEV_ADS8688_PROG_PLUSMINUS0625VREF      0x02    /*!< Input range ¡À0.625 x VREF */
#define DEV_ADS8688_PROG_PLUS25VREF             0x05    /*!< Input range 0-2.5 x VREF */
#define DEV_ADS8688_PROG_PLUS125VREF            0x06    /*!< Input range 0-1.25 x VREF */

#define DEV_ADS8688_PROG_DEVICEID0              0x00    /*!< Device 0 in daisy-chain mode */
#define DEV_ADS8688_PROG_DEVICEID1              0x40    /*!< Device 1 in daisy-chain mode */
#define DEV_ADS8688_PROG_DEVICEID2              0x80    /*!< Device 2 in daisy-chain mode */
#define DEV_ADS8688_PROG_DEVICEID3              0xC0    /*!< Device 3 in daisy-chain mode */
#define DEV_ADS8688_PROG_DEVICEID_MASK          0xC0    /*!< Device ID mask */
#define DEV_ADS8688_PROG_SDOFMT_L               0x00    /*!< SDO Format Conversion result + Pulled Low */
#define DEV_ADS8688_PROG_SDOFMT_CL              0x01    /*!< SDO Format Conversion result + Pulled Low */
#define DEV_ADS8688_PROG_SDOFMT_CDL             0x02    /*!< SDO Format Conversion result + Channel Address + Device Address + Pulled Low */
#define DEV_ADS8688_PROG_SDOFMT_CDLI            0x03    /*!< SDO Format Conversion result + Channel Address + Device Address + Input Range */
#define DEV_ADS8688_PROG_SDOFMT_MASK            0x07    /*!< SDO Format mask */


/**
 ******************************************************************************* 
 */

/* Public macro --------------------------------------------------------------*/

/* Public variables declarations ---------------------------------------------*/

/* Public function prototypes ------------------------------------------------*/
void dev_ads8688_init(void);
void dev_ads8688_cmd(uint8_t cmd);
uint8_t dev_ads8688_prog_write(uint8_t addr, uint8_t data);
void dev_ads8688_prog_read(uint8_t addr, uint8_t *pdata);
void dev_ads8688_data_read(uint16_t *pdata);

#ifdef __cplusplus
}
#endif

#endif	/* __DEV_ADS8688_H */

/**********************************END OF FILE*********************************/

