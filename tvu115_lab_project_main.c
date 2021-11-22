#include <avr/io.h>
#include "io.h"
#include "timer.h"
#define NUMBUTTONS 8
#define BUFFERLEN 17
unsigned char GetBit(unsigned char word, unsigned char position){
  return (word >> position) & 0x01; 
}
unsigned long sysperiod = 200;
unsigned char buffer[BUFFERLEN] = "";
unsigned char button[BUFFERLEN] = "";
unsigned char lastBuffer[BUFFERLEN] = "";

int main(){
  char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
  DDRB = 0xFF; PORTB = 0xFF;
  DDRC = 0xFF; PORTC = 0x00;
  DDRD = 0xFF; PORTD = 0x00;
  TimerSet(sysperiod);
  TimerOn();
  while(1){
    int pos = 0;
    int i;
    for(i = 0;i < 16; i++){
      buffer[i] = ' ';
    }
    for(i = 0; i < NUMBUTTONS; i++){
      if(GetBit(~PINB, NUMBUTTONS-1-i))
        buffer[i]=alpha[i];
    }
    if(compareString(lastBuffer, buffer, 16) == 0x00){
      LCD_DisplayString(1, buffer);
      copyString(lastBuffer,buffer, 16);
    }
    /* if(strcmp(buffer, lastBuffer) != 0x00){ */
    /*   LCD_ClearScreen(); */
    /*   strcpy(lastBuffer, buffer); */
    /* } */
    while(!TimerFlag){};
    TimerFlag = 0;
  }
}
