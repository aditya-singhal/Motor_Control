#include "boardConfig.h"
#include <util/delay.h>
#include "motor.h"
#include "motion.h"

uint8_t getSensorData();

//PWM channels
//pin5(OC0B) pin6(OC0A)
//pin3(OC2B) pin11(OC2A)

//FL
MotorCfg_t motor1 =
{
	PORTD,BIT_3,PORTD,BIT_2,PORTD,BIT_4,PORTB,BIT_0,	//pin3,pin2,pin4,pin8
};

//FR
MotorCfg_t motor2 =
{
	PORTD,BIT_5,PORTD,BIT_6,PORTD,BIT_7,PORTB,BIT_0		//pin5,pin6,pin7,pin8
};

int main(void)
{
	float distanceTravelled=0;
	
	boardInit();
	attachMotor(&motor1);
	attachMotor(&motor2);

	followLine();

	//distanceTravelled = botMove(40,MAX_MOTOR_SPEED,enBotMoveForward);
	//distanceTravelled = botMove(14.65,MAX_MOTOR_SPEED/3,enBotMoveForward);
	//botRotate(90, MAX_MOTOR_SPEED/3,enBotOrientationRight);
	//botRotate(90, MAX_MOTOR_SPEED/3,enBotOrientationRight);
	//botRotate(90, MAX_MOTOR_SPEED,enBotOrientationLeft);
	//botRotate(90, MAX_MOTOR_SPEED,enBotOrientationLeft);
	//botShortBreak();
	//_delay_ms(200);
	//botRotate(90, MAX_MOTOR_SPEED,enBotOrientationRight);
	//botRotate(90, MAX_MOTOR_SPEED,enBotOrientationRight);
	
	while(1);
}


void followLine()
{
	uint8_t sensorData=0;
	while(1)
	{
		sensorData = getSensorData();
		switch(sensorData)
		{
			//forward
			case 0x1B:
			case 0x11:
			case 0x00:
			{
				botRun(30, enBotMoveForward);
				break;
			}
			//go hard right
			case 0x1E:
			case 0x1C:
			case 0x18:
			{
				botRun(20,enBotMoveRight);
				break;		
			}
			
			//go right
			case 0x1D:
			case 0x19:
			{
				botRun(20,enBotMoveForward);
				break;			
			}
			//go left
			case 0x13:
			case 0x17:
			{
				botRun(20,enBotMoveForward);
				break;
			}
			
			//hard left
			case 0x0F:
			case 0x7:
			case 0x3:
			{
				botRun(20,enBotMoveLeft);
				break;
			}
			
			case 0x1F:
			{
				botShortBreak();
				break;
			}
			default:
				break;
		}	
	}
}

//starting form the left
//IRsensor1 - digital9	- PB1
//IRsensor2 - digital10 - PB2
//IRsensor3 - digital11	- PB3
//IRsensor4 - digital12	- PB4
//IRsensor5 - digital13	- PB5
uint8_t getSensorData()
{
	uint8_t data=0;
	
	data = (GPIO_PORT_READ(PORTB));
	return ((data>>1) & (0x1F));
}

//On BLACK- led off - output 0
//On WHITE- led on  - output 1