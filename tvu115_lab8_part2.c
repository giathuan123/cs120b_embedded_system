/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 8  Exercise 2
 *	Exercise Description: A2C converter
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo link: https://drive.google.com/drive/folders/1qhNV4oHdLui7sbfcxBKOoA8kX7zZhtJI?usp=sharing
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
void ADC_init(){
  ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE);
}
int main(void) {
    /* Insert DDR and PORT initializations */
    unsigned short tempADC = 0x00;
    DDRB = 0x00;
    DDRD = 0x00;
    PORTB = 0xFF;
    PORTD = 0xFF;
    ADC_init();
    /* Insert your solution below */
    while (1) {
      tempADC = ADC;
      PORTB = (unsigned char) tempADC;
      PORTD = (unsigned char) (tempADC >> 8);
    }
    return 0;
}
