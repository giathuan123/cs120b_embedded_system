/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 10  Exercise 4
 *	Exercise Description: Concurrent synch SM
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://drive.google.com/drive/folders/1vbyz9felmTvu6dzUBMSaL0-GajSoNqFA?usp=sharing
 */

#include "tasks.h"
#include <avr/io.h>

extern struct task_t Speaker_task;

enum volume_States {init, down, neutral, up} volume_state;

void turnUpFreq(unsigned long *speakerPeriod){
  if(*speakerPeriod > 1){
    (*speakerPeriod)--;
  }
  return;
}
void turnDownFreq(unsigned long *speakerPeriod){
  // assuming lowest frequency possible is 20Hz
  if(*speakerPeriod < 50)
    (*speakerPeriod)++;
  return;
}
int pollButton_tickFnc(int prevState){
  char upButton = ~PINA & 0x01;
  char downButton = ~PINA & 0x02;
  switch(prevState){
    case(init):
      prevState = neutral;
      break;
    case(neutral):
      if(upButton){
        turnUpFreq(&(Speaker_task.period));
        prevState = up;
      }else if(downButton){
        turnDownFreq(&(Speaker_task.period));
        prevState = down;
      }
      break;
  } 
  switch(prevState){
    case(up):
      if(!upButton){
        prevState = neutral;
      }
      break;
    case(down):
      if(!downButton){
        prevState = neutral;
      }
      break;
  }
  return prevState;
}

struct task_t pollButton_task = {
  .period = 1,
  .elaspedTime = 0,
  .state = init,
  .TickFct = pollButton_tickFnc
};
