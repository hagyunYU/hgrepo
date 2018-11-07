/*
* mart.cpp
*
* Created: 2018-11-07 오전 11:13:01
* Author : Administrator
*/

#include "myFunc.h"

unsigned int tCount = 0, hou = 0, min = 0, sec = 0;
int mode = NORMAL_MODE;
int flag = 0;

ISR(TIMER0_OVF_vect)
{
	tCount++;
	if (tCount >= 61)
	{
		// 1 second
		sec++;
		if (sec > 59) { min++; sec = 0; }
		if (min > 59) { hou++; min = 0; }
		if (hou > 23) { hou = min = sec = 0; }
		tCount = 0;
	}
}

int main(void)
{
	initSystem();
	lcd_clear();
	unsigned int inputKey = 0;
	unsigned long long currentPrice = 0;
	unsigned long long totalPrice = 0;
	int flag = 0;
	while (1)
	{
		
		inputKey = getKey();
		if (mode == NORMAL_MODE)
		{
			DisplayClock(hou,min,sec);
			if (inputKey == KEY_MENU) mode = MENU_MODE;
		}
		else if (mode == MENU_MODE)
		{
			lcd_putsf(0,0,(unsigned char *)"1: Calculation  ");
			lcd_putsf(0,1,(unsigned char *)"2: Total Sales  ");
			if (inputKey == KEY_1) mode = CALC_MODE;
			else if (inputKey == KEY_2) mode = TOTAL_MODE;
			inputKey = 0;
			_delay_ms(50);
		}
		else if (mode == CALC_MODE)
		{
			lcd_putsf(0,0,(unsigned char *)"Calculation Mode  ");
			lcd_putsf(0,1,(unsigned char *)"                  ");
			if(flag == 0)
			{
				if(inputKey == KEY_0) currentPrice = (currentPrice * 10) + 0;
				else if(inputKey == KEY_1) currentPrice = (currentPrice * 10) + 1;
				else if(inputKey == KEY_2) currentPrice = (currentPrice * 10) + 2;
				else if(inputKey == KEY_3) currentPrice = (currentPrice * 10) + 3;
				else if(inputKey == KEY_5) currentPrice = (currentPrice * 10) + 4;
				else if(inputKey == KEY_6) currentPrice = (currentPrice * 10) + 5;
				else if(inputKey == KEY_7) currentPrice = (currentPrice * 10) + 6;
				else if(inputKey == KEY_9) currentPrice = (currentPrice * 10) + 7;
				else if(inputKey == KEY_10) currentPrice = (currentPrice * 10) +8;
				else if(inputKey == KEY_11) currentPrice = (currentPrice * 10) +9;
				else if(inputKey == KEY_PLUS)
				{
					totalPrice = totalPrice + currentPrice;
					currentPrice = 0;
				}
				flag = 1;
			}
			if(inputKey == 0) flag = 0;
			char str[16];
			sprintf(str,"%ld",currentPrice);
			lcd_putsf(0,1,(unsigned char *)str);
		}
		else if (mode == TOTAL_MODE)
		{
			lcd_putsf(0,0,(unsigned char *)"Total Sales Mode  ");
		}
		// Whenever client push the lobby key, then go back to normal mode.
		if (inputKey == KEY_LOBBY) mode = NORMAL_MODE;
	}
}

