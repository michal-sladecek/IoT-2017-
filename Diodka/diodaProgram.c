#include "common.h"
#include "diodaProgram.h"
#include "boardOutputs.h"

int pesnicky[][70] = {
	{
		20, 0, 0, 0,
		20, 0, 0, 0,
		20, 0, 20, 0,
		20, 0, 0, 0,
		20, 0, 20, 0,
		20, 0, 20, 0,
		0, 0, 20, 0,
		20, 0, 0, 0,
		0, 0, 0, 0
	},
	{
		20,0
	},
	{
		5, 0, 10, 0, 15, 0, 20, 0, 20, 20, 20, 0, 15, 0, 10, 0, 15, 0, 15, 15, 15, 0, 10, 0, 5,
		0, 10, 0, 10, 10, 10, 0, 15, 0, 10, 0, 5, 0, 5, 5
	},
	{
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,
		24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0
	}
};
int dlzkaPesnicky[] = {36,2,32,51};
int numPesniciek = 4;

int nekonecno[] =	{
	2,1,5,4,3,1,6,7
};

void programDioda(){
	int cur_pesnicka = 0;
	int lastCycleZmena = false;
	for(int cur=0;   ;cur = (cur+1)%dlzkaPesnicky[cur_pesnicka])
	{
		showNum(cur_pesnicka+1);
		if(isButtonPressed() && !lastCycleZmena){
			cur_pesnicka = (cur_pesnicka + 1)%numPesniciek;
			cur = 0;
			lastCycleZmena = true;
		}
		if(!isButtonPressed()){
			lastCycleZmena = false;
		}
		blinkDiodForTime(100, pesnicky[cur_pesnicka][cur]);
	}
}