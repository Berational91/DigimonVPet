#include "AnimationScreenGenerator.h"

//Generates a screen, where the digimon is eating meat
V20::AnimationScreen* V20::AnimationScreenGenerator::getEatMeatScreen(AbstractSpriteManager* spriteManager, uint8_t digimonSpriteIndex) {
    V20::AnimationScreen* eatScreen;
    eatScreen = new AnimationScreen(spriteManager, digimonSpriteIndex, 5);

    eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_WALK_0);
        const byte* meatSprite = sm->getSymbol(SYMBOL_MEAT);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t meatWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t meatHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - meatWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(meatSprite, meatWidth, meatHeight, screenX + 32 - meatWidth, screenY, false, pixelColor);
        });

    eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_EATING);
        const byte* meatSprite = sm->getSymbol(SYMBOL_MEAT);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t meatWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t meatHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - meatWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(meatSprite, meatWidth, meatHeight, screenX + 32 - meatWidth, screenY + meatHeight, false, pixelColor);
        });

    eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_WALK_0);
        const byte* meatSprite = sm->getSymbol(SYMBOL_HALF_MEAT);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t meatWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t meatHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - meatWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(meatSprite, meatWidth, meatHeight, screenX + 32 - meatWidth, screenY + meatHeight, false, pixelColor);
        });

    eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_EATING);
        const byte* meatSprite = sm->getSymbol(SYMBOL_HALF_MEAT);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t meatWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t meatHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - meatWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(meatSprite, meatWidth, meatHeight, screenX + 32 - meatWidth, screenY + meatHeight, false, pixelColor);
        });

    eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_WALK_0);
        const byte* meatSprite = sm->getSymbol(SYMBOL_EMPTY_MEAT);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t meatWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t meatHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - meatWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(meatSprite, meatWidth, meatHeight, screenX + 32 - meatWidth, screenY + meatHeight, false, pixelColor);
        });






    return eatScreen;

}


//Generates a screen, where the digimon is eating a pill
V20::AnimationScreen* V20::AnimationScreenGenerator::getEatPillScreen(AbstractSpriteManager* spriteManager, uint8_t digimonSpriteIndex) {
    V20::AnimationScreen* eatScreen;
    eatScreen = new AnimationScreen(spriteManager, digimonSpriteIndex, 5);

    eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_WALK_0);
        const byte* pillSprite = sm->getSymbol(SYMBOL_PILL);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t pillWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t pillHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - pillWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(pillSprite, pillWidth, pillHeight, screenX + 32 - pillWidth, screenY, false, pixelColor);
        });

        eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_EATING);
        const byte* pillSprite = sm->getSymbol(SYMBOL_PILL);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t pillWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t pillHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - pillWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(pillSprite, pillWidth, pillHeight, screenX + 32 - pillWidth, screenY+pillHeight, false, pixelColor);
        });

        eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_WALK_0);
        const byte* pillSprite = sm->getSymbol(SYMBOL_HALF_PILL);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t pillWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t pillHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - pillWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(pillSprite, pillWidth, pillHeight, screenX + 32 - pillWidth, screenY+pillHeight, false, pixelColor);
        });

        eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_EATING);
        const byte* pillSprite = sm->getSymbol(SYMBOL_HALF_PILL);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t pillWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t pillHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - pillWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(pillSprite, pillWidth, pillHeight, screenX + 32 - pillWidth, screenY+pillHeight, false, pixelColor);
        });

        eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_WALK_0);

        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();
        uint8_t pillWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - pillWidth - digiWidth, screenY, true, pixelColor);
        });

    


    return eatScreen;

}


