/**
  ******************************************************************************
  * @file    main.h
  * @author  Wolfik
  * @version V0.0.0
  * @date    22-03-2016
  * @brief   This file contains all the functions prototypes for the main.c 
  *          file.
  ******************************************************************************
  * @attention
  * 
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H



/* Includes ------------------------------------------------------------------*/


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/*Конфигурация контролеера*/
#define		Fm_CPU				16000000

/*Конфигурация DEBUG*/			
#define		BAUD				256000
#define		UBRValued			((Fm_CPU/16)/BAUD)
/*ОТладочный светодиод*/
#define		LEDPORTCONFIG		DDRB
#define		LEDPORT				PORTB
#define		LED0				PINB0		
#define		LED0ON				LEDPORT |= (1<<LED0)
#define		LED0OFF				LEDPORT &= ~(1<<LED0)
#define		LEDCHANGE			LEDPORT ^= (1<<LED0) 

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  
void InitAll(void);
void DEBUGSendChar(char symbol);
void DEBUGSendMass(uint8_t * pData, uint8_t sizedata);

#endif /* __MAIN_H */


/******************* AME 2016 *****END OF FILE****/

