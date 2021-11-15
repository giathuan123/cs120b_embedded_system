/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 11  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://drive.google.com/drive/folders/1zyelkDwS04xA2N8Z63zEzipkXeXe0OG0?usp=sharing
 */
#include <avr/io.h>
#include "timer.h"
#include "tasks.h"
#include "io.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum Game_State {init, playing, end};
enum Buttons_State{ buttons_init, up, down};
enum Display_State{ ds_init, display};

const unsigned char charPosition = 2;
unsigned char topObstacle = 10;
unsigned char bottomObstacle = 13;
unsigned char curPosition = 1; // 1 - up 0 - down
unsigned char gameStart = 0;

int Buttons_SM(int state){
  unsigned char moveUp = ~PINA & 0x02;
  unsigned char moveDown = ~PINA & 0x03;
  switch(state){
    case buttons_init:
      if(gameStart)
        state = down;
      break;
    case up:
      if(moveDown){
        state = down;
        curPosition = 0;
      }
      break;
    case down:
      if(moveUp){
        state = up;
        curPosition = 1;
      }
      break;
  }
  return state;
}
int Display_SM(int state){
  switch(state){
    case ds_init:
      if(gameStart){
        state = display;
      }
      break;
    case display:
      if(gameStart){
        LCD_ClearScreen();
        LCD_Cursor(topObstacle);
        LCD_WriteData('#');
        LCD_Cursor(15+bottomObstacle);
        LCD_WriteData('#');
        topObstacle = ((topObstacle > 0) ? topObstacle-1 : 16);
        bottomObstacle = (bottomObstacle > 0) ? bottomObstacle-1 : 16;
        LCD_Cursor(2);
        LCD_WriteData('P');
      }
      break;
  }
  return state;
}
int Game_SM(int state){
  unsigned char startButton = ~PINA & 0x01;
  switch(state){
    case init:
      if(startButton){
        state = playing;
        gameStart = 1;
      }
      break;
    case playing:
      if(curPosition){
        if(topObstacle == charPosition)
          state = end;
      }else{
        if(bottomObstacle == charPosition)
          state = end;
      } break;
    case end:
      gameStart = 0;
      LCD_DisplayString(1, "Thanks for playing");
      break;
  }
  return state;
}
task_t tasks[] = {
  { // Buttons
    .period = 20,
    .elaspedTime = 0,
    .TickFct = Buttons_SM,
    .state = buttons_init
  },
  {
    .period = 20,
    .elaspedTime = 0,
    .TickFct = Game_SM,
    .state = init
  },
  {
    .period = 200,
    .elaspedTime = 0,
    .TickFct = Display_SM,
    .state = ds_init
  }
};
int main(){
  DDRA = 0x00; PORTA = 0xFF;
  DDRC = 0xFF; PORTC = 0x00;
  DDRD = 0xFF; PORTD = 0x00;
  LCD_init();
  TimerSet(10);
  TimerOn();
  while(1){
    int i = 0;
    for(;i < 3; i++){
      if(tasks[i].elaspedTime >= tasks[i].period){
        tasks[i].state = tasks[i].TickFct(tasks[i].state);
        tasks[i].elaspedTime = 0;
      }
      tasks[i].elaspedTime+=20;
    }
    while(!TimerFlag){}
    TimerFlag = 0;
  } 
}
