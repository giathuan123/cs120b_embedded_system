/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 10  Exercise 1
 *	Exercise Description: Concurrent synch SM
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://drive.google.com/drive/folders/1vbyz9felmTvu6dzUBMSaL0-GajSoNqFA?usp=sharing
 */

#include "tasks.h"
#include <avr/io.h>

char blinking = 0x00;

enum BlinkingLED_States {init, on, off} BlinkingLED_state;

int BlinkLED_tickFnc(int prevState){
  switch(prevState){
    case(init):
      prevState = off;
      blinking = 0x01;
      break;
    case(off):
      blinking = 0x00;
      prevState = on;
      break;
    case(on):
      blinking = 0x01;
      prevState = off;
      break;
  } 
  
  return prevState;
}

struct task_t BlinkLED_task = {
  .period = 1000,
  .elaspedTime = 0,
  .state = init,
  .TickFct = BlinkLED_tickFnc
};
