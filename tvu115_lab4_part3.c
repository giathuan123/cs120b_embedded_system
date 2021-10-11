/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab4  Exercise 3
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

enum States {startState, lock, hash_pressed, hash_released, unlock} state;

void tick(){
  switch(state){
    case(startState):
      state = lock;
      break;
    case(lock):
      if(PINA == 0x04){
        state = hash_pressed;
      }
      break;
    case(hash_pressed):
      if(PINA == 0x00){
        state = hash_released;
      }
      break;
    case(hash_released):
      if(PINA == 0x02){
        state = unlock;
      }else if(GetBit(PINA, 0) || GetBit(PINA, 2)){
        state = lock;
      }
      break;
    case(unlock):
      if(PINA == 0x80)
        state = lock;
      break;
    default:
      break;
  }
  switch(state){
    case(startState):
      PORTC = startState;
      PORTB = SetBit(PORTB, 0, 0);
      break;
    case(lock):
      PORTC = lock;
      PORTB = SetBit(PORTB, 0, 0);
      break;
    case(hash_pressed):
      PORTC = hash_pressed;
      break;
    case(hash_released):
      PORTC = hash_released;
      break;
    case(unlock):
      PORTC = unlock;
      PORTB = SetBit(PORTB, 0, 1);
      break;
    default:
      break;
  }
}
int main(void) {
    PORTC = startState;
    /* Insert your solution below */
    while (1) {
      tick();
    }
    return 1;
}
