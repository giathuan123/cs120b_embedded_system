#include <avr/io.h>
#include "io.h"
#include "timer.h"
#include "tasks.h"

extern int gameTickFct(int state);
extern int soundTickFct(int state);
extern int displayTickFct(int state);
unsigned char GetBit(unsigned char port, unsigned char pos){
  return (port >> pos) & 0x01;
}
unsigned short sysperiod = 50;

task_t tasks[] = {
  {
    .period = 100,
    .elaspedTime = 100,
    .state = 0,
    .TickFct = gameTickFct,
  },
  {
    .period = 50,
    .elaspedTime = 50,
    .state = 0,
    .TickFct = displayTickFct,
  },
  {
    .period = 50,
    .elaspedTime = 50,
    .state = 0,
    .TickFct = soundTickFct,
  }
};

void runTasks(task_t *tasks, int size){
  int i;
  for(i = 0; i < size; i++){
    if(tasks[i].period <= tasks[i].elaspedTime){
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elaspedTime = 0;
    }
    tasks[i].elaspedTime += sysperiod;
  }
}

int main(){
  DDRA = 0xFF; PORTA = 0xFF;
  DDRB = 0xFF; PORTB = 0xFF;
  DDRC = 0xFF; PORTC = 0x00;
  DDRD = 0xFF; PORTD = 0x00;
  TimerSet(sysperiod);
  TimerOn();
  LCD_init();
  LCD_DisplayString(1, "choose difficulty: 1, 2, 3");
  while(1){
    runTasks(&tasks, 3);
    while(!TimerFlag){}
    TimerFlag = 0;
  }
  
}

