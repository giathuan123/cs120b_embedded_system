/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 11  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "tasks.h"
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
unsigned char key;
enum Keypad_States { kp_init, polling } Keypad_state = kp_init;
enum Display_States { ds_init, display_state } Display_state = ds_init;

unsigned char getbit(unsigned char port, unsigned char position){
  return ((port >> position) & 0x01);
}
unsigned char getkeypadkey(){
  PORTC = 0xef;
  asm("nop");
  if(getbit(PINC, 0) == 0) return '1';
  if(getbit(PINC, 1) == 0) return '4';
  if(getbit(PINC, 2) == 0) return '7';
  if(getbit(PINC, 3) == 0) return '*';
  PORTC = 0xdf;
  asm("nop"); 
  if(getbit(PINC, 0) == 0) return '2';
  if(getbit(PINC, 1) == 0) return '5';
  if(getbit(PINC, 2) == 0) return '8';
  if(getbit(PINC, 3) == 0) return '0';
  PORTC = 0xbf;
  asm("nop"); 
  if(getbit(PINC, 0) == 0) return '3';
  if(getbit(PINC, 1) == 0) return '6';
  if(getbit(PINC, 2) == 0) return '9';
  if(getbit(PINC, 3) == 0) return '#';
  PORTC = 0x7f;
  asm("nop"); 
  if(getbit(PINC, 0) == 0) return 'A';
  if(getbit(PINC, 1) == 0) return 'B';
  if(getbit(PINC, 2) == 0) return 'C';
  if(getbit(PINC, 3) == 0) return 'D';
  
  return '\0';
}
int Keypad_SM(int state){
  switch(state){
    case kp_init:
      state = polling;
      break;
    case polling:
      key = getkeypadkey(); 
      break;
  }
  return state;
}
void display(unsigned char x){
      switch(x){
      case '\0': PORTB = 0x1F; break;
                 
      case '1': PORTB = 0x01; break;
      case '4': PORTB = 0x04; break;
      case '7': PORTB = 0x07; break;
      case '*': PORTB = 0x0E; break;
                
      case '2': PORTB = 0x02; break;
      case '5': PORTB = 0x05; break;
      case '8': PORTB = 0x08; break;
      case '0': PORTB = 0x00; break;
                
      case '3': PORTB = 0x03; break;
      case '6': PORTB = 0x06; break;
      case '9': PORTB = 0x09; break;
      case '#': PORTB = 0x0F; break;
                
      case 'A': PORTB = 0x0A; break;
      case 'B': PORTB = 0x0B; break;
      case 'C': PORTB = 0x0C; break;
      case 'D': PORTB = 0x0D; break;
      }
}

int Display_SM(int state){
  switch(state){
    case ds_init:
      state = display_state;
      break;
    case display_state:
      display(key);
      break;
  }
  return state;
}
unsigned short systemPeriod = 50;
task_t tasks[] = {
  {
  .period=50,
  .elaspedTime=50,
  .state=kp_init,
  .TickFct=Keypad_SM,
  },
  {
  .period=50,
  .elaspedTime=50,
  .state=ds_init,
  .TickFct=Display_SM,
  }
};
int main(){
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xF0; PORTC = 0x0F;
    TimerSet(systemPeriod);
    TimerOn();
    while(1){
      int i = 0;
      for(;i < 2;i++){
        if(tasks[i].elaspedTime >= tasks[i].period){
          tasks[i].state = tasks[i].TickFct(tasks[i].state);
          tasks[i].elaspedTime = 0;
        } 
        tasks[i].elaspedTime += systemPeriod;
      }
      while(!TimerFlag){}
      TimerFlag = 0;
    }
}

