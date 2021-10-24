/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 6  Exercise 3
 *	Exercise Description: Synch SM 
 *
 *	I acknowledge all content contained herein, excluding template or example code, is my own original work.
 *      Demo Link: https://drive.google.com/drive/folders/1jZ0Wl-PjloW4bR6Ub9M-CygLvROtuzR4?usp=sharing
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include <timer.h>
enum synchSM_state{start, wait_state, increment_state, decrement_state, reset_state} state = start;
unsigned char lights = 0x00;
unsigned char cnt = 0;

void increment(unsigned char* lights){
  unsigned char currLight = *lights;
  currLight = (currLight < 9) ? currLight + 1 : 9;
  *lights = currLight;
}
void decrement(unsigned char* lights){
  unsigned char currLight = *lights;
  currLight = (currLight > 0) ? currLight - 1 : 0;
  *lights = currLight;
}
void tick(){
  unsigned char buttonA0 = ~PINA & 0x01;
  unsigned char buttonA1 = ~PINA & 0x02;
  switch(state){
    case(start):
      lights = 0x07;
      state = wait_state;
      break;
    case(wait_state):
      if(buttonA0 && !buttonA1){
        increment(&lights);
        state = increment_state;
      }
      if(buttonA1 && !buttonA0){
        decrement(&lights);
        state = decrement_state;
      }
      if(buttonA0 && buttonA1)
        state = reset_state;
      break;
    case(increment_state):
      if(buttonA0 && buttonA1)
        state = reset_state;
      if(!buttonA0)
        state = wait_state;
      if(cnt == 10){
        increment(&lights);
        cnt = 0;
      }
      break;
    case(decrement_state):
      if(buttonA0 && buttonA1)
        state = reset_state;
      if(!buttonA1)
        state = wait_state;
      if(cnt == 10){
        decrement(&lights);
        cnt = 0;
      }
      break;
    case(reset_state):
      if(!(buttonA0 && buttonA1))
        state = wait_state;
      break;
  }
  switch(state){
    case(start):
      break;
    case(wait_state):
      cnt = 0;
      break;
    case(increment_state):
      cnt ++;
      break;
    case(decrement_state):
      cnt++;
      break;
    case(reset_state):
      lights = 0; 
      break; 
  }
}

int main(){
  DDRB = 0xFF;
  DDRA = 0x00;
  PORTA = 0xFF;
  PORTB = 0x00;
  TimerSet(100);
  TimerOn();
  while(1){
    tick();
    PORTB = lights;
    while(!TimerFlag);
    TimerFlag = 0;
  }
}


