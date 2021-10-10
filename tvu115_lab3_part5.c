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
    DDRD = 0x00;
    DDRB = 0x06; // 0110
    while (1) {
      unsigned int weight = ((unsigned int) PIND << 1) + GetBit(PINB, 0);
      PORTB = SetBit(PINB, 1, (weight >= 70));
      PORTB = SetBit(PINB, 2, (weight < 70 && weight > 5));
    }
    return 1;
}
