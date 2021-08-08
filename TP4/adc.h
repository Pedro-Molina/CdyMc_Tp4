/*
 * dac.h
 *
 * Created: 2/8/2021 13:15:14
 *  Author: molin
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

void ADCInit();
void ADCStart();
uint16_t ADCGetRead();
void ADCSetRead();
