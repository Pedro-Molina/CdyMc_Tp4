/*
 * TP4.c
 *
 * Created: 2/8/2021 13:11:35
 * Author : molin
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>



#include "adc.h"
#include "lcd.h"
#include "timer2.h"



int main(void)
{
	DIDR0= 0x01;//ADC0 como analog input
	

	
	ADCInit();
	LCDinit();
	LCDclr();
	LCDGotoXY(0,0);
	TIMER2Init();
	ADCStart();
	volatile int temp = 10;
	sei();
	
    while (1) 
    {
		if (TIMER2GetPrintFlag() == 2){
			//actualizo LCD
			temp = (ADCGetRead()*500UL)/1024;
			LCDclr();
			LCDGotoXY(0,0);
			LCDescribeDato(temp,-1);
			TIMER2ResetPrintFlag();
		}
		if(TIMER2GetTempFlag() == 1){
			//verifico temp
			TIMER2ResetTempFlag();
		}

    }
}



