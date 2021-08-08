/*
 * timer0.h
 *
 * Created: 5/8/2021 11:04:35
 *  Author: molin
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

void TIMER2Init();
uint8_t TIMER2GetPrintFlag();
uint8_t TIMER2GetTempFlag();
void TIMER2ResetPrintFlag();
void TIMER2ResetTempFlag();