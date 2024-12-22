 /******************************************************************************
 *
 * Module: DC MOTOR
 *
 * File Name: DcMotor.h
 *
 * Description: header file for the ATmega32 DC MOTOR driver
 *
 * Author: Nada Hefnawy
 *
 *******************************************************************************/


#ifndef DCMOTOR_H_
#define DCMOTOR_H_

#include "std_types.h"

#define DC_MOTOR_PORT_ID		PORTD_ID
#define DC_MOTOR_PIN1_ID		PIN2_ID
#define DC_MOTOR_PIN2_ID		PIN3_ID

typedef enum{STOP,CW,A_CW}DcMotor_State;

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);



#endif /* DCMOTOR_H_ */
