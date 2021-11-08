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

#include <avr/io.h>
#include "timer.h"
#include "tasks.h"

#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

extern char lights;
extern char blinking;
extern char sound;

extern struct task_t ThreeLED_task;
extern struct task_t BlinkLED_task;
extern struct task_t Speaker_task;
extern struct task_t pollButton_task;

unsigned long systemPeriod = 1;

void runTask(struct task_t* tasks){
  if(tasks->elaspedTime >= tasks->period){
    tasks->state = tasks->TickFct(tasks->state);
    tasks->elaspedTime = 0;
  }
  tasks->elaspedTime += systemPeriod;
  
  return;
}
int main(void) {
    DDRB = 0x10;
    DDRA = 0xFF;
    PORTA = 0xFF;
    PORTB = 0x00;
    TimerSet(systemPeriod);
    TimerOn();
    char on = 0x00;
    while (1) {
      on = ~PINA & 0x04;
      runTask(&ThreeLED_task);
      runTask(&BlinkLED_task);
      runTask(&Speaker_task);
      runTask(&pollButton_task);
      if(!on)
        PORTB = blinking << 3 | lights;
      else
        PORTB = (sound << 4) | (blinking << 3) | lights;
      while(!TimerFlag){}
      TimerFlag = 0;
    }
    return 1;
}
