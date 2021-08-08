/*
 * Timer0.c
 *
 * Created: 5/8/2021 11:02:03
 *  Author: molin
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

#include "adc.h"
#include "lcd.h"

static uint8_t TEMP_FLAG = 0;
static uint8_t PRINT_FLAG = 0;

void TIMER2Init(){
/* interrupcion cada 0,25s*/
	ASSR|= (1<<AS2) ;
	TCCR2A =0x00;
	TCCR2B |= (1<<CS21) | (1<<CS20);//preescalador 32 T = 0,25s
	TIMSK2 |=  (1<<TOIE2);
}
uint8_t TIMER2GetPrintFlag(){
	return PRINT_FLAG;
}
uint8_t TIMER2GetTempFlag(){
	return TEMP_FLAG;
}

void TIMER2ResetPrintFlag(){
	PRINT_FLAG =0;
}
void TIMER2ResetTempFlag(){
	TEMP_FLAG =0;
}
ISR (TIMER2_OVF_vect)  //interrupción cada 0,25s
{
	//sin condición en este caso siempre sumamos 
	TEMP_FLAG++;   
	PRINT_FLAG++;
}
