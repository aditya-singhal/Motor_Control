#include "boardConfig.h"
#include "motor.h"
#include "motion.h"

#include <util/delay.h>

typedef enum
{
	enBotStateIdle,
	enBotStateRamping,
	enBotStateDesiredSpeed,
	enBotStateStop
}EnBotState_t;

typedef enum
{
	enMotorRunningState_0 = 0,
	enMotorRunningState_1,
	enMotorRunningState_2,
	enMotorRunningState_3,
	enMotorRunningState_4,
	enMotorRunningState_5,
	enMotorRunningState_6,
	enMotorRunningState_7,
	enMotorRunningState_8,
	enMotorRunningState_9
}EnMotorState_t;

static EnMotorState_t motorCurrentState = enMotorRunningState_0;
static EnBotState_t botCurrentState		= enBotStateIdle;

//100% duty cycle
//Average RPM values for the following milliseconds
//RPM and distance traveled by the bot in a gap of 100 milliseconds
float BOT_RPM[10]					= {181.3,209.3,232.5,254.6,256.7,265.1,267.1,272,272.8,274.8};
//float BOT_DISTANCE_TRAVELLED[10]	= {6.5,8.5,10,11.5,9.5,11,10,11,10,10.5};		//distance mapped according to the timings

#define GET_SPEED(RPM)							((RPM*WHEEL_CIRCUMFERENCE)/60)
#define GET_DUTY_CYCLE(x,maxStateSpeed)			((x/maxStateSpeed)*100)

#define MAX_MOTOR_SUPPORTED			4

static void _botMoveForward();
static void _botMoveBackward();
static void _botTurnLeft();
static void _botTurnRight();
static float _motorRamp(float userSpeed,BotMoveDirection_t direction,uint8_t freeRun, float distance);
static void _botSetSpeed(float userSpeed, EnMotorState_t motorState);

typedef void (*botMove_fp)();

botMove_fp move[4] = 
{
	_botMoveForward,
	_botMoveBackward,
	_botTurnLeft,
	_botTurnRight
};

MotorCfg_t* Motor[MAX_MOTOR_SUPPORTED] = {0,0,0,0};
uint8_t motorCount = 0;

int8_t attachMotor(MotorCfg_t* motor)
{
	if(motorCount < MAX_MOTOR_SUPPORTED)
	{
		Motor[motorCount] = motor;
		motorCount++;
		return 0;
	}
	else
		return -1;
}

float botMove(float distance, float userSpeed,BotMoveDirection_t direction)
{
	float distTravelled=0;
	double time=0;
	
	if(motorCurrentState < enMotorRunningState_9)
	{
		distTravelled = _motorRamp(userSpeed,direction,0,distance);
		if(distTravelled == distance)
		{
			botShortBreak();
			return distTravelled;
		}
	}

	_botSetSpeed(userSpeed, enMotorRunningState_9);	
	time = ((float)(distance-distTravelled)/(float)(userSpeed))*1000;
	(move[direction])();
	_delay_ms(time);
	botShortBreak();
	
	return distance;
}

void botRun(float userSpeed, BotMoveDirection_t direction)
{
	_motorRamp(userSpeed, direction,1,0);
	(move[direction])();
}

void botShortBreak()
{
	dcMotorShortBreak(Motor[0]);
	dcMotorShortBreak(Motor[1]);
	motorCurrentState	= enMotorRunningState_0;
	botCurrentState		= enBotStateStop;
}

void botRotate(uint16_t angle, float speed,BotOrientation_t orientation)
{
	float distance;
	
	distance = (PI*AXLE_LENGTH/4);
	if(orientation == enBotOrientationLeft)
	{
		botMove(distance,speed,enBotMoveLeft);
	}
	else
	{
		botMove(distance,speed,enBotMoveRight);
	}
}

static float _motorRamp(float userSpeed,BotMoveDirection_t direction,uint8_t freeRun, float distance)
{
	float distTravelled=0, botSpeed=0;
	double time=0;
	
	botCurrentState = enBotStateRamping;
	while(motorCurrentState < enMotorRunningState_9)		//for 900ms
	{
		switch(botCurrentState)
		{
			case enBotStateRamping:
			{
				if(GET_SPEED(BOT_RPM[motorCurrentState]) > userSpeed)
				{
					botSpeed		= userSpeed;
					botCurrentState = enBotStateDesiredSpeed;
				}
				else
				{
					botSpeed = GET_SPEED(BOT_RPM[motorCurrentState]);
				}
				break;
			}
			
			case enBotStateDesiredSpeed:				//bot speed=user speed
			{
				break;
			}
		}
		
		_botSetSpeed(botSpeed, motorCurrentState);		
		if(((distance-distTravelled) < (GET_SPEED(BOT_RPM[motorCurrentState]) * 0.1)) && (freeRun == 0))
		{
			time = ((float)(distance-distTravelled)/(float)(GET_SPEED(BOT_RPM[motorCurrentState-1])))*1000;		//(botCurrentState-1)? check it
			(move[direction])(time);
			motorCurrentState++;
			return distance;
		}
		else
		{
			//run for 100ms
			(move[direction])();
			_delay_ms(100);
			distTravelled += botSpeed * 0.1;
		}
		motorCurrentState++;
	}
	return distTravelled;
}

static void _botSetSpeed(float userSpeed, EnMotorState_t motorState)
{
	setPWMDutyCycle(MOTOR1_FL, DUTY_CYCLE(GET_DUTY_CYCLE(userSpeed,GET_SPEED(BOT_RPM[motorState]))));
	setPWMDutyCycle(MOTOR2_FR, DUTY_CYCLE(GET_DUTY_CYCLE(userSpeed,GET_SPEED(BOT_RPM[motorState]))));
}

static void _botMoveForward()
{
	dcMotorMove_CW(Motor[0]);
	dcMotorMove_CW(Motor[1]);
}

static void _botMoveBackward()
{
	dcMotorMove_CCW(Motor[0]);
	dcMotorMove_CCW(Motor[1]);
}

static void _botTurnLeft()
{
	dcMotorMove_CCW(Motor[0]);
	dcMotorMove_CW(Motor[1]);
}

static void _botTurnRight()
{
	dcMotorMove_CW(Motor[0]);
	dcMotorMove_CCW(Motor[1]);
}
