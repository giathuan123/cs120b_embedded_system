/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 8  Exercise 4
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
static unsigned short max = 188;
void ADC_init(){
  ADCSRA |= (1<<ADEN) | (1<<ADSC) | (1<<ADATE);
}
unsigned char getLevels(){
  unsigned char levels = ADC / (max/8);
  int i = 0;
  unsigned char ret = 0x00;
  for(;i < levels; ++i){
    ret |= (1 << i);
  }
  return ret;
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0x00;
    PORTB = 0xFF;
    ADC_init();
    /* Insert your solution below */
    while (1) {
      PORTB = getLevels();
    }
    return 0;
}
