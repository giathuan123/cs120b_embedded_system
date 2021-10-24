/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 6  Exercise 2
 *	Exercise Description:  Synch SM
 *
 *	I acknowledge all content contained herein, excluding template or example code, is my own original work.
 *      Demo Link: https://drive.google.com/drive/folders/1jZ0Wl-PjloW4bR6Ub9M-CygLvROtuzR4?usp=sharing
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include <timer.h>
enum synchSM_state{start, on, pressed, released, cont_press} state = start;
unsigned char lights = 0x00;
unsigned char cnt = 0;
void tick(){
  unsigned char button = ~PINA & 0x01;
  switch(state){
    case(start):
      state = on;
      break;
    case(on):
      if(button){
        state = pressed;
      }
      break;
    case(pressed):
      if(!button)
        state = released;
      break;
    case(released):
      if(button)
        state = cont_press;
      break;
    case(cont_press):
      if(!button)
        state = on;
      break;
  }
  switch(state){
    case(start):
      lights = 0x01;
      break;
      
    case(on):
      cnt++;
      if(cnt == 12){
      lights = lights << 1;
      cnt = 0;
      if((lights == 0x08 || lights == 0x00))
        lights = 0x01;
      }
      break;
  }
}

int main(){
  DDRB = 0xFF;
  DDRA = 0x00;
  PORTA = 0xFF;
  PORTB = 0x00;
  TimerSet(25);
  TimerOn();
  while(1){
    tick();
    PORTB = lights;
    while(!TimerFlag);
    TimerFlag = 0;
  }
}


