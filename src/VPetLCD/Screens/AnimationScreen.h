/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////
#pragma once
#include "../VPetLCD.h"
#include <functional>

namespace V20 {


  class AnimationScreen : public VPetLCD::Screen {

  private:
    AbstractSpriteManager* spriteManager;


    std::function<void(VPetLCD* lcd, AnimationScreen* context)> *frames;

    //this function is called when the animation ends (last frame showed)
    std::function<void(void)> animationEndAction;

    uint16_t digimonSpriteIndex;
    uint8_t numberOfFramesMax;
    uint8_t numberOfFrames;
    uint8_t currentFrame;

    uint32_t frameDurationMillis;
    uint32_t timer;
    void nextFrame();

  public:
    void loop(unsigned long delta);
    AnimationScreen(AbstractSpriteManager *_spriteManager, uint16_t _digimonSpriteIndex, uint8_t _numberOfFrames);
    boolean addFrame(std::function<void(VPetLCD* lcd, AnimationScreen* context)> frame);
    void draw(VPetLCD *lcd);
 
    void setAnimationEndAction(std::function<void(void)> _animationEndAction);
    AbstractSpriteManager* getSpriteManager(){return spriteManager;};
    uint16_t getDigimonSpriteIndex(){ return digimonSpriteIndex;};

    //starts the Animation
    void startAnimation(){currentFrame=0;};
    void abortAnimation(){currentFrame=-1;}
  };


}