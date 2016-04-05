/**
  ******************************************************************************
  * @file    ADCFunc.h
  * @author  Wolfik
  * @version V1.0.0
  * @date    24-03-2016
  * @brief   This file contains all the functions prototypes for the ADCFunc.c 
  *          file.
  ******************************************************************************
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef ADCFUNC_H_
#define ADCFUNC_H_
/* Includes ------------------------------------------------------------------*/
#include "main.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define		RESCHANEL			0x05
#define		INPUTCHANEL			0x06
#define		FEEDBACKCHANEL		0x07
#define 	MAXVOLT				5.0
#define		MAXADCVALUE			0x3FF
#define		RATIO				13000.0
#define		RFB					2200.0
#define		AMPERVmAMPER		1000
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  
void InitADC(void);
int GetVoltage(void);
int GetCurrent(void);
int GetADCValue(uint8_t chanelADC);

#endif /* ADCFUNC_H_ */


/******************* AME 2016 *****END OF FILE****/









