/*	Author: thuanvu
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 2 Exercise 4 Challenge
 *	Exercise Description: Intro to AVR roolchain
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    while(1){
      unsigned short totalWeight = PINA + PINB + PINC;
      // larget totalWeight = 765 = 10 1111 1101, present by shifting right 2 and masking with 0xFC 1111 1100
      PORTD = ((totalWeight) > 140) + ((((PINA - PINC) > 80) || ((PINC - PINA) > 80)) << 1) + ((totalWeight >> 2) & 0xFC);
    }
    return 1;
}
