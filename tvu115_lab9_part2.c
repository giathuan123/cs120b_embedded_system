/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 9  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum state{ init, wait_press, wait_release} toggle_button = init;
enum state up_button = wait_press,down_button = wait_press;
enum scale{C4, D, E, F, G, A, B, C5} sound_scale = C4;
double scaleChart[8] = {261.63, 293.66, 329.63, 349.23, 392, 440, 493.88, 523.25};
unsigned char on = 0x00;

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

void tick(){
  unsigned char buttonA0 = ~PINA & 0x01; 
  unsigned char buttonA1 = ~PINA & 0x02; 
  unsigned char buttonA2 = ~PINA & 0x04; 
  switch(toggle_button){
    case(init):
      sound_scale = C4;
      toggle_button = wait_press;
      break;
    case(wait_press):
      if(buttonA0){
        on = !on;
        toggle_button = wait_release;
      }
      break;
    case(wait_release):
      if(!buttonA0){
        toggle_button = init;
      }
      break;
  }
  switch(up_button){
    case(wait_press):
      if(buttonA1 && (sound_scale < C5)){
          sound_scale++;
          up_button = wait_release;
      }
      break;
    case(wait_release):
      if(!buttonA1){
        up_button = wait_press;
      }
      break;
  }
  switch(down_button){
    case(wait_press):
      if(buttonA2 && (sound_scale > C4)){
          sound_scale--;
          down_button = wait_release;
      }
      break;
    case(wait_release):
      if(!buttonA2){
        down_button = wait_press;
      }
      break;
  }
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0x40;
    DDRA = 0xFF;
    PORTA = 0xFF;
    PWM_on();
    /* Insert your solution below */
    while (1) {
      tick();      
      if(on){
        set_PWM(scaleChart[sound_scale]);
      }else{
        set_PWM(0);
      }
    }
    return 1;
}
