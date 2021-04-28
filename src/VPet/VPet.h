#pragma once
#include "VPetLCD/VPetLCD.h"
#include "VPetLCD/VPetLCDMenuBar32p.h"
#include "VPetLCD/Screens/AgeWeightScreen.h"
#include "VPetLCD/Screens/DigimonNameScreen.h"
#include "VPetLCD/Screens/HeartsScreen.h"
#include "VPetLCD/Screens/ProgressBarScreen.h"
#include "VPetLCD/Screens/PercentageScreen.h"
#include "VPetLCD/Screens/SelectionScreen.h"
#include "VPetLCD/Screens/ClockScreen.h"
#include "VPetLCD/Screens/DigimonWatchingScreen.h"
#include "VPetLCD/Screens/AnimationScreens/EatingAnimationScreen.h"
#include "GameLogic/AbstractDigimonDataLoader.h"
#include "SaveGame/SaveGameHandler.h"


#include "GameLogic/ScreenStateMachine.h"
#include "GameLogic/Digimon.h"


#define CONFIRM_SIGNAL 0
#define NEXT_SIGNAL 1
#define BACK_SIGNAL 2

class VPet {

private:

    Digimon* digimon;
    AbstractSpriteManager* spriteManager;
    AbstractDigimonDataLoader* dataLoader;
    AbstractDisplayAdapter* displayAdapter;
    SaveGameHandler* saveGame;

    VPetLCD* screen;
    VPetLCDMenuBar32p* menuBar;

    //screens
    V20::DigimonWatchingScreen* digimonScreen;
    V20::DigimonNameScreen* digiNameScreen;
    V20::AgeWeightScreen* ageWeightScreen;
    V20::HeartsScreen* hungryScreen;
    V20::HeartsScreen* strengthScreen;
    V20::HeartsScreen* effortScreen;
    V20::ProgressBarScreen* dpScreen;
    V20::PercentageScreen* sPercentageScreen;
    V20::PercentageScreen* tPercentageScreen;
    V20::SelectionScreen* foodSelection;
    V20::SelectionScreen* fightSelection;
    int hours = 23;
    int minutes = 59;
    int seconds = 0;
    V20::ClockScreen* clockScreen;
    V20::EatingAnimationScreen* eatingAnimationScreen;

    const uint8_t numberOfScreens = 13;
    const uint8_t numberOfSignals = 3;



// the ScreenStateMachinehandles transitions between screens
//and the actions of the buttons; the buttons are just sending signals to the statemachine
    ScreenStateMachine* stateMachine;

    uint8_t digimonScreenId;
    uint8_t digiNameScreenId;
    uint8_t ageWeightScreenId;
    uint8_t hungryScreenId;
    uint8_t strengthScreenId; 
    uint8_t effortScreenId; 
    uint8_t dpScreenId;
    uint8_t sPercentageScreenId;
    uint8_t tPercentageScreenId;
    uint8_t foodSelectionId;
    uint8_t fightSelectionId;
    uint8_t clockScreenId;
    uint8_t eatingAnimationScreenId ;

    void stateMachineInit();

    void setupScreens();

public:
    VPet(AbstractDisplayAdapter* _displayAdapter,  AbstractSpriteManager* _spriteManager,  AbstractDigimonDataLoader* _dataLoader, SaveGameHandler* _saveGameHandler);
    void setup();
    void loop(unsigned long delta);
    void sendSignal(uint8_t signalid){stateMachine->sendSignal(signalid);};
    void hideMenuBar(){screen->setMenuBar(NULL); screen->setLCDPosY(0);}

    void showMenuBar(){screen->setMenuBar(menuBar);screen->setLCDPosY(32);}
    void setLcdScreenDims(uint8_t resolutionX,uint8_t resolutionY ){screen->setLcdDimensions(resolutionX,resolutionY);};
    void setLcdScale(uint8_t scale){screen->setLcdScale(scale);};

    



};