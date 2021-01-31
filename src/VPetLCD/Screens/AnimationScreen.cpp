#include "AnimationScreen.h"


V20::AnimationScreen::AnimationScreen(AbstractSpriteManager* _spriteManager, uint16_t _digimonSpriteIndex, uint8_t _numberOfFrames) {
    spriteManager = _spriteManager;
    numberOfFramesMax = _numberOfFrames;
    digimonSpriteIndex = _digimonSpriteIndex;

    //initialization
    numberOfFrames = 0;//how many frames are there at the moment
    currentFrame = 0;//index of current frame
    frameDurationMillis = 1000;//how long should 1 frame showed
    timer = 0;//the timer for the framedurations
    frames = new std::function<void(VPetLCD* lcd, AnimationScreen* context)>[numberOfFramesMax];
    animationEndAction = NULL;
}

/**
 * Adds a frame to the animation if maximum number of frames is not reached.
 *
 * @param frame lambda function specifing the content of the frame
 * @return true if frame is added, false if not
 */
boolean V20::AnimationScreen::addFrame(std::function<void(VPetLCD* lcd, AnimationScreen* context)> frame) {
    if (numberOfFrames < numberOfFramesMax) {
        frames[numberOfFrames] = frame;
        numberOfFrames++;
    } else {
        return false;
    }
}

/**
 * Draws the current frame of the animation if currentframe is not -1
 *  
 * */
void V20::AnimationScreen::draw(VPetLCD* lcd) {
    //just calling the function of the current frame
    if(currentFrame != -1)
    frames[currentFrame](lcd, this);
}

/**
 * This method should be called if the screen should switch to the next frame.
 * When you call this Method while the last frame, the animationEndAction function will be called
 * */
void V20::AnimationScreen::nextFrame() {
    if(currentFrame != -1){
        currentFrame++;
        currentFrame %= numberOfFrames;
        if (currentFrame == 0) {
            currentFrame = -1;
            
            if(animationEndAction != NULL)
            animationEndAction();
             
        }
    }
}

/**
 * This method calls the nextFrame() method when the updateIntervallTime is reached
 * When you call this Method while the last frame, the animationEndAction function will be called
 * */
void V20::AnimationScreen::loop(unsigned long delta){
    if(isNextFrameTime(delta)){
        nextFrame();
    }
}

void V20::AnimationScreen::setAnimationEndAction(std::function<void(void)> _animationEndAction) {
    animationEndAction = _animationEndAction;
}

