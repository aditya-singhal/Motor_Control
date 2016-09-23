#include "boardConfig.h"
#include "motor.h"

//PWM channels
//pin5(OC0B) pin6(OC0A)
//pin3(OC2B) pin11(OC2A)

MotorCfg_t motor1 =
{						
	PORTC,BIT_0,PORTC,BIT_1,PORTD,BIT_6,PORTB,BIT_5		//a0,a1,pin6,pin13
};

MotorCfg_t motor2 =
{
	PORTB,BIT_2,PORTD,BIT_7,PORTD,BIT_5,PORTB,BIT_0		//pin10,pin7,pin5,pin8
};

MotorCfg_t motor3 =
{
	PORTB,BIT_4,PORTB,BIT_1,PORTB,BIT_3,PORTB,BIT_5		//pin12,pin9,pin11,pin13
};

MotorCfg_t motor4 =
{
	PORTD,BIT_2,PORTD,BIT_4,PORTD,BIT_3,PORTB,BIT_0,		//pin2,pin4,pin3,pin8
};

int main(void)
{	
	boardInit();
	//setPWMDutyCycle(MOTOR1_FL,80);
	//setPWMDutyCycle(MOTOR2_FR,80);
	setPWMDutyCycle(MOTOR3_BL,80);
	setPWMDutyCycle(MOTOR4_BR,80);
	
	while(1)
	{
		//dcMotorMove_CW(&motor1);
		//dcMotorMove_CW(&motor2);
		dcMotorMove_CW(&motor3);
		dcMotorMove_CW(&motor4);
	}
}

#if 0
void ledBlinkTest()
{
	uint16_t loop=0;
	while(1)
	{
		for(loop=0;loop<=255;loop++)
		{
			SET_PWM_DUTY_CYCLE(MOTOR1_FL, loop);
			SET_PWM_DUTY_CYCLE(MOTOR2_FR, loop);
			SET_PWM_DUTY_CYCLE(MOTOR3_BL, loop);
			SET_PWM_DUTY_CYCLE(MOTOR4_BR, loop);
			_delay_ms(10);
		}
		for(loop=255;loop>=1;loop--)
		{
			SET_PWM_DUTY_CYCLE(MOTOR1_FL, loop);
			SET_PWM_DUTY_CYCLE(MOTOR2_FR, loop);
			SET_PWM_DUTY_CYCLE(MOTOR3_BL, loop);
			SET_PWM_DUTY_CYCLE(MOTOR4_BR, loop);
			_delay_ms(10);
		}
	}
}

#endif