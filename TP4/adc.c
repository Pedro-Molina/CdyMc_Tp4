/*
 * CFile1.c
 *
 * Created: 2/8/2021 13:14:18
 *  Author: molin
 */ 
#include "adc.h"

void ADCSetRead();// funcion privada

static volatile uint16_t read = 0;// mantiene ultimo valor del registro ADC
/**********************************************************
* 
***********************************************************/
/**********************************************************
* Propósito de la función: inicializa el ADC
* vref -> 5V, mux 000 -> ADC0, ADLAR -> 0
* hablitito ADC, preescalador -> 64
*
* Parámetros de entrada : -
***********************************************************/
void ADCInit(){
	ADMUX = 0x00;
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(0<<ADPS0)|(1<<ADATE)|(1<<ADIE);
}

/**********************************************************
* Propósito de la función: comienza la conversion
***********************************************************/
void ADCStart(){
	ADCSRA|= (1<<ADSC);
}

uint16_t ADCGetRead(){
	return read;
}
void ADCSetRead(uint16_t new_read){
	read = new_read;
}
/**********************************************************
* Gestor de interrupciones
***********************************************************/
ISR(ADC_vect){
	ADCSetRead(ADC);
}
