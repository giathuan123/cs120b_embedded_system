/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab5  Exercise 1
 *	Exercise Description: [optional - include for your own benefit] I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://drive.google.com/file/d/1e7gXcBeoVQB4FSt6ZQItFbDCH57qCB6S/view?usp=sharing
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum ButtonStates {start, off_release, on_press, on_release, off_press} buttonA0 = off_release;
unsigned char button = 0;
unsigned char carry = 0;
unsigned char lights = 1;
void tick(){
  switch(buttonA0){
    case(start):
      buttonA0 = off_release;
      break;
    case(off_release):
      if(button){
        lights = lights << 1;
        if((lights & 0x3F) == 0x00)
          lights = 0x01;
        buttonA0 = on_press;
      }
      break;
    case(on_press):
      if(!button){
        buttonA0 = on_release;
      }
      break;
    case(on_release):
      if(button){
        lights = lights << 1;
        if((lights & 0x3F) == 0x00)
          lights = 0x01;
        buttonA0 = on_press;
      }
      break;
    case(off_press):
      if(!button)
        buttonA0 = off_release;
      break;
  }  
}
int main(void) {
  DDRA = 0x00;
  PORTA = 0xFF;
  DDRB = 0xFF; 
  PORTB = 0x00;
  
  while(1){
    button = ~PINA & 0x01;
    tick();
    PORTB = lights; 
  }
}
