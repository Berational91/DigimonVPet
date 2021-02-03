#include "EatingAnimationScreen.h"



namespace V20 {

    EatingAnimationScreen::EatingAnimationScreen(AbstractSpriteManager *_spriteManager, uint16_t _digimonSpriteIndex) : AnimationScreen(_spriteManager, _digimonSpriteIndex,5){
        setSprites(SYMBOL_MEAT, SYMBOL_HALF_MEAT,SYMBOL_EMPTY_MEAT);
        
        addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        EatingAnimationScreen *eContext = (EatingAnimationScreen*) (context);
        uint8_t foodFullSpriteIndex = eContext->getFullSpriteIndex() ;

        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_EATING1);
        const byte* foodSprite = sm->getSymbol(foodFullSpriteIndex);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();



        uint8_t foodWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t foodHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - foodWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(foodSprite, foodWidth, foodHeight, screenX + 32 - foodWidth, screenY, false, pixelColor);
        });

       addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        EatingAnimationScreen *eContext = (EatingAnimationScreen*) (context);
        uint8_t foodFullSpriteIndex = eContext->getFullSpriteIndex() ;

        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_EATING2);
        const byte* foodSprite = sm->getSymbol(foodFullSpriteIndex);

        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t foodWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t foodHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - foodWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(foodSprite, foodWidth, foodHeight, screenX + 32 - foodWidth, screenY + foodHeight, false, pixelColor);
        });

     addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_EATING1);
        EatingAnimationScreen *eContext = (EatingAnimationScreen*)(context);
        uint8_t foodHalfSpriteIndex = eContext->getHalfSpriteIndex() ;

        const byte* foodSprite = sm->getSymbol(foodHalfSpriteIndex);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t foodWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t foodHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - foodWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(foodSprite, foodWidth, foodHeight, screenX + 32 - foodWidth, screenY + foodHeight, false, pixelColor);
        });

    addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_EATING2);
        EatingAnimationScreen *eContext = (EatingAnimationScreen*) (context);
        uint8_t foodHalfSpriteIndex = eContext->getHalfSpriteIndex() ;

        const byte* foodSprite = sm->getSymbol(foodHalfSpriteIndex);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t foodWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t foodHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - foodWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(foodSprite, foodWidth, foodHeight, screenX + 32 - foodWidth, screenY + foodHeight, false, pixelColor);
        });

    addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_EATING1);
        EatingAnimationScreen *eContext = (EatingAnimationScreen*)(context);
        uint8_t foodEmptySpriteIndex = eContext->getEmptySpriteIndex() ;

        const byte* foodSprite = sm->getSymbol(foodEmptySpriteIndex);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t foodWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t foodHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - foodWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(foodSprite, foodWidth, foodHeight, screenX + 32 - foodWidth, screenY + foodHeight, false, pixelColor);
        });
    };
            

    //Sets the Food sprites; Set 0 for "no Sprite"
    void EatingAnimationScreen::setSprites(uint8_t _foodFullSpriteIndex, uint8_t _foodHalfSpriteIndex,uint8_t _foodEmptySpriteIndex){
        foodFullSpriteIndex = _foodFullSpriteIndex;
        foodHalfSpriteIndex = _foodHalfSpriteIndex;
        foodEmptySpriteIndex = _foodEmptySpriteIndex;
    }

    
    
 }