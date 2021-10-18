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
unsigned char cnt = 0;

void tick(){
  switch(state){
    case(startState):
      state = init;
      break;
    case(init):
      if(GetBit(PINA, 0) && GetBit(PINA, 1)){
        state = reset;
      } else if(GetBit(PINA, 0)){
        state = increment;
      } else if(GetBit(PINA, 1)){
        state = decrement;
      }
      break;
    case(increment):
      if(GetBit(PINA, 0) && GetBit(PINA, 1)){
        state = reset;
      }else if(GetBit(PINA, 0) == 0x00){
        state = init;
      }
      break;
    case(decrement):
      if(GetBit(PINA, 0) && GetBit(PINA, 1)){
        state = reset;
      }else if(GetBit(PINA, 1) == 0x00){
        state = init;
      }
      break;
    case(reset):
      state = init;
      break;
    default:
      break;
  }
  switch(state){
    case(init):
      cnt = 7;
      break;
    case(increment):
      cnt = (cnt < 9) ? cnt + 1: cnt;
      break;
    case(decrement):
      cnt = (cnt > 0) ? cnt - 1: cnt;
      break;
    case(reset):
      cnt = 0;
  }
}
int main(void) {
    DDRC = 0xFF;
    DDRA = 0x00;
    PORTA = 0x00;
    PORTC = 0x07;
    /* Insert your solution below */
    while (1) {
      tick();
      PORTC = cnt;
    }
    return 1;
}
