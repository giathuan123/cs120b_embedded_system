#include <avr/io.h>
#include "io.h"
#include "define.h"
enum displayState {init, display, end};

unsigned char lastBuffer[BUFFER_LEN];
extern char lives;
extern unsigned char endGame;
extern unsigned char startGame;
extern unsigned char buffer[BUFFER_LEN];
extern unsigned char reset;

unsigned char compareString(const unsigned char* str1, const unsigned char* str2, unsigned char size){
  int i;
  for( i = 0; i < size; i++){
    if(str1[i] != str2[i])
      return 0x00;
  }
  return 0x01;
}
void copyString(unsigned char* dest, const unsigned char* src, unsigned char size){
  int i;
  for( i = 0; i < size; i++){
    dest[i] = src[i];
  }
}

int displayTickFct(int state){
  switch(state){
    case init:
      if(startGame)
        state = display;
      break;
    case display:
      if(reset){
        state = init;
        LCD_DisplayString(1, "choose difficulty: 1, 2, 3");
        break;
      }
      if(endGame){
        state = end;
        break;
      }
      if(compareString(lastBuffer, buffer, BUFFER_LEN) == 0x00){
        LCD_DisplayString(FIRST_ROW, buffer);
        copyString(lastBuffer,buffer,  BUFFER_LEN);
      }
      break;
    case end:
      if(reset){
        state = init;
        LCD_DisplayString(1, "choose difficulty: 1, 2, 3");
        break;
      }
      if(compareString(lastBuffer, buffer, BUFFER_LEN) == 0x00){
        LCD_DisplayString(FIRST_ROW, buffer);
        copyString(lastBuffer, buffer, BUFFER_LEN);
      }
      break;
  }
  return state;
}
