/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 7  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example code, is my own original work.
 *      Demo Link: 
 */

#include <avr/io.h>
#include "io.h"
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
  LCD_Cursor(1);
  LCD_WriteData(currLight + '0');
  *lights = currLight;
}
void decrement(unsigned char* lights){
  unsigned char currLight = *lights;
  currLight = (currLight > 0) ? currLight - 1 : 0;
  LCD_Cursor(1);
  LCD_WriteData(currLight + '0');
  *lights = currLight;
}
void tick(){
  unsigned char buttonA0 = ~PINA & 0x01;
  unsigned char buttonA1 = ~PINA & 0x02;
  switch(state){
    case(start):
      lights = 0x07;
      LCD_Cursor(1);
      LCD_WriteData(lights + '0');
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
  DDRA = 0x00;
  PORTA = 0xFF;
  DDRC = 0xFF; PORTC = 0x00;
  DDRD = 0xFF; PORTD = 0x00; 
  LCD_init();
  TimerSet(100);
  TimerOn();
  while(1){
    tick();
    while(!TimerFlag);
    TimerFlag = 0;
  }
}


