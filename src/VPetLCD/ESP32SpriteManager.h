#include "AbstractSpriteManager.h"


//this is the realization of the Abstract Sprite Manager for ESP32 Devices
class ESP32SpriteManager : public AbstractSpriteManager {

public:
  
      ESP32SpriteManager() {};
    const unsigned short* getDigimonSprite(uint16_t digimonIndex, uint16_t spriteIndex);
    const byte* getSmallDigitsSprite(uint8_t index);
    const byte* getDigitSprite(uint8_t digit);
    const byte* getSmallCapitalLetter(char c);
    const uint8_t getSmallCapitalLetterWidth(char c);
    const byte* getSymbol(uint16_t symbolIndex);
    const uint32_t* getHighResMenuItem(uint16_t menuItemIndex);


};