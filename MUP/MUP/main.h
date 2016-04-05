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
#include <avr/io.h>
#include "DEBUG.h"
#include "ADCFunc.h"
#include "EEPROM.h"
#include "avr/interrupt.h"
/* Exported types ------------------------------------------------------------*/
typedef enum {DISABLE = 0, ENABLE = !DISABLE} MemStatetype;	
typedef enum {NORMAL = 0, DEBUGING = !NORMAL} ControlStatetype;		
typedef enum {FixedCoef = 0x0,IncDecCoef = 0x1,Res22kOm = 0x2,Res47kOm = 0x3} WorkStatetype;	
typedef struct{
	unsigned int PWMCoefficient;
	MemStatetype MemBtnState;
	}EEPROMType;
	

/* Exported constants --------------------------------------------------------*/
/*Конфигурация контролеера*/
#define		Fm_CPU				16000000
#define		DATAADDRESS			0x10
#define		WORKSTATEMASK		0x70

/*ОТладочный светодиод*/
#define		LEDPORTCONFIG		DDRB
#define		LEDPORT				PORTB
#define		LED0				PINB0		
#define		LED0ON				LEDPORT |= (1<<LED0)
#define		LED0OFF				LEDPORT &= ~(1<<LED0)
#define		LEDCHANGE			LEDPORT ^= (1<<LED0) 

/*Ключи и кнопки*/
/////////////////
#define		SW1					PIND3
#define		SWCONFIG			DDRD
#define		SWPORT				PORTD
#define		SW1OFF				SWPORT	 &=	~(1<<SW1)
#define		SW1ON				SWPORT   |= (1<<SW1)
/////////////////
#define		MEMBTN				PINB2
#define		MEMBTNPPIN			PINB			

#define		MEMSW				PINC4
#define		MEMSWCONFIG			DDRC
#define		MEMSWPORT			PORTC
#define		MEMSWON				MEMSWPORT |= (1<<MEMSW)
#define		MEMSWOFF			MEMSWPORT &=~(1<<MEMSW)
/////////////////	
#define		TIMERPRESCALER1024	5	
#define		TIMETOENTERDEBUG	610	

/////////////////
#define		BUTTON1				(1<<0)
#define		BUTTON2				(1<<1)
#define		BUTTON3				(1<<2)
#define		BUTTON4				(1<<3)	
#define		BUTTONMASK			0x0F
#define		NUMBEROFBUTTINS		4			

/*Напряжения питания*/

#define		Up24V				252
#define		Low24V				216	

#define		Up12V				127
#define		Low12V				107

#define		MAXLOADCURRENT		500

#define		SCV10				0x66
#define		SCV100				0x3F0
#define		SCV70				0x2CC
#define		SCV40				0x199	

#define		STEPPWM				0x66

/*Резисторы*/
#define		LOW47				0x191
#define		LOW22				0x256
#define		STEP22				2
#define		STEP47				1.45					
	
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */  
void InitAll(EEPROMType init);


#endif /* __MAIN_H */


/******************* AME 2016 *****END OF FILE****/
