/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab 9  Exercise 2
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
#include <timer.h>

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
enum state{ init, wait_press, playing} toggle_button = init;
enum scale{NO_SOUND, C4, D, E, F, G, A, B, C5};
enum scale tones[] = {C4, E, F, NO_SOUND, F, NO_SOUND, F, B, G};
unsigned short period = 100;
unsigned char playTimes[] = {5, 8, 2, 4, 2, 4, 2, 4, 5};
unsigned char elaspePlaytime = 0;
unsigned char playIndex = 0;
double scaleChart[9] = {0, 261.63, 293.66, 329.63, 349.23, 392, 440, 493.88, 523.25};
unsigned char on = 0x00;

void playTunes(){
  if(playIndex < 9){
    if(elaspePlaytime < playTimes[playIndex]){
      elaspePlaytime++; 
    }else{
      playIndex++;
      set_PWM(scaleChart[tones[playIndex]]);
      elaspePlaytime = 0;
    }
  }
}
void tick(){
  unsigned char buttonA0 = ~PINA & 0x01; 
  static char wait;
  switch(toggle_button){
    case(init):
      playIndex = 0;
      toggle_button = wait_press;
      break;
    case(wait_press):
      if(buttonA0){
        toggle_button = playing;
      }
      break;
    case(playing):
      if(playIndex < 9){
        playTunes();
      };
      if(!buttonA0 && playIndex >= 9){
        toggle_button = init;
      }
      break;
  }
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0x40;
    DDRA = 0xFF;
    TimerSet(period);
    TimerOn();
    PORTA = 0xFF;
    PWM_on();
    /* Insert your solution below */
    while (1) {
      tick();      
      while(!TimerFlag){}
      TimerFlag = 0;
    }
    return 1;
}
