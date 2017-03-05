/*
 * wifi.c
 *
 * Created: 03.03.2017 19:58:55
 *  Author: USER
 */ 
#include "common.h"
#include "wifi.h"
#include "boardOutputs.h"
#include <string.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

FILE uart_str = FDEV_SETUP_STREAM(USART_send_byte,USART_receive_byte,_FDEV_SETUP_RW);

void setup_USART(void)
{
	DDRD |=(1<<PORTD1);					// Tx output
	DDRD &=~(1<<PORTD0);				//Rx input
	UBRR0H = (uint8_t)(UBRR_VALUE>>8);	// BAUDERATE
	UBRR0L = (uint8_t)UBRR_VALUE;
	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00);  //8 bits, parit non, 1 stop
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);	// enable rx a tx
	UCSR0A |= (1<<U2X0);
}

void setupWiFi()
{
	setup_USART();
	stdout=stdin=&uart_str;
	debugCommand("AT+RST\r\n","OK","ERROR");
	delay_ms(2000);
	debugCommand("ATE0\r","OK","ERROR");
	debugCommand("AT\r","OK","ERROR");
	debugCommand("AT+CWMODE_CUR=3\r","OK","ERROR");
	debugCommand("AT+CIPMUX=1\r","OK","ERROR");
}

void createHotSpot(){
	debugCommand("AT+CWSAP_CUR=\"freeWiFi\",\"\",8,0\r","OK","ERROR");	
}

void createServer(){
	debugCommand("AT+CIPSERVER=1,80\r","OK","ERROR");
	debugCommand("AT+CIPSTO=1000\r","OK","ERROR");
}

bool cmdResponseWait(char * cmd, char * response, char * error){
	puts(cmd);
	while(true){
		char buffer[300];
		scanf("%299s",buffer);
		if(strncmp(buffer, response, strlen(response)) == 0){
			return true;
		}
		if(strncmp(buffer, error, strlen(error)) == 0){
			return false;
		}
	}
	return false;
}


uint8_t USART_send(uint8_t a)
{
	while(!(UCSR0A & (1<<UDRE0))){};
	UDR0 = a;
	return 0;
}
uint8_t USART_receive(void)
{
	uint8_t a;
	while(!(UCSR0A & (1<<RXC0))){};
	a = UDR0;
	//USART_send(a);  //echo
	return a;
}
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int USART_send_byte(char u8data, FILE *stream)
{
	if(u8data == '\r')				// \n
	{
		USART_send('\r');
		USART_send('\n');
		//	USART_send_byte('\n',0);	// \r
		return 0;
	}
	
	while(!(UCSR0A & (1<<UDRE0))){};
	UDR0 = u8data;
	return 0;
}
int USART_receive_byte(FILE *stream)
{
	uint8_t u8data;
	while(!(UCSR0A& (1<<RXC0))){};
	u8data = UDR0;
	//USART_send_byte(u8data,stream);  //echo
	return u8data;
}

void debugCommand(char * cmd, char * response, char * error){
	showNum(0xa);
	puts(cmd);
	bool ok = cmdResponseWait(cmd,response,error);
	showNum(0xb);
	isOk(ok, 0b10011110); //E
}

void printIp(char * IP){
	uint16_t length = strlen(IP);
	for(uint16_t i = 0;i<length; ++i){
		if(IP[i] == '.') showNum(17);
		else if(IP[i] >= '0' && IP[i] <= '9'){
			showNum(IP[i] - '0');
		}
		delay_ms(200);
		putToDisplay(0);
		delay_ms(100);
	}
}

void printOwnIP(){
	showNum(0xC);
	puts("AT+CIFSR\r");
	char buffer[500];
	while(true){
		setDiodOn();
		scanf("%499s", buffer);
		setDiodOff();
		if(strncmp("+CIFSR:", buffer, 7) == 0){
			printIp(buffer+7);
			return;
		}
	}
	isOk(false, 0b10011110); //E
	return;
}