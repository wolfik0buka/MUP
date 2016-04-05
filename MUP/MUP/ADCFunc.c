/**
  ******************************************************************************
  * @file    ADCFunc.c
  * @author  wolfik
  * @version V1.0.0
  * @date    24-03-2016
  * @brief   Функции АЦП задействованные в проекте 
  ******************************************************************************
  * @attention В данном файле описаны функции связанные с АЦП
  ******************************************************************************
  *		HOW TO 
  ******************************************************************************
  * 1) Произведите настройку АЦП функцией InitADC()
  *	2) Для получения текущего значения АЦП GetADCValue(uint8_t chanelADC)
  * 3) Для получения напряжения на входе GetVoltage()
  *	4) Для получения тока нагрузки GetCurrent()
  * 
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "ADCFunc.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/**********************Настройки АЦП******************************/
/*Предделитель */
#define		PRESCALER128		0x07
/*Маска очистики канала*/
#define		CLEARCHANEL			0x0F

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Инициализирует Работу АЦП.
  * @note	В качестве опорного напряжения используется внешний выъход AVCC (REFD = 01). 
  * Выравнивание по правому краю (ADLAR = 0) , MUX не устанавливаем, так как в данный момент нет выбора канала.
  * Устаноавлен предделитель частоты значением 128 (Fadc = Fclk/128 = 16 000 000 / 128 = 125 КГц (Макс 200Кгц), И запущен АЦП.
  * Free Run и прерывания выключены.
  * @param  None
  * @retval None
  */

void InitADC(void)
{
	ADMUX |= (1<<REFS0);					
	ADCSRA |= (1<<ADEN) | PRESCALER128;
}

/**
  * @brief  Получение измеренного значения АЦП.
  * @param  chanelADC - код канала, который надо измерить
  *		RESCHANEL		-	Канал потонциометра
  *		INPUTCHANEL		-	Входное напряжение
  *		FEEDBACKCHANEL	-	Канал обратной связи
  * @retval Измеренное значение от 0x00 до 0x3FF
  */
int GetADCValue(uint8_t chanelADC)
{
//	int result;
	ADMUX &=~(CLEARCHANEL);			//Очищаем биты выбора канала
	ADMUX |= chanelADC;				// Записываем интересующий нас канал
	ADCSRA |= (1<<ADSC);			// Запускаем преобразование
	while (!(ADCSRA & (1<<ADIF)));	// Ждем окончания преобразования 
	ADCSRA |= (1<<ADIF);			// Очищаем флаг готовности 
	//result = ADC;	
	return ADC;						//Возвраящаем измеренное значение
	
}

/**
  * @brief  Получение текущего входного Напряжения.
  * @param  None
  * @retval Действующее значение напряжения на входе в сотнях миливольт
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
  * @brief  Получение текущего тока нагрузки.
  * @param  None
  * @retval Действующее значение тока нагрузки в мА.
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
