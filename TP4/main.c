/*
 * TP4.c
 *
 * Created: 2/8/2021 13:11:35
 * Author : molin
 */ 

#define _GNU_SOURCE

#define F_CPU 8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>



#include "adc.h"
#include "lcd.h"
#include "timer2.h"

void checkTempTask();
void printTempTask();



int main(void)
{
	DIDR0= 0x01;//ADC0 como analog input
	DDRB = 0x03;

	
	ADCInit();
	LCDinit();
	LCDclr();
	LCDGotoXY(0,0);
	TIMER2Init();
	ADCStart();
	sei();
	
    while (1) 
    {
		if (TIMER2GetPrintFlag() == 2){
			printTempTask();
		}
		if(TIMER2GetTempFlag() == 1){
			checkTempTask();
		}
    }
}
void printTempTask(){
	//actualizo LCD
	uint16_t temperature;
	char formato[12] ;
	temperature = round((ADCGetRead()*5000UL)/1024);//redondear para rriba?
	snprintf(formato,sizeof(formato),"TEMP: %.2d C",temperature);
	LCDclr();
	LCDGotoXY(0,0);
	LCDstring(formato,sizeof(formato));
	TIMER2ResetPrintFlag();
}

void checkTempTask(){
	//check temperatura y ejecuto actuadores
	uint16_t temperature;
	temperature = round((ADCGetRead()*50000UL)/1024);
	if (temperature > 24){
		PORTB |=(1<<PB0); 
	}else if (temperature < 17)
	{
		PORTB |=(1<<PB1);
	}else 
	{
		PORTB = 0x00;
	}
	TIMER2ResetTempFlag();
}



