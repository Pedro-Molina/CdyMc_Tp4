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
#include <math.h>



#include "adc.h"
#include "lcd.h"
#include "timer2.h"

void checkTempTask();
void printTempTask();

static volatile uint16_t temperature;


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
	if (TIMER2GetPrintFlag() == 2){ //flag que me define cuantas interrupciones hubo. 
		printTempTask(); //verifico que se hayan dado dos interrupciones para actualizar el LCD cada 0.5 segundos.
		TIMER2ResetPrintFlag(); //reseteo el flag
	}
	if(TIMER2GetTempFlag() == 1){  //flag que me define si debo de ejecutar la lógica de control de temperatura.
		checkTempTask(); //ejecuto el control de la temperatura.
		TIMER2ResetTempFlag(); //reseteo el flaj
	}
    }
}
void printTempTask(){
	//actualizo LCD
	char formato[13] ;
	temperature = (ADCGetRead()*0.488*10);//redondear para rriba?
	uint8_t parteEntera = temperature/10;
	uint8_t parteFraccionaria = temperature % 10;
	snprintf(formato,sizeof(formato),"TEMP: %d,%d C",parteEntera,parteFraccionaria);
	LCDclr();
	LCDGotoXY(0,0);
	if (parteEntera < 10){
		LCDstring(formato,sizeof(formato)-2);
		
	}else LCDstring(formato,sizeof(formato)-1);
	
	
}

void printTempTask(){
	//actualizo LCD
	char formato[13] ;
	temperature = (ADCGetRead()*0.488*10);//redondear para rriba?
	uint8_t parteEntera = temperature/10;
	uint8_t parteFraccionaria = temperature % 10;
	snprintf(formato,sizeof(formato),"TEMP: %d,%d C",parteEntera,parteFraccionaria);
	LCDclr();
	LCDGotoXY(0,0);
	if (parteEntera < 10){
		LCDstring(formato,sizeof(formato)-2);
		
	}else LCDstring(formato,sizeof(formato)-1);
	
	TIMER2ResetPrintFlag();
	
	
}

void checkTempTask(){
	//check temperatura y ejecuto actuadores
	temperature = round((ADCGetRead()*0.488*10));
	if (temperature > 240){
		PORTB |=(1<<PB0);
	}else if (temperature < 170)
	{
		PORTB |=(1<<PB1);
	}else
	{
		PORTB = 0x00;
	}
	TIMER2ResetTempFlag();
}

funcionControlTemperatura
{
	voltaje = ADC_getVoltaje() //me guardo el voltaje de lectura del ADC
	//obtengo la temperatura usando la funcion obtenida anteriormente pero primero multiplico por 10
	// ya que estoy usando numeros enteros y queremos tener un decimal de precisión.
	temperatura = voltaje * 0.488 * 10
	
	if (temperature > (24 grados)*10){
		//ponemos el bit de PB0 en 1
	}else if (temperature < (17 grados)*10)
	{
		//ponemos el bit de PB1 en 1
	}else
	{
		//ponemos todo PORTB en 0
	}
	
}




