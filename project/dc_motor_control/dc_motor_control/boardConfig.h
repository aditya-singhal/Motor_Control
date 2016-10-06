#ifndef BOARDCONFIG_H_
#define BOARDCONFIG_H_

#include <stdint.h>
#include "regmap_atmega328.h"

#define F_CPU 16000000UL

#define DUTY_CYCLE(x)			((x/100)*255)

#define TIMER0_A	1
#define TIMER0_B	2
#define TIMER2_A	3
#define TIMER2_B	4

#define GPIO_SET(port,pin)			((GPIO_typedef*)(port))->PORT |= (pin)
#define GPIO_CLEAR(port,pin)		((GPIO_typedef*)(port))->PORT &= ~(pin)

void boardInit();

/**	Sets the duty cycle of output. The Function sets the duty cycle of PWM output generated on OC0 PIN
	The average voltage on this output pin will be

			duty
	Vout =  ------ x 5v
			255 
	Arguments:	motor- Use above defined MACROS to select the timer
				duty- Between 0 - 255
	0= 0%
	255= 100%
**/
void setPWMDutyCycle(uint8_t timer, uint8_t duty);

#endif /* BOARDCONFIG_H_ */