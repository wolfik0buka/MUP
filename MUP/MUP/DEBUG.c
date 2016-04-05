
/**
  ******************************************************************************
  * @file    DEBUG.c
  * @author  wolfik
  * @version V1.0.0
  * @date    22-03-2016
  * @brief   ������� Debug
  ******************************************************************************
  * @attention
  * � ������ ����� ��������� �������, ������� ������������ ��� �������.
  * ****************************************************************************
  * HOW TO
  ******************************************************************************
  * 1) ���������������� UART ��� ������ ������ ������� InitDEBUG()
  * 2) ��� �������� ������ ���������� ������� ���������  DEBUGSendChar()
  * 3) ��� �������� ������� �������� ������������ DEBUGSendMass()
  *
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "Debug.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

/**
  * @brief ������������� UART ����������� ��� �������.
  * �������� ������ � ����� main.h.
  * @param  None
  * @retval None
  */
void InitDEBUG(void)
{
	int UBRValue =UBRValued;
	
	UBRRL	=	(uint8_t)	(UBRValue);
	UCSRA	&=~(1<<U2X);
	UCSRC	=  (1<<URSEL)|(1<<UCSZ1) | (1<<UCSZ0);
	UCSRB	|= (1<<TXEN) ;
}

/**
  * @brief  �������� ������� � DEBUG.
  * @param  char symbol - ������ ��� ����� ����������� ��������� 
  * @retval None
  */
void DEBUGSendChar(char symbol)
{
	while (!(UCSRA & (1<<UDRE)));
	UDR = symbol;	
}
/**
  * @brief  �������� ������� �������� � DEBUG.
  * @param  uint8_t * pData - ��������� �� ������ ������� ��������
  * @param	uint8_t sizedata - ������ ������� � ������.
  * @retval None
  */
void DEBUGSendMass(uint8_t * pData, uint8_t sizedata)
{
	for (int NumberSymbol = 0;NumberSymbol < sizedata;NumberSymbol++)
	{
		DEBUGSendChar((char) *(pData+NumberSymbol));
	}
}


/******************* AME 2016*****END OF FILE****/