/*	Author: thuanvu
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab5  Exercise 1
 *	Exercise Description: [optional - include for your own benefit] I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    DDRA = 0x00;
    DDRC = 0xFF;
    unsigned char output = 0;
    while (1) {
      unsigned char uc_fuel_lvl = ~PINA & 0x0F;
      if(uc_fuel_lvl == 0){ // P0 -> P5 no ligts, P6 lights
        output = 0x40;
      }else if(uc_fuel_lvl <= 2){ // P5 lights, p6 lights
        output = 0x60; 
      }else if(uc_fuel_lvl <= 4){ // p5,p4 lights, p6 lights 0x0111 0000
        output = 0x70; 
      }else if(uc_fuel_lvl <= 6){ // p5,p4,p3 lights, p6 no lights 0x00111000
        output = 0x38; 
      }else if(uc_fuel_lvl <= 9){ // p5,p4,p3,p2 lights p6 no lights 0x0011 1100
        output = 0x3C;
      }else if(uc_fuel_lvl <= 12){ // p5,p4,p3,p2,p1 lights p6 no lights 0x0011 1110
        output = 0x3E; 
      }else if(uc_fuel_lvl <= 15){
        output = 0x3F;
      }
      PORTC = output;
    }
    return 1;
}
