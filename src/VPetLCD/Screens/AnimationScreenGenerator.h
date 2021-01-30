#include "AnimationScreen.h"


namespace V20 {

    //this class generates some animationscreens, with preconfigured animations
    class AnimationScreenGenerator {

    public:
        static AnimationScreen* getEatMeatScreen(AbstractSpriteManager *spriteManager, uint8_t digimonSpriteIndex);
        static AnimationScreen* getEatPillScreen(AbstractSpriteManager *spriteManager, uint8_t digimonSpriteIndex);
        static AnimationScreen* getEatPoopScreen(AbstractSpriteManager *spriteManager, uint8_t digimonSpriteIndex);
        static AnimationScreen* getEatLoveScreen(AbstractSpriteManager *spriteManager, uint8_t digimonSpriteIndex);

    };

}