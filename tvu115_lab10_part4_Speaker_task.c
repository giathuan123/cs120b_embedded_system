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

char sound = 0x00;

enum Speaker_States {init, on, off} Speaker_state;

int Speaker_tickFnc(int prevState){
  switch(prevState){
    case(init):
      prevState = off;
      sound = 0x01;
      break;
    case(off):
      sound = 0x00;
      prevState = on;
      break;
    case(on):
      sound = 0x01;
      prevState = off;
      break;
  } 
  
  return prevState;
}

struct task_t Speaker_task = {
  .period = 2,
  .elaspedTime = 0,
  .state = init,
  .TickFct = Speaker_tickFnc
};
