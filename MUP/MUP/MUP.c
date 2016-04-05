/**
  ******************************************************************************
  * @file    MUP.c
  * @author  Wolfik 
  * @version v0.0.1.0
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

#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
volatile uint8_t PreviosState = 0xf;			
volatile int	 TimeKnopki;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
ISR (TIMER0_OVF_vect)
{
	TimeKnopki++;
	DEBUGSendChar('I');
} 


/**
  * @brief  ��������� ������ �� ������� 
  * @param  None
  * @retval ��������� � ������� �������� ������ (0b0000 0000) , ��� ��������� 4 ���� 1- ��� ����� , 0 �� ���� ������
  */
uint8_t ScanKeys(void)
{
	extern volatile uint8_t PreviosState;
	uint8_t CurrentStateButtons, ResultFronts;
	ResultFronts = 0;
	CurrentStateButtons = PINC & BUTTONMASK	;
	for (int NumberPin=0; NumberPin<NUMBEROFBUTTINS  ;NumberPin++)
	{
		if (((CurrentStateButtons & (1<<NumberPin)) == 0) & ((PreviosState & (1<<NumberPin)) != 0))
		{
			ResultFronts |= 1<<NumberPin;
		}
	}
	PreviosState = CurrentStateButtons;
	return ResultFronts;
}
/**
  * @brief  ������������� ����� ����������� ���
  * @param  NewCoeff - ����� ����������� 0x66 - 0x3FF
  * @retval none
  */
