/*
 * myFunc.h
 *
 * Created: 2018-11-07 오전 11:19:21
 *  Author: Administrator
 */ 


#ifndef MYFUNC_H_
#define MYFUNC_H_

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "lcd.h"

#define KEY_1 238
#define KEY_2 222
#define KEY_3 190
#define KEY_PLUS 126
#define KEY_5 237
#define KEY_6 221
#define KEY_7 189
#define KEY_ENTER 125
#define KEY_9 235
#define KEY_10 219
#define KEY_11 187
#define KEY_MENU 123
#define KEY_13 231
#define KEY_CHANGE 183
#define KEY_LOBBY 119

unsigned char getkey()
{
	unsigned char key = 0;
	for (int i=0; i<4; i++)
	{
		PORTD = ~(0x00 | (1 << i));
		_delay_ms(5);
		key = (~PIND & 0xf0);
		if (key) return PIND;
	}
	return 0;
}

void initSystem()
{
	// Register Setting
	DDRA = 0xff;	// 0,1 : Motor | 5,6,7 : RGY LED
	DDRD = 0x0f;	// 0,1,2,3 : Row 0, 1, 2, 3 | 4,5,6,7 : Col 4, 5, 6, 7
	TIMSK = 0x01;
	TCCR0 = 0x07;	// 1024분주
	
	lcd_init();
	lcd_clear();
	for (int i=0; i<2; i++)
	{
		lcd_putsf(0,0,(unsigned char *)"     MARKET     ");
		lcd_putsf(0,1,(unsigned char *)"     SYSTEM     ");
		PORTA = 0b00000000;
		_delay_ms(100);
		lcd_clear();
		PORTA = 0b11100000;
		_delay_ms(100);
	}
	sei();	// Global Interrupt Enable
}

void DisplayClock(unsigned int hou, unsigned int min, unsigned sec)
{
	char str[16];
	sprintf(str,"    %02d:%02d:%02d",hou,min,sec);
	lcd_putsf(0,0,(unsigned char *)"    WELCOME!!   ");
	lcd_putsf(0,1,(unsigned char *)str);
}



#endif /* MYFUNC_H_ */