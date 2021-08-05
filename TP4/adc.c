/*
 * CFile1.c
 *
 * Created: 2/8/2021 13:14:18
 *  Author: molin
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint16_t read = 0;

void ADCInit(){
	ADMUX = 0x00;//vref -> 5V, mux 000 -> ADC0, ADLAR -> 0 
	ADCSRA |= (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADATE)|(1<<ADIE);//hablitito ADC, preescalador -> 128, 
}
void ADCStart(){
	ADCSRA|= (1<<ADSC);
}
uint16_t ADCGetRead(){
	return read;
}
void ADCSetRead(uint16_t new_read){
	read = new_read;
}
ISR(ADC_vect){
	ADCSetRead(ADC);
}
