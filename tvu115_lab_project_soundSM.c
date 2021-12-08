/*	Author: thuanvu
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Game Project
 *	Exercise Description: Count the number of 1s on ports A and B and output that number on portC 
 *      Demo Link: https://drive.google.com/drive/folders/173Dt0iPtX2V9g_A5oSe08jxe19fHSaDX?usp=sharing
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "pwm.h"
#include "define.h"

extern unsigned char GetBit(unsigned char word, unsigned char position);
extern double gameSong[];
extern char startGame;
extern unsigned short songSize;
extern unsigned short curNote;
extern unsigned char reset;
extern char lives;
enum soundState { init, playSound };
double notes[] = {
  A_NOTE,
  B_NOTE,
  C_NOTE,
  D_NOTE,
  E_NOTE,
  F_NOTE,
};

int soundTickFct(int state){
  char soundSet;
  switch(state){
    case init:
      if(startGame){
        state = playSound;
        PWM_on();
      }
      break;
    case playSound:
      if(reset || lives == 0 || curNote >= songSize - 1){
        state = init;
        set_PWM(0);
        break;
      }
      state = playSound;
      set_PWM(gameSong[curNote]);
      break;
  }
  return state;
}
