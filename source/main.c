/*	Author: thuanvu
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 2 Exercise 1
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
      PORTB = ~(PINA & 0x02) && (PINA & 0x01);
    }
    return 1;
}
