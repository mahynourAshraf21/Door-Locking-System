
#define F_CPU 8000000UL
#define MC2_READY 0x10
#define MC1_READY 0x20
#define PASSWORD_SIZE 5
#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include <util/delay.h> /* For the delay functions */
#include "std_types.h"
#include "gpio.h"
#include "timer.h"
#include "mainFunctions.h"
#include "avr/interrupt.h"
uint8 pass1[7], pass2[7],counter=0,stop=0,a_cw=0,state=0;
uint16 i,c=0;
uint8 k;
boolean flag=0;

void controlMotorTiming_15sec(void) {

	counter++;
	if (state == 0) {
		LCD_clearScreen();
		LCD_displayString("unlocking");
	}
	if (counter == 15) {
		if (state == 0) {
			LCD_clearScreen();
			LCD_displayString("stop");
		}
		state++;
		counter = 0;
		if (state == 1) {
			Timer1_setCallBack(controlMotorTiming_3sec);
		} else if (state == 2) {
	    	c=0;

			Timer1_deInit();
			//DcMotor_Rotate(STOP, 0);
			state = 0;
		}
	}
}


void controlMotorTiming_3sec(void){
	counter++;
	if(counter == 3){ /* 3 seconds */
		//DcMotor_Rotate(A_CW, 100);
		LCD_clearScreen();
		LCD_displayString("locking");
		counter = 0;
		Timer1_setCallBack(controlMotorTiming_15sec);
	}
}
void createPass() {

	LCD_clearScreen();

	LCD_displayString("plz enter pass: ");

	LCD_moveCursor(1, 0);
	i=0;

	while (i < PASSWORD_SIZE) {
		k = KEYPAD_getPressedKey();
		if ((k >= '0') && (k <= '9')) {
			pass1[i] = k;
			LCD_displayCharacter(k);
			i++;
		}
		_delay_ms(250);
	}

	pass1[i] = '#';
	pass1[i + 1] = '\0';
	while (KEYPAD_getPressedKey() != '=') {
	}

	UART_sendString(pass1);
	//UART_sendByte(0);
	//_delay_ms(500);

	LCD_clearScreen();
	LCD_displayString("plz re-enter the");
	LCD_displayStringRowColumn(1, 0, "same pass: ");
	i = 0;
	while (i < PASSWORD_SIZE) {
		k = KEYPAD_getPressedKey();
		if ((k >= '0') && (k <= '9')) {
			pass2[i] = k;
			LCD_displayCharacter(k);
			i++;
		}
		_delay_ms(250);
	}
	pass2[i] = '#';
	pass2[i + 1] = '\0';
	while (KEYPAD_getPressedKey() != '=') {
	}
	UART_sendString(pass2);
}
void controlLCDTiming_1min(void){
	counter++;
	LCD_displayStringRowColumn(0,1,"pass incorrect");
	LCD_displayStringRowColumn(1,1,"3 times");
	if(counter == 60){
		c=0;
		LCD_clearScreen();
		counter = 0;

	}
}

void getPasswordAndCompare(uint8 key) {
	while (1) {
		//get password

		LCD_clearScreen();
		LCD_displayString("plz enter pass");
		LCD_moveCursor(1, 0);
		i = 0;
		while (i < PASSWORD_SIZE) {
			k = KEYPAD_getPressedKey();
			if ((k >= '0') && (k <= '9')) {
				pass2[i] = k;
				LCD_displayCharacter(k);
				i++;
			}
			_delay_ms(250);
		}
		pass2[i] = '#';
		pass2[i + 1] = '\0';
		while (KEYPAD_getPressedKey() != '=') {
			}

		//send pass
		UART_sendString(pass2);
		uint8 cmp = UART_recieveByte();
		if (cmp == 0 && key=='+') {
			LCD_clearScreen();
			LCD_displayString("password is correct");
			_delay_ms(500);
			Timer1_ConfigType TimerConfig =  {0,8000,PRESCALER_1024,CTC};
			Timer1_init(&TimerConfig);
			c=1;
			Timer1_setCallBack(controlMotorTiming_15sec);
			LCD_clearScreen();

			LCD_displayString("unlocking");
			break;
		} else if (cmp == 1 ) {
			LCD_clearScreen();
			LCD_displayString("INCORRECT");
			_delay_ms(500);
			continue;

		} else if (cmp == 2)
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,1,"pass incorrect");
			LCD_displayStringRowColumn(1,1,"3 times");
			c=1;
			Timer1_ConfigType TimerConfig =  {0,8000,PRESCALER_1024,CTC};
			Timer1_init(&TimerConfig);
			Timer1_setCallBack(controlLCDTiming_1min);

			break;
	}
}
//get password
//send pass}

int main(void) {
	SREG |= (1<<7);

	//GPIO_setupPinDirection(PORTC_ID, PIN0_ID, PIN_OUTPUT);
	LCD_init();

	UART_ConfigType config_ptr = { EIGHT, DISABLED, ONE, BAUD_RATE_9600 };

	UART_init(&config_ptr);
	UART_sendByte(MC1_READY);


	//while (UART_recieveByte() != MC2_READY) {}
	boolean flag = UART_recieveByte();
	if (flag == 0) {
		createPass();

	}








    while(1)
    {

    	LCD_clearScreen();
        LCD_displayStringRowColumn(0,1, "+ open door");
        LCD_displayStringRowColumn(1,1, "- change pass");
        _delay_ms(250);
        uint8 key=KEYPAD_getPressedKey();

        UART_sendByte(key);

        switch (key){
		case '+':
			getPasswordAndCompare(key);
			while(c==1){};


			break;
		case '-':
			getPasswordAndCompare(key);
			while(c==1){};
			createPass();




			break;
        }

    }
}
