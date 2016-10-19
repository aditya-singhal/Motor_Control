#include "boardConfig.h"

static void _sensorInit();
static void _timer0Init();
static void _timer2Init();

void boardInit()
{
	_sensorInit();
	_timer0Init();
	_timer2Init();
}

static void _sensorInit()
{
	PERIPH_PORTC->DDR	|= (BIT_0);		//set PC0 in output direction(VCC)
	GPIO_SET(PORTC,BIT_0);				//VCC
}

static void _timer0Init()
{
	PERIPH_TIMER0->TCCRA |= (BIT_7)|(BIT_5)|(BIT_1)|(BIT_0);	//Fast PWM mode, timer count from BOTTOM(0x00) to MAX(0xFF)
																//Output pin is cleared on compare match and sets at BOTTOM
	PERIPH_TIMER0->TCCRB |= (BIT_0);							//Clk(No prescaling)
	PERIPH_PORTD->DDR	|= (BIT_5);								//Set OC0B in output direction
}

static void _timer2Init()
{	
	PERIPH_TIMER2->TCCRA |= (BIT_7)|(BIT_5)|(BIT_1)|(BIT_0);	//Fast PWM mode, timer count from BOTTOM(0x00) to MAX(0xFF)
																//Output pin is cleared on compare match and sets at BOTTOM
	PERIPH_TIMER2->TCCRB |= BIT_0;								//Clk(No prescaling)
	PERIPH_PORTD->DDR   |= BIT_3;								//Set OC2B in output direction
}

void setPWMDutyCycle(uint8_t timer, uint8_t duty)
{
	switch(timer)
	{
		case TIMER0_A:
		{
			PERIPH_TIMER0->OCRA = duty;
			break;
		}
		case TIMER0_B:
		{
			PERIPH_TIMER0->OCRB = duty;
			break;
		}
		case TIMER2_A:
		{
			PERIPH_TIMER2->OCRA = duty;
			break;
		}
		case TIMER2_B:
		{
			PERIPH_TIMER2->OCRB = duty;
			break;
		}
	}
}
