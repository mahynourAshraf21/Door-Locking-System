 /******************************************************************************
 *
 * Module: DC MOTOR
 *
 * File Name: DcMotor.c
 *
 * Description: source file for the ATmega32 DC MOTOR driver
 *
 * Author: Mahy Mahrous
 *
 *******************************************************************************/


#include "gpio.h"
#include "DcMotor.h"
#include "pwm.h"

/*
 * Description:
 * Function to setup the DC Motor pins direction and stop the motor at the beginning.
 */
void DcMotor_Init(){
	/* setup the pins direction for DC motor pins */
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_PIN1_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(DC_MOTOR_PORT_ID, DC_MOTOR_PIN2_ID, PIN_OUTPUT);

	/* Stop the DC motor at the beginning */
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN1_ID, PIN_INPUT);
	GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN2_ID, PIN_INPUT);
}

/*
 * Description:
 * control the movement of the DC motor depending on its status.
 * send the required speed to the PWM driver to apply it on the DC motor.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	PWM_Timer0_Start(speed);
	switch(state){
	case STOP:
		/* Stop the DC motor */
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN1_ID, PIN_INPUT);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN2_ID, PIN_INPUT);
		break;
	case A_CW:
		/* Rotate clock-wise by assigning A = LOW, B = HIGH */
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN1_ID, PIN_INPUT);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN2_ID, PIN_OUTPUT);
		break;
	case CW:
		/* Rotate Anti-clock-wise by assigning A = HIGH, B = LOW */
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN1_ID, PIN_OUTPUT);
		GPIO_writePin(DC_MOTOR_PORT_ID, DC_MOTOR_PIN2_ID, PIN_INPUT);
		break;
	}
}







