#ifndef __PWM__
#define __PWM__
#include <avr/io.h>

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
#endif
