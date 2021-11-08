/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 10  Exercise 1
 *	Exercise Description: Concurrent synch SM
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#include "tasks.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
extern char lights;
extern char blinking;
extern struct task_t ThreeLED_task;
extern struct task_t BlinkLED_task;
/* extern struct task_t BlinkLED_task; */
unsigned long period;

void runTask(struct task_t* tasks){
  if(tasks->elaspedTime == tasks->period){
    tasks->state = tasks->TickFct(tasks->state);
    tasks->elaspedTime = 0;
  }else{
    tasks->elaspedTime += period;
  }
  return;
}
int main(void) {
    DDRB = 0x00;
    PORTB = 0x00;
    /* Insert DDR and PORT initializations */
    period = 100;
    TimerSet(period);
    TimerOn();
    /* Insert your solution below */
    while (1) {
      runTask(&ThreeLED_task);
      runTask(&BlinkLED_task);
      PORTB = blinking << 3 | lights;
      while(!TimerFlag){}
      TimerFlag = 0;
    }
    return 1;
}
