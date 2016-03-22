/**
  ******************************************************************************
  * @file    MUP.c
  * @author  Wolfik 
  * @version v0.0.0.1
  * @date    22-03-2016
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * ��������� ���������� ���������� �� ��������. � ������ ����� ���������
  * �������� �������� ������, ������������� ��������� � �.�
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <avr/io.h>
#include "main.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	uint8_t Test[] = "Test Message";
	InitAll();
	UDR = 0x31;
	for(int i=0;i<1000;i++);
	DEBUGSendChar('5');
	DEBUGSendMass(Test, sizeof(Test));
	while(1)
	{
        LEDCHANGE;
		
	}
}
/**
  * @brief  �������������� ������ ����������. ��������� �� ����� �������� ��������,
  * ����������� ��� �������� ��������� ����������. ��������� � PB0. 
  * @param  None
  * @retval None
  */
void InitLed0(void)
{
	LEDPORTCONFIG |= (1<<LED0);
}
/**
  * @brief ������������� UART ����������� ��� �������.
  * �������� ������ � ����� main.h.
  * @param  None
  * @retval None
  */
void InitDEBUG(void)
{
	int UBRValue =UBRValued;
	
//	UBRRH	=	(uint8_t)	(UBRValue>>8);
	UBRRL	=	(uint8_t)	(UBRValue);
	UCSRA	&=~(1<<U2X);
	UCSRC	=  (1<<URSEL)|(1<<UCSZ1) | (1<<UCSZ0);
	UCSRB	|= (1<<TXEN) ;
}

/**
  * @brief  �������������� ��� ����������� ���������.
  * @param  None
  * @retval None
  */
void InitAll(void)
{
	InitLed0();
	InitDEBUG();
}



/**
  * @brief  �������� ������� � DEBUG.
  * @param  None
  * @retval None
  */
void DEBUGSendChar(char symbol)
{
	while (!(UCSRA & (1<<UDRE)));
	UDR = symbol;	
}
void DEBUGSendMass(uint8_t * pData, uint8_t sizedata)
{
	for (int NumberSymbol = 0;NumberSymbol < sizedata;NumberSymbol++)
	{
		DEBUGSendChar((char) *(pData+NumberSymbol));
	}
}
/******************* AME 2016*****END OF FILE****/