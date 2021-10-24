/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 7  Exercise 2
 *	Exercise Description:  Synch SM
 *
 *	I acknowledge all content contained herein, excluding template or example code, is my own original work.
 *      Demo Link: https://drive.google.com/file/d/1jqMU3f9RWbv8WAHy0Bl706GIRTlDDmzI/view?usp=sharing
 */

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
#include <timer.h>
#include "io.h"
enum synchSM_state{start, on, pressed, released, cont_press} state = start;

unsigned char lights = 0x00;
unsigned char cnt = 0;
unsigned char points = 5;
unsigned char winner = 0;
void printPoints(){
  LCD_Cursor(1);
  LCD_WriteData(points + '0');
}

void printWinner(){
  LCD_DisplayString(1, "Winner!!");
  winner = 1;
}

void tick(){
  unsigned char button = ~PINA & 0x01;
  switch(state){
    case(start):
      printPoints();
      state = on;
      break;
    case(on):
      if(button){
        if(lights == 0x02){
          points++;
          if(points == 9){
            printWinner();
          }else{
            printPoints();
          }
        }
        else{
          if(points > 0)
            points--;
          printPoints();
        }
        state = pressed;
      }
      break;
    case(pressed):
      if(!button)
        state = released;
      break;
    case(released):
      if(button){
        if(winner){
          winner = 0;
          LCD_ClearScreen();
          points = 5;
          printPoints();
        } 
        state = cont_press;
      }
        
      break;
    case(cont_press):
      if(!button)
        state = on;
      break;
  }
  switch(state){
    case(start):
      lights = 0x01;
      break;
      
    case(on):
      cnt++;
      if(cnt == 12){
      lights = lights << 1;
      cnt = 0;
      if((lights == 0x08 || lights == 0x00))
        lights = 0x01;
      }
      break;
  }
}

int main(){
  DDRB = 0xFF;
  DDRA = 0x00;
  DDRC = DDRD = 0xFF;
  PORTC = PORTD = 0x00;
  PORTA = 0xFF;
  PORTB = 0x00;
  LCD_init();
  TimerSet(25);
  TimerOn();
  while(1){
    tick();
    PORTB = lights;
    while(!TimerFlag);
    TimerFlag = 0;
  }
}
