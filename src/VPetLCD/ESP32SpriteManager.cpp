#include "ESP32SpriteManager.h"

const unsigned short* ESP32SpriteManager::getDigimonSprite(uint16_t digimonIndex, uint16_t spriteIndex){
    return DIGIMON[digimonIndex][spriteIndex];
}

const byte* ESP32SpriteManager::getSmallDigitsSprite(uint8_t index){
    return SMALLDIGITS[index];
}


const byte* ESP32SpriteManager::getDigitSprite(uint8_t digit){
    return DIGITS[digit];
}

const byte* ESP32SpriteManager::getSmallCapitalLetter(char c){

  //make character uppercase if its not
  if (c > 'Z') {
    c -= 32;
  }
  //position of the image data in the array in the flash memory (65 is the ASCII value of A, which is in position 0 in capitalAlphabet)
  int arrayPos = c - 65;

    return CAPITAL_ALPHABET_SMALL[arrayPos];
}


const uint8_t ESP32SpriteManager::getSmallCapitalLetterWidth(char c){
    if (c > 'Z') {
    c -= 32;
  }
  int arrayPos = c - 65;
  return CAPITAL_LETTER_WIDTH[arrayPos];
}
const byte* ESP32SpriteManager::getSymbol(uint16_t symbolIndex){
    return SYMBOLS[symbolIndex];
}

const uint32_t* ESP32SpriteManager::getHighResMenuItem(uint16_t menuItemIndex){
    return MENU_ITEMS[menuItemIndex];
}