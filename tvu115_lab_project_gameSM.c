#include  <avr/io.h>
#include "define.h"
#include "io.h"
#include "gameSong.h"

enum gameState {init, playing, end};
/* extern  */
#define NOTE_A 0x20
#define NOTE_B 0x10
#define NOTE_C 0x08
#define NOTE_D 0x04
#define NOTE_E 0x02
#define NOTE_F 0x01

extern unsigned char GetBit(unsigned char port, unsigned char position);

unsigned char buffer[BUFFER_LEN] = "";
unsigned char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F'};
unsigned char endGame = 0;
unsigned char startGame = 0;
unsigned short curNote = 0;
unsigned char move = 0;
unsigned char reset;
unsigned short songSize = sizeof(gameSong)/sizeof(double);
char lives;
unsigned char getNoteKey(double note){
  if(note == A_NOTE){
    return NOTE_A;
  }else if(note == B_NOTE){
    return NOTE_B;
  }else if(note == C_NOTE){
    return NOTE_C;
  }else if(note == D_NOTE){
    return NOTE_D;
  }else if(note == E_NOTE){
    return NOTE_E;
  }else if(note == F_NOTE){
    return NOTE_F;
  }else if(note == 0){
    return 0;
  }
}
unsigned char getKeyAlpha(double note){
  if(note == A_NOTE){
    return 'A';
  }else if(note == B_NOTE){
    return 'B';
  }else if(note == C_NOTE){
    return 'C';
  }else if(note == D_NOTE){
    return 'D';
  }else if(note == E_NOTE){
    return 'E';
  }else if(note == F_NOTE){
    return 'F';
  }else{
    return ' ';
  }
}
void buildSongDisplay(int note){
  int i;
  for(i = 0;i < 16; i++){
    if(note + i < songSize - 1)
      buffer[SECOND_ROW + i] = getKeyAlpha(gameSong[note+i]);
    else
      buffer[SECOND_ROW + i] = 'x';
  }
}
int gameTickFct(int state){
  static char notePressCorrect;
  static char counter;
  static char keyPressed = 0;
  char easy, medium, hard;
  int i;
  switch(state){
  case init:
    easy = GetBit(~PINB, 5);
    medium = GetBit(~PINB, 4);
    hard = GetBit(~PINB, 3);
    buffer[13] = reset + 0x30;
    if(easy ^ hard ^ medium){
      startGame = 1;
      reset = 0;
      state = playing;
      curNote = 0;
      counter = 0;
      keyPressed = 0;
      lives = 3;
      notePressCorrect = 0;
      for(i = 0;i < BUFFER_LEN; i++){
        buffer[i] = ' ';
      }
      buildSongDisplay(curNote);
    }
    if(easy){
      move = 8;
    }else if(medium){
      move = 6;
    }else if(hard){
      move = 4;
    }
    break;
  case playing:
    reset = GetBit(~PINA, 0);
    if(reset){
      state = init;
      startGame = 0;
      break;
    } 
    if(!keyPressed) 
      keyPressed = (~PINB & 0x3F);
    if(lives == 0 || curNote == songSize ){
      state = end;
      break;
    }
    for(i = 0;i < 16; i++){
      buffer[i] = ' ';
    }
    char curLive = lives;
    char pos = 0;
    while(curLive){
      buffer[15-pos] = (curLive % 10) + 0x30;
      pos++;
      curLive /= 10;
    }
    for(i = 0; i < NUMBUTTONS; i++){
      if(GetBit(~PINB, NUMBUTTONS-1-i)){
        LCD_Cursor(1+i);
        LCD_WriteData(alpha[i]);
      }
    }
    
    notePressCorrect = (getNoteKey(gameSong[curNote]) == keyPressed);
    state = playing;
    counter++;
    if(counter >= move){
      if(notePressCorrect && gameSong[curNote]){
        lives++;
      }else if(!notePressCorrect){
        lives--;
      }
      curNote++;
      buildSongDisplay(curNote);
      keyPressed = 0;
      notePressCorrect = 0;
      counter = 0;
    }
    break;
  case end:
    reset = GetBit(~PINA, 0);
    if(lives != 0)
      copyString(buffer, "WINNER!!!",10);
    else
      copyString(buffer, "You loss", 9);
    if(reset){
      state = init;
      startGame = 0;
      break;
    } 
    endGame = 1;
    break;
  }

  return state;
}
