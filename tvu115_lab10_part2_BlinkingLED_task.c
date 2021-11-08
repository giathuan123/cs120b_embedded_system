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
