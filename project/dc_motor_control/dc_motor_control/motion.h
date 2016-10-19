#ifndef MOTION_H_
#define MOTION_H_

#define MAX_MOTOR_SPEED			98.5			//At RPM = 275

typedef enum
{
	enBotOrientationLeft,
	enBotOrientationRight
}BotOrientation_t;

typedef enum
{
	enBotMoveForward = 0,
	enBotMoveBackward,
	enBotMoveLeft,
	enBotMoveRight,
}BotMoveDirection_t;

int8_t attachMotor(MotorCfg_t* motor);
float botMove(float distance, float speed,BotMoveDirection_t direction);
void botRun(float userSpeed, BotMoveDirection_t direction);
void botRotate(uint16_t angle, float speed,BotOrientation_t orientation);
void botShortBreak();

#endif /* MOTION_H_ */