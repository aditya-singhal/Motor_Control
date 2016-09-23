#ifndef MOTOR_H_
#define MOTOR_H_

#include "boardConfig.h"

#define MOTOR1_FL			TIMER0_A		//Motor1 Front-left
#define MOTOR2_FR			TIMER0_B		//Motor2 Front-right
#define MOTOR3_BL			TIMER2_B		//Motor3 Back-left
#define MOTOR4_BR			TIMER2_A		//Motor4 Back-right

typedef struct MotorCfg 
{
	uint8_t	IN1_PORT;
	uint8_t	IN1_PIN;
	uint8_t	IN2_PORT;
	uint8_t	IN2_PIN;
	uint8_t	PWM_PORT;
	uint8_t	PWM_PIN;
	uint8_t	STBY_PORT;
	uint8_t	STBY_PIN;
}MotorCfg_t;

#define SET_PWM_DUTY_CYCLE(motor,duty)			setPWMDutyCycle(motor,duty)

void dcMotorMove_CW(MotorCfg_t* motor);
void dcMotorMove_CCW(MotorCfg_t* motor);
void dcMotorShortBreak(MotorCfg_t* motor);
void dcMotorStop(MotorCfg_t* motor);
void dcMotorStandby(MotorCfg_t* motor);

#endif /* MOTOR_H_ */