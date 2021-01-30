#include "../AnimationScreen.h"


namespace V20 {
    class EatingAnimationScreen : public AnimationScreen {

        private:

            //the indices for the Symbolsprites
            uint8_t foodFullSpriteIndex;
            uint8_t foodHalfSpriteIndex;
            uint8_t foodEmptySpriteIndex;

        public:
            EatingAnimationScreen(AbstractSpriteManager *_spriteManager, uint16_t _digimonSpriteIndex);
            //sets the sprites for the animation
            void setSprites(uint8_t _foodFullSpriteIndex, uint8_t _foodHalfSpriteIndex,uint8_t _foodEmptySpriteIndex);
            uint8_t getFullSpriteIndex(){return foodFullSpriteIndex;};
            uint8_t getHalfSpriteIndex(){return foodHalfSpriteIndex;};
            uint8_t getEmptySpriteIndex(){return foodEmptySpriteIndex;};
    }; 


 }