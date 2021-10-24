/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 6  Exercise 1
 *	Exercise Description: Synch SM 
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *      Demo Link: https://drive.google.com/drive/folders/1jZ0Wl-PjloW4bR6Ub9M-CygLvROtuzR4?usp=sharing
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include <timer.h>
enum synchSM_state{start, on} state = start;
unsigned char lights = 0x00;
void tick(){
  switch(state){
    case(start):
      state = on;
      break;
    case(on):
      break;
  }
  switch(state){
    case(start):
      lights = 0x01;
      break;
    case(on):
      lights = lights << 1;
      if(lights == 0x08 || lights == 0x00)
        lights = 0x01;
  }
}

int main(){
  DDRB = 0xFF;
  PORTB = 0x00;
  TimerSet(1000);
  TimerOn();
  while(1){
    tick();
    PORTB = lights;
    while(!TimerFlag);
    TimerFlag = 0;
  }
}


