 /******************************************************************************
 *
 * Module: PWM
 *
 * File Name: pwm.c
 *
 * Description: source file for the ATmega32 PWM driver
 *
 * Author: Nada Hefnawy
 *
 *******************************************************************************/

#include "pwm.h"
#include <avr/io.h>

/* Description:
 * calculating the duty cycle by multiplying the percentage of speed by timer maximum counter.
 * initialize timer counter with zero.
 * assign the calculated duty cycle to the compare match register.
 * setup the direction of PB3 pin to be output pin.
 * configure timer0 with  non inverting fast PWM mode with prescaler 8.
 */
void PWM_Timer0_Start(uint8 duty_cycle){
	if(duty_cycle == 0){
		TCCR0 = 0; /* if speed equals zero, stop timer to save power consumption */
		return;
	}
	duty_cycle = (uint8)(((uint16)(TIMER_MAX_COUNTER*duty_cycle))/100);
	TCNT0 = 0;
	OCR0 = duty_cycle;
	DDRB |= (1<<PB3);
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01);
}


