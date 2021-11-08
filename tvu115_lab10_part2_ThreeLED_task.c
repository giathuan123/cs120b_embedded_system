/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 10  Exercise 2
 *	Exercise Description: Concurrent synch SM
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://drive.google.com/drive/folders/1vbyz9felmTvu6dzUBMSaL0-GajSoNqFA?usp=sharing
 */

#include "tasks.h"
#include <avr/io.h>

char lights = 0x01;

enum ThreeLED_states {init, on} ThreeLED_state;

int ThreeLED_tickFnc(int prevState){
  switch(prevState){
    case(init):
      prevState = on;
      lights = 0x01;
      break;
    case(on):
      lights = lights << 1;
      if(lights == 0x08)
        lights = 0x01;
      break;
  } 
  
  return prevState;
}

struct task_t ThreeLED_task = {
  .period = 300,
  .elaspedTime = 0,
  .state = init,
  .TickFct = ThreeLED_tickFnc
};


