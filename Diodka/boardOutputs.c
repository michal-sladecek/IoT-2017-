/*
 * BoardInputs.c
 *
 * Created: 01.03.2017 14:14:12
 *  Author: USER
 */ 

#include "common.h"
#include "boardOutputs.h"

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SRCLK PORTB1
#define RCLK PORTB2
#define OE PORTC4
#define SER PORTC5
#define TLACITKO_PIN PORTD2
#define DIODA_PIN PORTD6


void initBoard(){
	
	sbi(DDRC,OE);
	sbi(DDRC,SER);
	sbi(DDRB,SRCLK);
	sbi(DDRB,RCLK);
	sbi(DDRD,DIODA_PIN);
	
	sbi(PORTD, TLACITKO_PIN);
	
	//Z periferii.c, treba spravit definy nech sa to da aj citat
	//Tiez treba zmazat tie ktore sa zapinaju dva krat
	sbi(DDRD,PORTD7);				// Control Trans. GP2Y
	sbi(PORTD,PORTD2);				// Pull-up S2
	sbi(DDRD,PORTD5);				//RES_ESP
	sbi(DDRC,PORTC2);				//TX SW_UART
	sbi(PORTC,PORTC2);				// TX SW_UART  H
	sbi(DDRD,PORTD6);				// CO2
	sbi(DDRD,PORTD7);				// Control Trans CO2
}

//Controlling of the diod
void setDiodOn(){
	sbi(PORTD,DIODA_PIN);
}

void setDiodOff(){
	cbi(PORTD,DIODA_PIN);
}

void blinkDiodForTime(int totalTime, int jas){
	int rep = totalTime / MAX_JAS;
	for(int i=0;i<rep;++i){
		setDiodOn();
		delay_ms(jas);
		setDiodOff();
		delay_ms(MAX_JAS - jas);
	}
}

//Controlling of the 7 segment display
void putToDisplay(int x){
	sbi(PORTC,OE);
	for(int i=0;i<8;++i){
		
		if((x & (1<<i)) == 0){
			cbi(PORTC,SER);
		}
		else{
			sbi(PORTC,SER);
		}
		cbi(PORTB,SRCLK);
		sbi(PORTB,SRCLK);
	}
	sbi(PORTB,RCLK);
	
	cbi(PORTB,SRCLK);
	cbi(PORTC,OE);
	cbi(PORTB,RCLK);
}

void showNum(int x){
	switch(x){
		case 0: putToDisplay(0b11111100);break;
		case 1: putToDisplay(0b01100000);break;
		case 2: putToDisplay(0b11011010);break;
		case 3: putToDisplay(0b11110010);break;
		case 4: putToDisplay(0b01100110);break;
		case 5: putToDisplay(0b00110110);break;
		case 6: putToDisplay(0b10111110);break;
		case 7: putToDisplay(0b11100000);break;
		case 8: putToDisplay(0b11111110);break;
		case 9: putToDisplay(0b11110110);break;
		case 0xa: putToDisplay(0b11101110);break;
		case 0xb: putToDisplay(0b00111110);break;
		case 0xc: putToDisplay(0b10011100);break;
		case 0xd: putToDisplay(0b01111010);break;
		case 0xe: putToDisplay(0b10011110);break;
		case 0xf: putToDisplay(0b00111110);break;
		case 0x10: putToDisplay(0b11111111);break;
		default: putToDisplay(1); break;
	}
}

//Button functions
bool isButtonPressed()
{
	return getbit(PIND,TLACITKO_PIN) == 0;
}

void waitForButton(){
	while(!isButtonPressed());
	delay_ms(100);
	while(isButtonPressed());
	delay_ms(100);
}

