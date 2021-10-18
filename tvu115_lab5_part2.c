/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab4  Exercise 2
 *	Exercise Description: [optional - include for your own benefit] I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char SetBit(unsigned char port, unsigned char index, unsigned char bit){
  return (bit ? (port | 0x01 << index) : (port & ~(0x01 << index)));
}
unsigned char GetBit(unsigned char port, unsigned char index){
  return ((port & (0x01 << index)) != 0x00);
}
enum ButtonStates {released, pressed} buttonA0, buttonA1;
enum States {startState, init, running, reset} state;
unsigned char cnt = 0;

void GetButtonState(enum ButtonStates *buttonState,unsigned char bit, void (*action)()){
  switch(*buttonState){
    case(released):
      if(bit){
        action();
        *buttonState = pressed;
      }
    case(pressed):
      if(bit == 0x00){
        *buttonState = released;
      }
  }
}
void increment(){
  cnt = (cnt < 9) ? cnt + 1 : cnt;
}
void decrement(){
  cnt = (cnt > 0) ? cnt - 1: cnt;
}

void tick(){
  unsigned char bit1 = ~PINA & 0x01;
  unsigned char bit2 = ~PINA & 0x02;
  GetButtonState(&buttonA0, bit1, increment);
  GetButtonState(&buttonA1, bit2, decrement);
  switch(state){
    case(startState):
      state = init;
      break;
    case(init):
      state = running;
      break;
    case(running):
      if(buttonA0 == pressed && buttonA1 == pressed){
        state = reset;
      }
      break;
    case(reset):
      if(buttonA0 == released && buttonA0 == released){
        state = running;
      }
  }
  switch(state){
    case(init):
      cnt = 8;
      break;
    case(reset):
      cnt = 0;
  } 
}
int main(void) {
    DDRC = 0xFF;
    PORTC = 0x07;
    DDRA =0x00;
    PORTA = 0xFF;
    /* Insert your solution below */
    buttonA0 = released;
    buttonA1 = released;
    while (1) {
      tick();
      PORTC = cnt;
    }
    return 1;
}
