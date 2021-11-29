/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Game
 *	Exercise Description: [optional - include for your own benefit]
 *      Demo Link: https://drive.google.com/drive/folders/173Dt0iPtX2V9g_A5oSe08jxe19fHSaDX?usp=sharing
 * I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "tasks.h"
#include "timer.h"
#include "define.h"

const char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', '#'};

unsigned char GetBit(unsigned char word, unsigned char position){
  return (word >> position) & 0x01; 
}
extern int displayTickFct(int state);
extern int soundTickFct(int state);

unsigned long sysperiod = 10;
unsigned char buffer[BUFFER_LEN] = "";
unsigned char lastBuffer[BUFFER_LEN] = "";

void runTasks(task_t* tasks, int numberOfTasks){
  int i;
  for(i = 0; i < numberOfTasks; i++){
    if(tasks[i].elaspedTime >= tasks[i].period){
      tasks[i].state = tasks[i].TickFct(tasks[i].state);
      tasks[i].elaspedTime = 0;
    }
    tasks[i].elaspedTime += sysperiod;
  }
}

task_t tasks[] =
{
  {
    .period = 50,
    .state = 0,
    .elaspedTime = 0,
    .TickFct = displayTickFct,
  },
  {
    .period = 50,
    .state = 0,
    .elaspedTime = 0,
    .TickFct = soundTickFct,
  }
};

int main(){
  DDRB = 0xFF; PORTB = 0xFF;
  DDRC = 0xFF; PORTC = 0x00;
  DDRD = 0xFF; PORTD = 0x00;
  TimerSet(sysperiod);
  TimerOn();
  while(1){
    int i;
    for(i = 0;i < 16; i++){
      buffer[i] = ' ';
    }
    for(i = 0; i < NUMBUTTONS; i++){
      if(GetBit(~PINB, NUMBUTTONS-1-i))
        buffer[i]=alpha[i];
    }
    runTasks(&tasks, 2);
    while(!TimerFlag){};
    TimerFlag = 0;
  }
}
