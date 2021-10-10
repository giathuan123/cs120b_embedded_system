/*	Author: thuanvu
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 3 Exercise 2
 *	Exercise Description: Count the number of 1s on ports A and B and output that number on portC 
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char SetBit(unsigned char port, unsigned char index, unsigned char bit){
  return (bit ? (port | 0x01 << index) : (port & ~(0x01 << index)));
}
unsigned char GetBit(unsigned char port, unsigned char index){
  return ((port & (0x01 << index)) != 0x00);
}
int main(void) {
    /* Insert your solution below */
    DDRA = 0x00;
    DDRC = 0xFF;
    DDRB = 0xFF;
    while (1) {
      unsigned char portA_upper = (PINA & 0xF0) >> 4;
      unsigned char portA_lower = (PINA & 0x0F) << 4;
      PORTC = portA_lower + (PORTC & 0x0F);
      PORTB = (PORTB & 0xF0) + portA_upper;
    }
    return 1;
}
