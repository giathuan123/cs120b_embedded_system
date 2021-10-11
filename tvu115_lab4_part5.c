/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab4  Exercise 4
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
unsigned char password[] = {0x04, 0x01, 0x02, 0x01};
unsigned char curr_key;
unsigned char expected_key = 0;
enum States {startState, lock, key_press, key_release, unlock} state;

void tick(){
  switch(state){
    case(startState):
      state = lock;
      break;
    case(lock):
      if(PINA){
        curr_key = PINA;
        state = key_press;
      }
      break;
    case(key_press):
      if((PINA == 0x00)){
        state = key_release;
      }
      break;
    case(key_release):
      if(expected_key == 4){
        state = unlock;
      }else{
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
      break;
    case(lock):
      PORTB = SetBit(PORTB, 0, 0);
      break;
    case(key_press):
     break;
    case(key_release):
      if(curr_key == password[expected_key]){
        expected_key++;
        curr_key = 0; 
      }else{
        expected_key = 0;
        curr_key = 0; 
      }
      break;
    case(unlock):
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
