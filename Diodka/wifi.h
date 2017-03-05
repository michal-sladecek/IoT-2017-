/*
 * wifi.h
 *
 * Created: 03.03.2017 19:58:44
 *  Author: USER
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#ifndef WIFI_H_
#define WIFI_H_
#include "common.h"
#include <stdio.h>

void setupWiFi();

void setup_USART();

uint8_t USART_send(uint8_t a);
uint8_t USART_receive();
int USART_send_byte(char u8data,FILE *stream);
int USART_receive_byte(FILE*stream);


bool cmdResponseWait(char * cmd, char * response, char * error);
void debugCommand(char * cmd, char * response, char * error);
void createHotSpot();
void printOwnIP();
void createServer();
#endif /* WIFI_H_ */