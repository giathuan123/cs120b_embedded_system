/*	Author: thuanvu
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 3 Exercise 1
 *	Exercise Description: Count the number of 1s on ports A and B and output that number on portC 
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char getBit(unsigned char p, unsigned char idx){
  return ((p & (0x01 << idx)) != 0);
}
unsigned char countPort(unsigned char port, unsigned char portSize){
  unsigned char cnt = 0;
  int i;
  for(i = 0; i < portSize; ++i)
    cnt += getBit(port, i);
  return cnt;
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    DDRB = 0x00;
    DDRC = 0xFF;
    /* Insert your solution below */
    while (1) {
      unsigned char cnt;
      cnt = countPort(PINA, 8);
      cnt += countPort(PINB, 8);
      PORTC = cnt;
    }
    return 1;
}
