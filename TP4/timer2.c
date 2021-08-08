/*
 * Timer0.c
 *
 * Created: 5/8/2021 11:02:03
 *  Author: molin
 */ 
/**********************************************************
*
***********************************************************/
#include "adc.h"

static uint8_t TEMP_FLAG = 0;
static uint8_t PRINT_FLAG = 0;

/**********************************************************
* Propósito de la función: inicializa el Timer 2
* modo asincronico
* preescalador 32 
* interrupcion por overflow activo
***********************************************************/
void TIMER2Init(){
/* interrupcion cada 0,25s*/
	ASSR|= (1<<AS2) ;				//modo asincronico
	TCCR2A =0x00;					//modo normal
	TCCR2B |= (1<<CS21) | (1<<CS20);//preescalador 32 
	TIMSK2 |=  (1<<TOIE2);			//activo interrupcino por overflow
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
/**********************************************************
* Gestor de interrupcion de Overflow
***********************************************************/
ISR (TIMER2_OVF_vect)  //interrupción cada 0,25s
{
	TEMP_FLAG++;   
	PRINT_FLAG++;
}