void SetPWMCoefficient(unsigned int NewCoeff)
{
	OCR1A = NewCoeff;

}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
	EEPROMType epromData;
	WorkStatetype WorkState;
	ControlStatetype StateControl = NORMAL;
	int InputVoltage,LoadCurrent,PausePower ;
	int HVoltage,LVoltage;
	uint8_t PreviosPinState, CurrentPinState;
	/*������ �� ������� �������*/
	ReadFromEEPROM ((uint8_t*) &epromData, sizeof(epromData),DATAADDRESS);
	if ((epromData.PWMCoefficient < SCV10) |(epromData.PWMCoefficient > SCV100))
	{
		epromData.PWMCoefficient = SCV10;
	}
	/*END*/
	InitAll(epromData);
	WriteToEEPROM ((uint8_t*) &epromData, sizeof(epromData),DATAADDRESS);
	PreviosPinState = MEMBTNPPIN & (1<<MEMBTN);
	/*������ � �������������� ���������*/
	WorkState = (PIND & WORKSTATEMASK) >> 4;
	if(PIND & (1<<PIND7))
	{
		HVoltage = Up24V;
		LVoltage = Low24V;
	} else {
		HVoltage = Up12V;
		LVoltage = Low12V;
	}
	SW1ON;
	PausePower = 0;
	/*END*/
	while(1)
	{
		/*��� ���������� ������, ��������� �������� ���������� � ��� � �������� �� ��������� ����������*/
		if (StateControl == NORMAL)
		{
			InputVoltage = GetVoltage();
			if ((InputVoltage < LVoltage) | (InputVoltage > HVoltage))
			{
				SW1OFF;
				PausePower = 0;
			}
			LoadCurrent = GetCurrent();
			if (LoadCurrent > MAXLOADCURRENT)
			{
				SW1OFF;
				PausePower = 0;
			}
		}
		
		if ((SWPORT & (1<<SW1)) == 0)
		{
			DEBUGSendChar('1');
			InputVoltage = GetVoltage();
			if ((InputVoltage > LVoltage) & (InputVoltage < HVoltage))
			{
				DEBUGSendChar('2');
				PausePower++;
				DEBUGSendMass((uint8_t*) &PausePower,sizeof(int));
			} else {
				PausePower = 0;
			}
			
			if (PausePower > 0x1F0)
			{
				SW1ON;
				DEBUGSendChar('3');
				PausePower = 0;
			}
		}
		/*��������� ��������� ������ ���������, ����� �������� �� ���� � ����� �����*/
		CurrentPinState = MEMBTNPPIN & (1<<MEMBTN);
		if (CurrentPinState !=PreviosPinState)
		{
			if ( (CurrentPinState != 0) & (PreviosPinState ==0  ))
			{
				if (StateControl == NORMAL)
				{
					TCCR0 = 0;
					TCNT0 = 0;
					cli();
					DEBUGSendChar('T');
				}
				if (epromData.MemBtnState == DISABLE)
				{
					MEMSWON;
					epromData.MemBtnState = ENABLE;
				}
				else
				{
					MEMSWOFF;
					epromData.MemBtnState = DISABLE;
				}
				WriteToEEPROM ((uint8_t*) &epromData, sizeof(epromData),DATAADDRESS);
			} else {
				if (StateControl == NORMAL)
				{
					TimeKnopki = 0;
					TCCR0 |=  TIMERPRESCALER1024;
					sei();
					DEBUGSendChar('S');
				}
			}
		}
		PreviosPinState = CurrentPinState;
		if (TimeKnopki >TIMETOENTERDEBUG)
		{
			TimeKnopki = 0;
			TCCR0 = 0;
			TCNT0 = 0;
			cli();
			DEBUGSendChar('D');
			StateControl = DEBUGING;
			SW1ON;
		}
		switch (WorkState) {
			case FixedCoef :
			{
				uint8_t Fronts;
				Fronts = ScanKeys();
				if (Fronts != 0)
				{
					if (Fronts & BUTTON1)
					{
						epromData.PWMCoefficient = SCV10;
					}
					if (Fronts & BUTTON2)
					{
						epromData.PWMCoefficient = SCV100;
					}
					if (Fronts & BUTTON3)
					{
						epromData.PWMCoefficient = SCV70;
					}
					if (Fronts & BUTTON4)
					{
						epromData.PWMCoefficient = SCV40;
					}
					SetPWMCoefficient(epromData.PWMCoefficient);
					WriteToEEPROM ((uint8_t*) &epromData, sizeof(epromData),DATAADDRESS);
				}				
				break;
			}
			case IncDecCoef:
			{
				uint8_t Fronts;
				Fronts = ScanKeys();
				if (Fronts != 0)
				{
					if (Fronts & BUTTON1)
					{
						epromData.PWMCoefficient = SCV10;
					}
					if (Fronts & BUTTON2)
					{
						epromData.PWMCoefficient = SCV100;
					}
					if (Fronts & BUTTON3)
					{
						epromData.PWMCoefficient += STEPPWM;
						if ((epromData.PWMCoefficient > SCV100) | (epromData.PWMCoefficient <SCV10) )
						{
							epromData.PWMCoefficient = SCV100;
						}
					}
					if (Fronts & BUTTON4)
					{
						epromData.PWMCoefficient -= STEPPWM;
						if ((epromData.PWMCoefficient < SCV10)  | (epromData.PWMCoefficient >SCV100))
						{
							epromData.PWMCoefficient =SCV10;
						}
					}
					SetPWMCoefficient(epromData.PWMCoefficient);
					WriteToEEPROM ((uint8_t*) &epromData, sizeof(epromData),DATAADDRESS);
				}
				break;
			}
			case Res22kOm:
			{
				
				int ADCValue;
				ADCValue = GetADCValue( RESCHANEL);
				ADCValue -= LOW22;
				epromData.PWMCoefficient = SCV10 + (STEP22*ADCValue);
				SetPWMCoefficient(epromData.PWMCoefficient);
				WriteToEEPROM ((uint8_t*) &epromData, sizeof(epromData),DATAADDRESS);
				break;
			}
			case Res47kOm:
			{
				int ADCValue;
				ADCValue = GetADCValue( RESCHANEL);
				ADCValue -= LOW47;
				epromData.PWMCoefficient = SCV10 + ((STEP47*ADCValue))/1;
				SetPWMCoefficient(epromData.PWMCoefficient);
				WriteToEEPROM ((uint8_t*) &epromData, sizeof(epromData),DATAADDRESS);
				break;
			}
			default:
			{
				DEBUGSendChar('E');
				DEBUGSendChar('R');
			}
		}
		
		
		PreviosPinState = CurrentPinState;
		
		/*DebugFunc*/
		
		LEDCHANGE;
		
		
		for (unsigned int i=0;i<60000;i++);
		/*END*/
		
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
  * @brief  �������������� ������ ���. �������� ������� 
  * @param  None
  * @retval None
  */

void InitPWM(unsigned int CoeffPWM)
{
	DDRB |= (1<<PINB1);
	TCCR1A |= (1<<COM1A1)|(1<<COM1A0) | (1<<WGM11) | (1<<WGM10);
	TCCR1B |=  (1<<WGM12);
	OCR1A = CoeffPWM;
	TCCR1B |= (1<<CS10);
	
}


/**
  * @brief  �������������� ��� ����������� ���������.
  * @param  None
  * @retval None
  */
void InitAll(EEPROMType init)
{
	InitDEBUG();					//	���������� �������
	InitLed0();						//	���������� ���������
	InitADC();						//	��������� ���
	InitPWM(init.PWMCoefficient);	//	��������� ���
	/*��������� ������*/			
	SWCONFIG |= (1<<SW1);			// �������������� ����
	SW1OFF;							// ��������� ����
	MEMSWCONFIG |= (1<<MEMSW);
	PORTB |= (1<<2);
	if (init.MemBtnState != DISABLE)
		MEMSWON;
	else 
		MEMSWOFF;
	/*��������� ��������� �������*/
	TIMSK |= (1<<TOIE0);
	
	
}


/******************* AME 2016*****END OF FILE****/