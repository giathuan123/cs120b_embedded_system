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
  .period = 1000,
  .elaspedTime = 0,
  .state = init,
  .TickFct = ThreeLED_tickFnc
};


