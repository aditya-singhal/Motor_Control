#include "boardConfig.h"
#include <util/delay.h>
#include "motor.h"
#include "motion.h"

//PWM channels
//pin5(OC0B) pin6(OC0A)
//pin3(OC2B) pin11(OC2A)

//FL
MotorCfg_t motor1 =
{						
	PORTD,BIT_6,PORTC,BIT_0,PORTC,BIT_1,PORTB,BIT_5		//pin6,a0,a1,pin13
};

//FR
MotorCfg_t motor2 =
{
	PORTD,BIT_3,PORTD,BIT_2,PORTD,BIT_4,PORTB,BIT_0,	//pin3,pin2,pin4,pin8
};

//BL
MotorCfg_t motor3 =
{
	PORTB,BIT_3,PORTB,BIT_4,PORTB,BIT_1,PORTB,BIT_5		//pin11,pin12,pin9,pin13
};

//BR
MotorCfg_t motor4 =
{
	PORTD,BIT_5,PORTB,BIT_2,PORTD,BIT_7,PORTB,BIT_0		//pin5,pin10,pin7,pin8
};

int main(void)
{
	float distanceTravelled=0;

	boardInit();
	attachMotor(&motor1);
	attachMotor(&motor2);
	attachMotor(&motor3);
	attachMotor(&motor4);

	distanceTravelled = botMove(40,MAX_MOTOR_SPEED/4,enBotMoveForward);
	//distanceTravelled = botMove(14.65,MAX_MOTOR_SPEED/3,enBotMoveForward);
	//distanceTravelled = botMove(14.65,MAX_MOTOR_SPEED/3,enBotMoveForward);
	//botRotate(90, MAX_MOTOR_SPEED/3,enBotOrientationRight);
	//botRotate(90, MAX_MOTOR_SPEED/3,enBotOrientationRight);
	//botRotate(90, MAX_MOTOR_SPEED,enBotOrientationRight);
	//botRotate(90, MAX_MOTOR_SPEED,enBotOrientationRight);	
	
	botShortBreak();
	
	//rotate(90,MOTOR_SPEED_MAX,enLeft);
	//createRectangle(60,30,48.2,enLeft);
	while(1);
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

	setPWMDutyCycle(MOTOR1_FL, DUTY_CYCLE(100));
	setPWMDutyCycle(MOTOR2_FR, DUTY_CYCLE(100));
	setPWMDutyCycle(MOTOR3_BL, DUTY_CYCLE(100));
	setPWMDutyCycle(MOTOR4_BR, DUTY_CYCLE(100));

	dcMotorMove_CW(&motor1);
	dcMotorMove_CW(&motor2);
	dcMotorMove_CW(&motor3);
	dcMotorMove_CW(&motor4);

	_delay_ms(1000);
	
	dcMotorShortBreak(&motor1);
	dcMotorShortBreak(&motor2);
	dcMotorShortBreak(&motor3);
	dcMotorShortBreak(&motor4);


#endif