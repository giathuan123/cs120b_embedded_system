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
#include "timer.h"
#include "tasks.h"
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
unsigned char currentDisplay = 0;
unsigned char lastDisplay = 0;
/* unsigned char position = 0; */
enum Keypad_States { kp_init, polling };
enum Display_States { ds_init, display};

unsigned char getbit(unsigned char port, unsigned char position){
  return ((port >> position) & 0x01);
}
unsigned char getkeypadkey(){
  PORTA = 0xef;
  asm("nop");
  if(getbit(PINA, 0) == 0) return '1';
  if(getbit(PINA, 1) == 0) return '4';
  if(getbit(PINA, 2) == 0) return '7';
  if(getbit(PINA, 3) == 0) return '*';
  PORTA = 0xdf;
  asm("nop"); 
  if(getbit(PINA, 0) == 0) return '2';
  if(getbit(PINA, 1) == 0) return '5';
  if(getbit(PINA, 2) == 0) return '8';
  if(getbit(PINA, 3) == 0) return '0';
  PORTA = 0xbf;
  asm("nop"); 
  if(getbit(PINA, 0) == 0) return '3';
  if(getbit(PINA, 1) == 0) return '6';
  if(getbit(PINA, 2) == 0) return '9';
  if(getbit(PINA, 3) == 0) return '#';
  PORTA = 0x7f;
  asm("nop"); 
  if(getbit(PINA, 0) == 0) return 'A';
  if(getbit(PINA, 1) == 0) return 'B';
  if(getbit(PINA, 2) == 0) return 'C';
  if(getbit(PINA, 3) == 0) return 'D';
  
  return '\0';
}

int Keypad_SM(int state){
  unsigned char curKey;
  switch(state){
    case kp_init:
      state = polling;
      break;
    case polling:
      curKey = getkeypadkey(); 
      if(curKey != '\0')
        currentDisplay = curKey;
      break;
  }
  return state;
}
int Display_SM(int state){
  switch(state){
    case ds_init:
      state = display;
      break;
    case display:
      if(currentDisplay != lastDisplay){
        lastDisplay = currentDisplay;
        LCD_Cursor(0);
        LCD_WriteData(currentDisplay);
      }
      break;
  }
  return state;
}
task_t tasks[] = {
  {
    .period = 50,
    .TickFct = Keypad_SM,
    .elaspedTime = 0,
    .state = kp_init
  },
  {
    .period = 100,
    .TickFct = Display_SM,
    .elaspedTime  = 0,
    .state = ds_init
  }
};
int main(){
  DDRA = 0xF0; PORTA = 0x0F;
  DDRC = 0xFF; PORTC = 0x00;
  DDRD = 0xFF; PORTD = 0x00;
  TimerSet(50);
  TimerOn();
  LCD_init();
  /* LCD_DisplayString(1, "Congratulations!"); */
  while(1){
    int i = 0;
    for(;i < 2; i++){
      if(tasks[i].elaspedTime >= tasks[i].period){
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elaspedTime = 0;
      }
      tasks[i].elaspedTime+=50;
    }
    while(!TimerFlag){};
    TimerFlag = 0;
  }
}
