/**
  ******************************************************************************
  * @file    debuf.h
  * @author  Wolfik
  * @version V1.0.0
  * @date    22-03-2016
  * @brief   This file contains all the functions prototypes for the debug.c 
  *          file.
  ******************************************************************************
  * @attention
  *
  * 
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DEBUG_H
#define __DEBUG_H
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/*Конфигурация DEBUG*/
#define		BAUD				256000
#define		UBRValued			((Fm_CPU/16)/BAUD)
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 
void InitDEBUG(void);
void DEBUGSendChar(char symbol);
void DEBUGSendMass(uint8_t * pData, uint8_t sizedata);

#endif /* __DEBUG_H */


/******************* AME 2016 *****END OF FILE****/

