/*
 * Diodka.c
 *
 * Created: 01.03.2017 8:51:19
 *  Author: USER
 */ 

#include "common.h"
#include "boardOutputs.h"
#include "diodaProgram.h"

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>

int main()
{	
	initBoard();
	programDioda();
}