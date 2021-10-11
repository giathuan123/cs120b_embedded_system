/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
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

enum States {startState, wait_press, press, off_press, second_press} state;

void tick(){
  switch(state){
    case(startState):
      state = wait_press;
      break;
    case(wait_press):
      if(GetBit(PINA, 0))
        state = press;
      break;
    case(press):
      if(GetBit(PINA, 0) == 0x00)
        state = off_press;
      break;
    case(off_press):
      if(GetBit(PINA, 0))
        state = second_press;
      break;
    case(second_press):
      if(GetBit(PINA, 0) == 0x00)
        state = wait_press;
      break;
    default:
      break;
  }
  switch(state){
    case(startState):
      PORTB = 0x01;
      break;
    case(wait_press):
      PORTB = 0x01;
      break;
    case(press):
      PORTB = 0x02;
      break;
    case(off_press):
      PORTB = 0x02;
      break;
    case(second_press):
      PORTB = 0x01;
      break;
  }
}
int main(void) {
    /* Insert DDR and PORT initializations */
    PORTB = 0x01;
    /* Insert your solution below */
    while (1) {
      tick();
    }
    return 1;
}
