/**
  ******************************************************************************
  * @file   EEPROM.h
  * @author  Wolfik
  * @version V0.0.1
  * @date    24-03-2016
  * @brief   This file contains all the functions prototypes for the EEPROM.c 
  *          file.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef EEPROM_H_
#define EEPROM_H_
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  
void ReadFromEEPROM (uint8_t *pData, uint8_t Length,unsigned int AddressEEPROM);
void WriteToEEPROM (uint8_t *pData, uint8_t Length,unsigned int AddressEEPROM);

#endif /* EEPROM_H_ */


/******************* AME 2016 *****END OF FILE****/







