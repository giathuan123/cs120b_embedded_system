/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 9  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Demo Link: https://drive.google.com/drive/folders/1qxMZbnyULlgnZLIsT941jTXVYqZjIOWo?usp=sharing
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
void set_PWM(double freq){
  static double curr_freq;
  if(freq != curr_freq){
    if(!freq){ TCCR3B &= 0x08;}
    else{TCCR3B |= 0x03;}

    if(freq < 0.954){OCR3A = 0xFFFF;}
    else if(freq > 31250){OCR3A = 0x0000;}
    else{
      OCR3A = (short)(8000000 / (128*freq)) - 1;
    }
    TCNT3 = 0;
    curr_freq = freq;
  }
}
void PWM_on(){
  TCCR3A = (1 << COM3A0);
  TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
  set_PWM(0);
}
void PWM_off(){
  TCCR3A = 0x00;
  TCCR3B = 0x00;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0x40;
    DDRA = 0xFF;
    PORTA = 0xFF;
    PWM_on();
    /* Insert your solution below */
    while (1) {
      unsigned char buttonA0 = ~PINA & 0x01; 
      unsigned char buttonA1 = ~PINA & 0x02; 
      unsigned char buttonA2 = ~PINA & 0x04; 
      if((!buttonA0 && !buttonA1 && !buttonA2) || (buttonA1 && buttonA2) || (buttonA2 && buttonA0) || (buttonA1 && buttonA0)){
        set_PWM(0);
      }else if(buttonA0){
        set_PWM(261.62);
      }else if(buttonA1){
        set_PWM(293.66);
      }else if(buttonA2){
        set_PWM(329.23);
      }
    }
    return 1;
}
