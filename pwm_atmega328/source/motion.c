#include "boardConfig.h"
#include "motor.h"
#include "motion.h"

#include <util/delay.h>

typedef enum
{
	enBotRunningState_0 = 0,
	enBotRunningState_1,
	enBotRunningState_2,
	enBotRunningState_3,
	enBotRunningState_4,
	enBotRunningState_5,
	enBotRunningState_6,
	enBotRunningState_7,
	enBotRunningState_8,
	enBotRunningState_9
}BotState_t;

static BotState_t botCurrentState = enBotRunningState_0;
static uint8_t botInit=0;

//100% duty cycle
//Average RPM values for the following milliseconds
//RPM and distance traveled by the bot in a gap of 100 milliseconds
float BOT_RPM[10]					= {181.3,209.3,232.5,254.6,256.7,265.1,267.1,272,272.8,274.8};
float BOT_DISTANCE_TRAVELLED[10]	= {6.5,8.5,10,11.5,9.5,11,10,11,10,10.5};		//distance mapped according to the timings
//x=RPM
#define GET_SPEED(x)						(x*WHEEL_CIRCUMFERENCE)/60
#define GET_DUTY_CYCLE(speed,maxSpeed)		((speed/maxSpeed)*100)

#define MAX_MOTOR_SUPPORTED			4

static void _botMoveForward(double duration);
static void _botMoveBackward(double duration);
static void _botTurnLeft(double duration);
static void _botTurnRight(double duration);

typedef void (*botMove_fp)(double);

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

float botMove(float distance, float speed,BotMoveDirection_t direction)
{
	double time;
	float distTravelled=0;
	
	while(botCurrentState < enBotRunningState_8)
	{
		if(botInit == 1)
			break;
		
		setPWMDutyCycle(MOTOR1_FL, DUTY_CYCLE(GET_DUTY_CYCLE(MAX_MOTOR_SPEED,MAX_MOTOR_SPEED)));
		setPWMDutyCycle(MOTOR2_FR, DUTY_CYCLE(GET_DUTY_CYCLE(MAX_MOTOR_SPEED,MAX_MOTOR_SPEED)));
		setPWMDutyCycle(MOTOR3_BL, DUTY_CYCLE(GET_DUTY_CYCLE(MAX_MOTOR_SPEED,MAX_MOTOR_SPEED)));
		setPWMDutyCycle(MOTOR4_BR, DUTY_CYCLE(GET_DUTY_CYCLE(MAX_MOTOR_SPEED,MAX_MOTOR_SPEED)));
			
		if(distTravelled < distance)
		{			
			if((distance-distTravelled) < BOT_DISTANCE_TRAVELLED[botCurrentState])
			{
				time = ((float)(distance-distTravelled)/(float)(GET_SPEED(BOT_RPM[botCurrentState])))*1000;
				(move[direction])(time);
				distTravelled = distance;		//can omit this line
				return distTravelled;
			}
			else
			{
				(move[direction])(100.0);								//run for 100ms
				distTravelled += BOT_DISTANCE_TRAVELLED[botCurrentState];
				botCurrentState++;		
			}
			
			if(GET_SPEED(BOT_RPM[botCurrentState+1]) > speed)
			{
				setPWMDutyCycle(MOTOR1_FL, DUTY_CYCLE(GET_DUTY_CYCLE(speed,GET_SPEED(BOT_RPM[botCurrentState]))));
				setPWMDutyCycle(MOTOR2_FR, DUTY_CYCLE(GET_DUTY_CYCLE(speed,GET_SPEED(BOT_RPM[botCurrentState]))));
				setPWMDutyCycle(MOTOR3_BL, DUTY_CYCLE(GET_DUTY_CYCLE(speed,GET_SPEED(BOT_RPM[botCurrentState]))));
				setPWMDutyCycle(MOTOR4_BR, DUTY_CYCLE(GET_DUTY_CYCLE(speed,GET_SPEED(BOT_RPM[botCurrentState]))));
				botInit = 1;
				break;
			}
		}
		else
		{
			return distTravelled;
		}
	}
	
	//Motor is now running at the desired speed requested by the user.
	time = ((float)(distance-distTravelled)/(float)speed) * 1000;
	(move[direction])(time);
	
	distTravelled = distance;
	return distTravelled;
}

static void _botMoveForward(double duration)
{
	BOT_MOVE_FORWARD(Motor[0]);
	BOT_MOVE_FORWARD(Motor[1]);
	BOT_MOVE_FORWARD(Motor[2]);
	BOT_MOVE_FORWARD(Motor[3]);
	_delay_ms(duration);
}

static void _botMoveBackward(double duration)
{
	BOT_MOVE_BACKWARD(Motor[0]);
	BOT_MOVE_BACKWARD(Motor[1]);
	BOT_MOVE_BACKWARD(Motor[2]);
	BOT_MOVE_BACKWARD(Motor[3]);
	_delay_ms(duration);
}

static void _botTurnLeft(double duration)
{
	BOT_MOVE_BACKWARD(Motor[0]);
	BOT_MOVE_FORWARD(Motor[1]);
	BOT_MOVE_BACKWARD(Motor[2]);
	BOT_MOVE_FORWARD(Motor[3]);
	_delay_ms(duration);
}

static void _botTurnRight(double duration)
{
	BOT_MOVE_FORWARD(Motor[0]);
	BOT_MOVE_BACKWARD(Motor[1]);
	BOT_MOVE_FORWARD(Motor[2]);
	BOT_MOVE_BACKWARD(Motor[3]);
	_delay_ms(duration);
}

void botShortBreak()
{
	dcMotorShortBreak(Motor[0]);
	dcMotorShortBreak(Motor[1]);
	dcMotorShortBreak(Motor[2]);
	dcMotorShortBreak(Motor[3]);
	botCurrentState = 0;
}

void botRotate(uint16_t angle, float speed,BotOrientation_t orientation)
{
	float distance;
	
	distance = (PI*AXLE_LENGTH/4);
	if(orientation == enBotOrientationLeft)
	{
		botMove(distance,speed,enBotTurnLeft);
	}
	else
	{
		botMove(distance,speed,enBotTurnRight);
	}
}