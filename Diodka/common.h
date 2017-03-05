/*
 * common.h
 *
 * Created: 03.03.2017 20:06:25
 *  Author: USER
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#ifndef BAUDERATE
#define BAUDERATE 115200
#endif

#ifndef UBRR_VALUE
#define UBRR_VALUE 16
#endif

#ifndef COMMON_H_
#define COMMON_H_


#define sbi(x,y) x |= _BV(y)
#define cbi(x,y) x &= ~_BV(y)
#define tbi(x,y) x ^= _BV(y)
#define getbit(x,y) (x & _BV(y))

typedef int bool;
#define true 1
#define false 0

void delay_ms( int ms );
//Assertion, ends program if false
void assert(bool mustBeTrue, int valueToDisplay);
//Just shows us output if false, otherwise blinks light
void isOk(bool mustBeTrue, int valueToDisplay);
void printBuffer(char * str);
#endif /* COMMON_H_ */