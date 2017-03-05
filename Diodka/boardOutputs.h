/*
 * board.h
 *
 * Created: 01.03.2017 14:10:58
 *  Author: USER
 */ 


#ifndef BOARD_H_
#define BOARD_H_
#include "common.h"
#include <avr/io.h>

#define MAX_JAS 20
#define CAS10 156			//kazdych 10 ms bude volana obsluha prerusenia TC0  12..117  16..156

void initBoard();

void setDiodOn();
void setDiodOff();
void blinkDiodForTime(int totalTime, int jas);

void showNum(int x);
void putToDisplay(int x);

bool isButtonPressed();
void waitForButton();


#endif /* BOARD_H_ */