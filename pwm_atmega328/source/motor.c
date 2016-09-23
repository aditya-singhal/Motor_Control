#include "boardConfig.h"
#include "motor.h"

void dcMotorMove_CW(MotorCfg_t* motor)
{
	GPIO_SET(motor->IN1_PORT, motor->IN1_PIN);
	GPIO_SET(motor->STBY_PORT, motor->STBY_PIN);
	GPIO_CLEAR(motor->IN2_PORT, motor->IN2_PIN);
}

void dcMotorMove_CCW(MotorCfg_t* motor)
{
	GPIO_SET(motor->IN2_PORT, motor->IN2_PIN);
	GPIO_SET(motor->STBY_PORT, motor->STBY_PIN);
	GPIO_CLEAR(motor->IN1_PORT, motor->IN1_PIN);
}

void dcMotorShortBreak(MotorCfg_t* motor)
{
	GPIO_SET(motor->IN1_PORT, motor->IN1_PIN);
	GPIO_SET(motor->IN2_PORT, motor->IN2_PIN);
	GPIO_SET(motor->STBY_PORT, motor->STBY_PIN);
}

void dcMotorStop(MotorCfg_t* motor)
{
	GPIO_CLEAR(motor->IN1_PORT, motor->IN1_PIN);
	GPIO_CLEAR(motor->IN2_PORT, motor->IN2_PIN);
	GPIO_SET(motor->STBY_PORT, motor->STBY_PIN);
}

void dcMotorStandby(MotorCfg_t* motor)
{
	GPIO_CLEAR(motor->STBY_PORT, motor->STBY_PIN);
}