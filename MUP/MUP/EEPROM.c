/**
  ******************************************************************************
  * @file    EEPROM.c
  * @author  wolfik
  * @version V0.0.1
  * @date    24-03-2016
  * @brief   Функции записи и чтения EEPROM
  ******************************************************************************
  * @attention В данном файле описаны функции, которые работают с 
  * Энергонезависимой памятью.
  ******************************************************************************
  ***************HOW TO
  ******************************************************************************
  *1)Запись данных в EEPROM WriteToEEPROM (uint8_t *pData, uint8_t Length,unsigned int AddressEEPROM)
  *2) Чтение данных с EEPROM ReadFromEEPROM (uint8_t *pData, uint8_t Length,unsigned int AddressEEPROM)
  *
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "EEPROM.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/



/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Запись в EEPROM.
  * @param  EEPROMAddress - Адресс в который требуется записать информацию (0x00 - 0x1FF)
  *	@param 	Data		  - Байт подлежащий записи.
  * @retval None
  */
void EEPROMWrite (unsigned int EEPROMAddress, uint8_t Data)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE));
	/* Set up address and data registers */
	EEAR = EEPROMAddress;
	EEDR = Data;
	/* Write logical one to EEMWE */
	EECR |= (1<<EEMWE);
	/* Start eeprom write by setting EEWE */
	EECR |= (1<<EEWE);
}

/**
  * @brief  Функция записи в EEPROM данных.
  * @param  *pData		  - Указатель на массив  который необходимо записать в EEPROM
  *	@param 	Length		  - Размер данных для записи.
  *	@param 	AddressEEPROM - Адресс с начала которого производится запись.
  * @retval None
  */
void WriteToEEPROM (uint8_t *pData, uint8_t Length,unsigned int AddressEEPROM)
{
	int CounterBytes;
	for (CounterBytes = 0 ;CounterBytes< Length;CounterBytes++)
	{
		EEPROMWrite (AddressEEPROM, *pData);
		AddressEEPROM++;
		pData++;
	}
}
/**
  * @brief  Чтение байта из EEPROM.
  * @param  Address - Адресс с которого необходимо считывать данные (0x00 - 0x1FF)
  * @retval прочитаный байт.
  */
uint8_t EEPROMread(unsigned int Address)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEWE))
	;
	/* Set up address register */
	EEAR = Address;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from data register */
	return EEDR;
}

/**
  * @brief  Функция чтения из  EEPROM данных.
  * @param  *pData		  - Указатель на массив в который необходимо записать данные
  *	@param 	Length		  - Размер данных для чтения.
  *	@param 	AddressEEPROM - Адресс с начала которого производится чтение.
  * @retval None
  */
void ReadFromEEPROM (uint8_t *pData, uint8_t Length,unsigned int AddressEEPROM)
{
	int CounterBytes;
	for (CounterBytes = 0 ;CounterBytes< Length;CounterBytes++)
	{
		*pData = EEPROMread (AddressEEPROM);
		AddressEEPROM++;
		pData++;
		
	}
}



/******************* AME 2016*****END OF FILE****/