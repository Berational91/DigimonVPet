// These are the 8x8 Monochrome Symbols stored in 8 8bit unsigned integer to decrease memory Usage.
// Each image needs 8 Byte
#pragma once
#include <Arduino.h>
#if defined(__AVR__)
#include <avr/pgmspace.h>
#elif defined(__PIC32MX__)
#define PROGMEM
#elif defined(__arm__)
#define PROGMEM
#endif



#define SPRITES_SYMBOL_RESOLUTION 8



#define N_SPRITES_SYMBOL 20
#define N_SPRITES_DIGIMON 12



// SYMBOLS WITHIN MENUES
#define SYMBOL_EMPTY 0
#define SYMBOL_PET 1
#define SYMBOL_SCALE 2
#define SYMBOL_HEARTEMPTY 3
#define SYMBOL_HEART 4
#define SYMBOL_AGE 5
#define SYMBOL_WEIGHT 6
#define SYMBOL_PERCENT 7
#define SYMBOL_ARROW 8
#define SYMBOL_MEAT 9
#define SYMBOL_HALF_MEAT 10
#define SYMBOL_EMPTY_MEAT 11
#define SYMBOL_PILL 12
#define SYMBOL_HALF_PILL 13
#define SYMBOL_AM 14
#define SYMBOL_PM 15
#define SYMBOL_EMPTY_TRIANGLE 16
#define SYMBOL_TRIANGLE 17
#define SYMBOL_POOP 18
#define SYMBOL_POOPWAVE 19




const byte SYMBOLS[N_SPRITES_SYMBOL][SPRITES_SYMBOL_RESOLUTION] PROGMEM = {
  {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
    0b00000000,
  },

  {
    0b00100100,
    0b01111110,
    0b01011010,
    0b01111110,
    0b01100110,
    0b11111111,
    0b00000000,
    0b00000000,
  },

  {
    0b10000010,
    0b11111110,
    0b00010000,
    0b01111100,
    0b01000100,
    0b01000100,
    0b01010100,
    0b11111110,
  },

  {
    0b00000000,
    0b01101100,
    0b10010010,
    0b10000010,
    0b10000010,
    0b01000100,
    0b00101000,
    0b00010000,
  },

  {
    0b00000000,
    0b01101100,
    0b10111110,
    0b10111110,
    0b11111110,
    0b01111100,
    0b00111000,
    0b00010000,
  },

  {
    0b00000000,
    0b00100000,
    0b01010000,
    0b10001000,
    0b11111000,
    0b10001000,
    0b10001000,
    0b00000000,
  },

  {
    0b00111000,
    0b01001000,
    0b00111000,
    0b00001100,
    0b01111000,
    0b10001000,
    0b01110000,
    0b00000000,
  },

  {
    0b00000000,
    0b00100001,
    0b01010010,
    0b01010100,
    0b00101010,
    0b00010101,
    0b00100101,
    0b01000010,
  },

  {
    0b00000000,
    0b00100000,
    0b00110000,
    0b11111000,
    0b11111100,
    0b11111000,
    0b00110000,
    0b00100000,
  },

  {
    0b00000011,
    0b00011101,
    0b00101010,
    0b01011110,
    0b01111110,
    0b01111100,
    0b10111000,
    0b11000000,
  },

  {
    0b00000011,
    0b00001101,
    0b00011110,
    0b00010110,
    0b00101100,
    0b01010000,
    0b10100000,
    0b11000000,
  },

  {
    0b00000011,
    0b00000101,
    0b00001010,
    0b00010100,
    0b00101000,
    0b01010000,
    0b10100000,
    0b11000000,
  },

  {
    0b00001110,
    0b00010011,
    0b00101111,
    0b01011111,
    0b10001110,
    0b10000100,
    0b10001000,
    0b01110000,
  },

  {
    0b00000000,
    0b00000000,
    0b00000000,
    0b01100000,
    0b11010000,
    0b10101000,
    0b10011000,
    0b01110000,
  },

  {
    0b01111000,
    0b11000100,
    0b11111100,
    0b11000100,
    0b00000000,
    0b11101100,
    0b11010100,
    0b11010100,
  },

 {
    0b01111000,
    0b11000100,
    0b11111000,
    0b11000000,
    0b00000000,
    0b11101100,
    0b11010100,
    0b11010100,
  },

  {
    0b10000000,
    0b01000000,
    0b00100000,
    0b01000000,
    0b10000000,
    0b00000000,
    0b00000000,
    0b00000000,
  },

   {
    0b10000000,
    0b11000000,
    0b11100000,
    0b11000000,
    0b10000000,
    0b00000000,
    0b00000000,
    0b00000000,
  },

   {
    0b10000000,
    0b01000010,
    0b10000001,
    0b00010010,
    0b00011000,
    0b00110100,
    0b01011110,
    0b01111110,
  },


   {
    0b00000000,
    0b00000000,
    0b10001000,
    0b01010101,
    0b10101010,
    0b11011101,
    0b01110111,
    0b00100010,
  },
  
 

  

};


