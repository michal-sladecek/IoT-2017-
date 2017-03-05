/*
 * common.c
 *
 * Created: 03.03.2017 20:08:45
 *  Author: USER
 */ 
#include "common.h"
#include "boardOutputs.h"
#include <string.h>
#include <util/delay.h>


void delay_ms( int ms )
{
	for (int i = 0; i < ms; i++)
	{
		_delay_ms(1);
	}
}

void printBuffer(char * str){
	uint16_t len = strlen(str);
	putToDisplay(len);
	delay_ms(20000);
	for(int i=0;i<len;++i){
		putToDisplay(str[i]);
		delay_ms(5000);
	}
}

void assert(bool mustBeTrue, int valueToDisplay)
{
	if(!mustBeTrue){
		putToDisplay(valueToDisplay);
		while(true){
			blinkDiodForTime(300,20);
			delay_ms(200);
		}
	}
}

void isOk(bool mustBeTrue, int valueToDisplay)
{
		if(mustBeTrue){
			blinkDiodForTime(100,20);
			delay_ms(100);
		}
		else{
			putToDisplay(valueToDisplay);
			delay_ms(1000);
		}
}
