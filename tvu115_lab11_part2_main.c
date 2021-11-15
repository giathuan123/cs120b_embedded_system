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
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
const unsigned char* displayString = "CS120B is Legend... wait for it DARY!";
enum String_States {init, display};
unsigned char currentPosition = 0;
unsigned char* bufferString = "                ";
void prepareDisplay(){
  currentPosition %= 37;
  // move left
  int i;
  for(i = 0;i < 15; i++){
    bufferString[i] = bufferString[i+1];
  }
  bufferString[15] = displayString[currentPosition];
  currentPosition++;
}
int String_SM(int state){
  switch(state){
    case init:
      state = display;
      break;
    case display:
      prepareDisplay();
      LCD_DisplayString(0, bufferString);
      break;
  }
  return state;
}
task_t task = {
  .period = 800,
  .elaspedTime = 0,
  .TickFct = String_SM,
  .state = init 
};
int main(){
  DDRC = 0xFF; PORTC=0x00;
  DDRD = 0xFF; PORTD = 0x00;
  LCD_init();
  TimerSet(100); 
  TimerOn();
  while(1){
   if(task.elaspedTime >= task.period){
     task.state = task.TickFct(task.state);
     task.elaspedTime = 0;
   }  
   task.elaspedTime += 100;
   while(!TimerFlag){}
   TimerFlag = 0;
  }
}