//Generates a screen, where the digimon is eating poop 
V20::AnimationScreen* V20::AnimationScreenGenerator::getEatPoopScreen(AbstractSpriteManager* spriteManager, uint8_t digimonSpriteIndex) {
    V20::AnimationScreen* eatScreen;
    eatScreen = new AnimationScreen(spriteManager, digimonSpriteIndex, 5);

    eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_WALK_0);
        const byte* poopSprite = sm->getSymbol(SYMBOL_POOP);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t poopWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t poopHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - poopWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(poopSprite, poopWidth, poopHeight, screenX + 32 - poopWidth, screenY, false, pixelColor);
        });

        eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_ATTACK_1);
        const byte* poopSprite = sm->getSymbol(SYMBOL_POOP);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t poopWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t poopHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - poopWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(poopSprite, poopWidth, poopHeight, screenX + 32 - poopWidth, screenY+poopHeight, true, pixelColor);
        });

        eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_WALK_0);
        const byte* poopSprite = sm->getSymbol(SYMBOL_HALF_PILL);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t poopWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t poopHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - poopWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(poopSprite, poopWidth, poopHeight, screenX + 32 - poopWidth, screenY+poopHeight, false, pixelColor);
        });

        eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_ATTACK_1);
        const byte* poopSprite = sm->getSymbol(SYMBOL_HALF_PILL);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t poopWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t poopHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - poopWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(poopSprite, poopWidth, poopHeight, screenX + 32 - poopWidth, screenY+poopHeight, false, pixelColor);
        });

        eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_WALK_0);

        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();
        uint8_t poopWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - poopWidth - digiWidth, screenY, true, pixelColor);
        });

    


    return eatScreen;

}


//Generates a screen, where the digimon is eating love
V20::AnimationScreen* V20::AnimationScreenGenerator::getEatLoveScreen(AbstractSpriteManager* spriteManager, uint8_t digimonSpriteIndex) {
    V20::AnimationScreen* eatScreen;
    eatScreen = new AnimationScreen(spriteManager, digimonSpriteIndex, 5);

    eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_WALK_0);
        const byte* heartSprite = sm->getSymbol(SYMBOL_HEART);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t heartWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t heartHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - heartWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(heartSprite, heartWidth, heartHeight, screenX + 32 - heartWidth, screenY, false, pixelColor);
        });

        eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_EATING);
        const byte* heartSprite = sm->getSymbol(SYMBOL_HEART);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t heartWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t heartHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - heartWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(heartSprite, heartWidth, heartHeight, screenX + 32 - heartWidth, screenY+heartHeight, false, pixelColor);
        });

        eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_WALK_0);
        const byte* heartSprite = sm->getSymbol(SYMBOL_HEARTEMPTY);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t heartWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t heartHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - heartWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(heartSprite, heartWidth, heartHeight, screenX + 32 - heartWidth, screenY+heartHeight, false, pixelColor);
        });

        eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_EATING);
        const byte* heartSprite = sm->getSymbol(SYMBOL_HEARTEMPTY);
        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();

        uint8_t heartWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t heartHeight = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - heartWidth - digiWidth, screenY, true, pixelColor);
        lcd->drawByteArray(heartSprite, heartWidth, heartHeight, screenX + 32 - heartWidth, screenY+heartHeight, false, pixelColor);
        });

        eatScreen->addFrame([](VPetLCD* lcd, AnimationScreen* context) {
        AbstractSpriteManager* sm = context->getSpriteManager();
        uint16_t pixelColor = context->getPixelColor();
        uint16_t digiIndex = context->getDigimonSpriteIndex();
        const unsigned short* digiSprite = sm->getDigimonSprite(digiIndex, SPRITE_DIGIMON_WALK_0);

        uint16_t screenX = context->getPosX();
        uint16_t screenY = context->getPosY();
        uint8_t heartWidth = SPRITES_SYMBOL_RESOLUTION;
        uint8_t digiWidth = SPRITES_DIGIMON_RESOLUTION;

        lcd->draw16BitArray(digiSprite, screenX + 32 - heartWidth - digiWidth, screenY, true, pixelColor);
        });

    


    return eatScreen;

}