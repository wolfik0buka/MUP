/**
  ******************************************************************************
  * @file    EEPROM.c
  * @author  wolfik
  * @version V0.0.1
  * @date    24-03-2016
  * @brief   ������� ������ � ������ EEPROM
  ******************************************************************************
  * @attention � ������ ����� ������� �������, ������� �������� � 
  * ����������������� �������.
  ******************************************************************************
  ***************HOW TO
  ******************************************************************************
  *1)������ ������ � EEPROM WriteToEEPROM (uint8_t *pData, uint8_t Length,unsigned int AddressEEPROM)
  *2) ������ ������ � EEPROM ReadFromEEPROM (uint8_t *pData, uint8_t Length,unsigned int AddressEEPROM)
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
  * @brief  ������ � EEPROM.
  * @param  EEPROMAddress - ������ � ������� ��������� �������� ���������� (0x00 - 0x1FF)
  *	@param 	Data		  - ���� ���������� ������.
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
  * @brief  ������� ������ � EEPROM ������.
  * @param  *pData		  - ��������� �� ������  ������� ���������� �������� � EEPROM
  *	@param 	Length		  - ������ ������ ��� ������.
  *	@param 	AddressEEPROM - ������ � ������ �������� ������������ ������.
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
  * @brief  ������ ����� �� EEPROM.
  * @param  Address - ������ � �������� ���������� ��������� ������ (0x00 - 0x1FF)
  * @retval ���������� ����.
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
  * @brief  ������� ������ ��  EEPROM ������.
  * @param  *pData		  - ��������� �� ������ � ������� ���������� �������� ������
  *	@param 	Length		  - ������ ������ ��� ������.
  *	@param 	AddressEEPROM - ������ � ������ �������� ������������ ������.
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