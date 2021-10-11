/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab4  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 * I acknowledge all content contained herein, excluding template or example
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

enum States {startState, init, increment, decrement, reset} state;

void tick(){
  switch(state){
    case(startState):
      PORTC = 7;
      state = init;
      break;
    case(init):
      if(GetBit(PINA, 0) && GetBit(PINA, 1)){
        PORTC = 0;
        state = reset;
      } else if(GetBit(PINA, 0)){
        PORTC = (PORTC < 9 ? PORTC + 1: PORTC);
        state = increment;
      } else if(GetBit(PINA, 1)){
        PORTC = (PORTC > 0 ? PORTC - 1: PORTC);
        state = decrement;
      }
      break;
    case(increment):
      if(GetBit(PINA, 0) && GetBit(PINA, 1)){
        PORTC = 0;
        state = reset;
      }else if(GetBit(PINA, 0) == 0x00){
        state = init;
      }
      break;
    case(decrement):
      if(GetBit(PINA, 0) && GetBit(PINA, 1)){
        PORTC = 0;
        state = reset;
      }else if(GetBit(PINA, 1) == 0x00){
        state = init;
      }
      break;
    case(reset):
      if((GetBit(PINA, 0) == 0x00) || (GetBit(PINA, 1) == 0x00))
        state = init;
      break;
    default:
      break;
  }
}
int main(void) {
    PORTC = 0x07;
    /* Insert your solution below */
    while (1) {
      tick();
    }
    return 1;
}
