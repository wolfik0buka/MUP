/**
  ******************************************************************************
  * @file    ADCFunc.c
  * @author  wolfik
  * @version V1.0.0
  * @date    24-03-2016
  * @brief   ������� ��� ��������������� � ������� 
  ******************************************************************************
  * @attention � ������ ����� ������� ������� ��������� � ���
  ******************************************************************************
  *		HOW TO 
  ******************************************************************************
  * 1) ����������� ��������� ��� �������� InitADC()
  *	2) ��� ��������� �������� �������� ��� GetADCValue(uint8_t chanelADC)
  * 3) ��� ��������� ���������� �� ����� GetVoltage()
  *	4) ��� ��������� ���� �������� GetCurrent()
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ADCFunc.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/**********************��������� ���******************************/
/*������������ */
#define		PRESCALER128		0x07
/*����� �������� ������*/
#define		CLEARCHANEL			0x0F

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  �������������� ������ ���.
  * @note	� �������� �������� ���������� ������������ ������� ������ AVCC (REFD = 01). 
  * ������������ �� ������� ���� (ADLAR = 0) , MUX �� �������������, ��� ��� � ������ ������ ��� ������ ������.
  * ����������� ������������ ������� ��������� 128 (Fadc = Fclk/128 = 16 000 000 / 128 = 125 ��� (���� 200���), � ������� ���.
  * Free Run � ���������� ���������.
  * @param  None
  * @retval None
  */

void InitADC(void)
{
	ADMUX |= (1<<REFS0);					
	ADCSRA |= (1<<ADEN) | PRESCALER128;
}

/**
  * @brief  ��������� ����������� �������� ���.
  * @param  chanelADC - ��� ������, ������� ���� ��������
  *		RESCHANEL		-	����� �������������
  *		INPUTCHANEL		-	������� ����������
  *		FEEDBACKCHANEL	-	����� �������� �����
  * @retval ���������� �������� �� 0x00 �� 0x3FF
  */
int GetADCValue(uint8_t chanelADC)
{
//	int result;
	ADMUX &=~(CLEARCHANEL);			//������� ���� ������ ������
	ADMUX |= chanelADC;				// ���������� ������������ ��� �����
	ADCSRA |= (1<<ADSC);			// ��������� ��������������
	while (!(ADCSRA & (1<<ADIF)));	// ���� ��������� �������������� 
	ADCSRA |= (1<<ADIF);			// ������� ���� ���������� 
	//result = ADC;	
	return ADC;						//����������� ���������� ��������
	
}

/**
  * @brief  ��������� �������� �������� ����������.
  * @param  None
  * @retval ����������� �������� ���������� �� ����� � ������ ���������
  */
int GetVoltage(void)
{
	float	Voltage;
	int ADCValue;
	ADCValue =  GetADCValue(INPUTCHANEL);
	Voltage = (MAXVOLT/MAXADCVALUE)*ADCValue;
	return Voltage*83/1;
	
	
}


/**
  * @brief  ��������� �������� ���� ��������.
  * @param  None
  * @retval ����������� �������� ���� �������� � ��.
  */
int GetCurrent(void)
{
	int ADCValue, LoadCurrentmA;
	float  FeedbackVoltage,LoadCurrent;
	ADCValue =  GetADCValue(FEEDBACKCHANEL);
	FeedbackVoltage = (MAXVOLT*ADCValue)/0x3FF;
	LoadCurrent = RATIO*FeedbackVoltage/RFB;
	LoadCurrentmA = LoadCurrent*AMPERVmAMPER/1;
	return	LoadCurrentmA;
	
}



/******************* AME 2016*****END OF FILE****/
