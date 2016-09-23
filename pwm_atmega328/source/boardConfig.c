#include "boardConfig.h"

static void timer0Init();
static void timer2Init();

void boardInit()
{
	timer0Init();
	timer2Init();
}

static void timer0Init()
{
	PERIPH_TIMER0->TCCRA |= (BIT_7)|(BIT_5)|(BIT_1)|(BIT_0);	//Fast PWM mode, timer count from BOTTOM(0x00) to MAX(0xFF)
																//Output pin is cleared on compare match and sets at BOTTOM
	PERIPH_TIMER0->TCCRB |= (BIT_0);							//Clk(No prescaling)
	PERIPH_PORTD->DDR	|= (BIT_6)|(BIT_5);						//Set OC0A and OC0B in output direction
}

static void timer2Init()
{	
	PERIPH_TIMER2->TCCRA |= (BIT_7)|(BIT_5)|(BIT_1)|(BIT_0);	//Fast PWM mode, timer count from BOTTOM(0x00) to MAX(0xFF)
																//Output pin is cleared on compare match and sets at BOTTOM
	PERIPH_TIMER2->TCCRB |= BIT_0;								//Clk(No prescaling)
	PERIPH_PORTB->DDR	|= BIT_3;								//Set OC2A in output direction
	PERIPH_PORTD->DDR   |= BIT_3;								//Set OC2B in output direction

	
	//PERIPH_TIMER2->TCCRA |= (1<<COM2A1)|(1<<COM2B1)|(1<<WGM21)|(1<<WGM20);	//Fast PWM mode, timer count from BOTTOM(0x00) to MAX(0xFF)
																				//Output pin is cleared on compare match and sets at BOTTOM
	//PERIPH_TIMER2->TCCRB |= (1<<CS20);										//Clk(No prescaling)
	//PERIPH_PORTB->DDR	|= (1<<PORTB3);											//Set OC0A in output direction
	//PERIPH_PORTD->DDR   |= (1<<PORTD3);										//Set OC0B in output direction
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