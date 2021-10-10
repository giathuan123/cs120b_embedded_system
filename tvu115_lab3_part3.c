/*	Author: thuanvu
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 3 Exercise 2
 *	Exercise Description: Count the number of 1s on ports A and B and output that number on portC 
 *
 *	I acknowledge all content contained herein, excluding template or example
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
int main(void) {
    /* Insert your solution below */
    DDRA = 0x00;
    DDRC = 0xFF;
    while (1) {
      unsigned char uc_fuel_lvl = PINA & 0x0F;
      if(uc_fuel_lvl == 0){ // P0 -> P5 no ligts, P6 lights
        PORTC = 0x40;
      }else if(uc_fuel_lvl <= 2){ // P5 lights, p6 lights
        PORTC = 0x60; 
      }else if(uc_fuel_lvl <= 4){ // p5,p4 lights, p6 lights 0x0111 0000
        PORTC = 0x70; 
      }else if(uc_fuel_lvl <= 6){ // p5,p4,p3 lights, p6 no lights 0x00111000
        PORTC = 0x38; 
      }else if(uc_fuel_lvl <= 9){ // p5,p4,p3,p2 lights p6 no lights 0x0011 1100
        PORTC = 0x3C;
      }else if(uc_fuel_lvl <= 12){ // p5,p4,p3,p2,p1 lights p6 no lights 0x0011 1110
        PORTC = 0x3E; 
      }else if(uc_fuel_lvl <= 15){
        PORTC = 0x3F;
      }
      unsigned char fasten_seatbelt = GetBit(PINA, 4) && GetBit(PINA, 5) && (GetBit(PINA, 6) != 0x01);
      PORTC = SetBit(PORTC, 7, fasten_seatbelt);
    }
    return 1;
}
