#ifndef MOTION_H_
#define MOTION_H_

#define MAX_MOTOR_SPEED			98.5			//At RPM = 275

#define BOT_MOVE_FORWARD(x)		dcMotorMove_CW(x)
#define BOT_MOVE_BACKWARD(x)	dcMotorMove_CCW(x)

typedef enum
{
	enBotOrientationLeft,
	enBotOrientationRight
}BotOrientation_t;

typedef enum
{
	enBotMoveForward = 0,
	enBotMoveBackward,
	enBotTurnLeft,
	enBotTurnRight,
}BotMoveDirection_t;

int8_t attachMotor(MotorCfg_t* motor);
float botMove(float distance, float speed,BotMoveDirection_t direction);
void botRotate(uint16_t angle, float speed,BotOrientation_t orientation);

#endif /* MOTION_H_ */