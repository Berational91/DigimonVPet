#pragma once
#include "VPet.h"


VPet::VPet(AbstractDisplayAdapter* _displayAdapter, AbstractSpriteManager* _spriteManager, AbstractDigimonDataLoader* _dataLoader, SaveGameHandler* _saveGameHandler) {
    digimon = new Digimon(0);
    dataLoader = _dataLoader;
    const DigimonProperties* properties = dataLoader->getDigimonProperties(0);
    digimon->setProperties(properties);
    digimon->getProperties()->digiName;

    displayAdapter = _displayAdapter;
    spriteManager = _spriteManager;
    
    saveGame= _saveGameHandler;

    uint8_t lcdWidth = 40;
    uint8_t lcdHeight = 16;
    screen = new VPetLCD(displayAdapter, spriteManager, lcdWidth, lcdHeight);
    
    //centering horizontal
    uint16_t displayWidthPix = displayAdapter->getWidthInPixel();
    menuBar = new VPetLCDMenuBar32p(7,5,displayWidthPix);

    screen->setMenuBar(menuBar);
    screen->setLcdScale(6);
    screen->setLCDPosX((displayWidthPix - lcdWidth*screen->getLcdScale()) / 2);

    stateMachine = new ScreenStateMachine(numberOfScreens, numberOfSignals);



}
void VPet::setup(){
    setupScreens();
   stateMachineInit();
}

void VPet::setupScreens() {


    digimonScreen = new V20::DigimonWatchingScreen(spriteManager, digimon->getDigimonIndex(), -4, 32, 0, 0);
    digiNameScreen = new V20::DigimonNameScreen(spriteManager, digimon->getProperties()->digiName, digimon->getDigimonIndex(), 24);
    ageWeightScreen = new V20::AgeWeightScreen(0, 1);
    hungryScreen = new V20::HeartsScreen("Hungry", 1, 4);
    strengthScreen = new V20::HeartsScreen("Strength", 1, 4);
    effortScreen = new V20::HeartsScreen("Effort", 1, 4);
    dpScreen = new V20::ProgressBarScreen("DP", 30, 1);
    sPercentageScreen = new V20::PercentageScreen("WIN", 'S', 0);
    tPercentageScreen = new V20::PercentageScreen("WIN", 'T', 93);
    foodSelection = new V20::SelectionScreen(true);
    fightSelection = new V20::SelectionScreen(true);
    clockScreen = new V20::ClockScreen(true);
    eatingAnimationScreen = new V20::EatingAnimationScreen(spriteManager, digimon->getDigimonIndex());

    menuBar->setIconOnIndex(0, 0);
    menuBar->setIconOnIndex(1, 1);
    menuBar->setIconOnIndex(2, 2);
    menuBar->setIconOnIndex(3, 3);
    menuBar->setIconOnIndex(4, 4);
    menuBar->setIconOnIndex(5, 5);
    menuBar->setIconOnIndex(6, 6);


    screen->setMenuBar(menuBar);

    //Positioning of the screens
    int screensOffsetX = 0;


    //set offset of the screens
    ageWeightScreen->setPos(screensOffsetX, 0);
    effortScreen->setPos(screensOffsetX, 0);
    strengthScreen->setPos(screensOffsetX, 0);
    hungryScreen->setPos(screensOffsetX, 0);
    dpScreen->setPos(screensOffsetX, 0);
    sPercentageScreen->setPos(screensOffsetX, 0);
    tPercentageScreen->setPos(screensOffsetX, 0);
    clockScreen->setPos(screensOffsetX, 0);
    eatingAnimationScreen->setPos(screensOffsetX, 0);



    //adding the food selection options
    foodSelection->addOption("Meat", SYMBOL_MEAT);
    foodSelection->addOption("PILL", SYMBOL_PILL);
    foodSelection->addOption("LOVE", SYMBOL_HEART);
    foodSelection->addOption("SHIT", SYMBOL_POOP);

    //adding the battle options
    fightSelection->setShowIcons(false);
    fightSelection->addOption("SINGLE");
    fightSelection->addOption("TAG");

    clockScreen->setHours(hours);
    clockScreen->setMinutes(minutes);
    clockScreen->setSeconds(seconds);
}


void VPet::stateMachineInit() {
    digimonScreenId = stateMachine->addScreen(digimonScreen);
    digiNameScreenId = stateMachine->addScreen(digiNameScreen);
    ageWeightScreenId = stateMachine->addScreen(ageWeightScreen);
    hungryScreenId = stateMachine->addScreen(hungryScreen);
    strengthScreenId = stateMachine->addScreen(strengthScreen);
    effortScreenId = stateMachine->addScreen(effortScreen);
    dpScreenId = stateMachine->addScreen(dpScreen);
    sPercentageScreenId = stateMachine->addScreen(sPercentageScreen);
    tPercentageScreenId = stateMachine->addScreen(tPercentageScreen);
    foodSelectionId = stateMachine->addScreen(foodSelection);
    fightSelectionId = stateMachine->addScreen(fightSelection);
    clockScreenId = stateMachine->addScreen(clockScreen);
    eatingAnimationScreenId = stateMachine->addScreen(eatingAnimationScreen);

    //return to food selection screen after showing eating animation
    eatingAnimationScreen->setAnimationEndAction([this]() {
        stateMachine->setCurrentScreen(foodSelectionId);

        });

    // in order to be able to go back to the digimon watching screen
    // we will add a transition from every screen to the digimon watching screen
    //triggered by the BACK_SIGNAL (backbutton)
    for (int i = 1; i <= numberOfScreens + 1;i++) {
        stateMachine->addTransition(i, digimonScreenId, BACK_SIGNAL);
    }

    //The Scale Menu transitions
    stateMachine->addTransition(digiNameScreenId, ageWeightScreenId, NEXT_SIGNAL);
    stateMachine->addTransition(ageWeightScreenId, hungryScreenId, NEXT_SIGNAL);
    stateMachine->addTransition(hungryScreenId, strengthScreenId, NEXT_SIGNAL);
    stateMachine->addTransition(strengthScreenId, effortScreenId, NEXT_SIGNAL);
    stateMachine->addTransition(effortScreenId, dpScreenId, NEXT_SIGNAL);
    stateMachine->addTransition(dpScreenId, sPercentageScreenId, NEXT_SIGNAL);
    stateMachine->addTransition(sPercentageScreenId, tPercentageScreenId, NEXT_SIGNAL);
    stateMachine->addTransition(tPercentageScreenId, digiNameScreenId, NEXT_SIGNAL);

    //Transitions between clock screen and digimon watching screen
    stateMachine->addTransition(digimonScreenId, clockScreenId, BACK_SIGNAL);
    stateMachine->addTransition(clockScreenId, digimonScreenId, BACK_SIGNAL);


    //Conditional transtitions from digimonScreen to the others (menuselection)
    //this must be set, because unset transitions wont trigger transitionActions
    stateMachine->addTransition(digimonScreenId, digimonScreenId, NEXT_SIGNAL);

    //if NEXT_SIGNAL is sent (nextbutton pressed), the menuselection will be
    //incremented and the selection will be set
    stateMachine->addTransitionAction(digimonScreenId, NEXT_SIGNAL, [this]() {
        menuBar->nextSelection();
        });

    //Here are the conditional transitions handled->
    stateMachine->addTransition(digimonScreenId, digimonScreenId, CONFIRM_SIGNAL);
    stateMachine->addTransitionAction(digimonScreenId, CONFIRM_SIGNAL, [this]() {
        uint8_t maxdp = digimon->getProperties()->maxDigimonPower;
        switch (menuBar->getSelection()) {
        case 0:
            digiNameScreen->setDigimonSpriteIndex(digimon->getDigimonIndex());
            hungryScreen->setHearts(4 - 4 * digimon->getHunger() / 10);

            if (maxdp > 0) {
                dpScreen->setFillPercentage((digimon->getDigimonPower() * 100) / maxdp);
            }
            else {
                dpScreen->setFillPercentage(0);
            }
            ageWeightScreen->setAge(digimon->getAge());
            ageWeightScreen->setWeight(digimon->getWeight());
            stateMachine->setCurrentScreen(digiNameScreenId);
            break;
        case 1:
            foodSelection->setSelection(0);
            stateMachine->setCurrentScreen(foodSelectionId);
            break;
        case 3:
            fightSelection->setSelection(0);
            stateMachine->setCurrentScreen(fightSelectionId);
            break;

        case 4:

            digimonScreen->flushPoop();
            digimon->setNumberOfPoops(0);
            break;

        case 2:

            break;
        }
        });


    //adding functionality of buttons in food screen:
    stateMachine->addTransition(foodSelectionId, foodSelectionId, NEXT_SIGNAL);
    stateMachine->addTransitionAction(foodSelectionId, NEXT_SIGNAL, [this]() {
        foodSelection->nextSelection();
        });

    //adding functionality of buttons in food screen:
    stateMachine->addTransition(foodSelectionId, foodSelectionId, CONFIRM_SIGNAL);
    stateMachine->addTransitionAction(foodSelectionId, CONFIRM_SIGNAL, [this]() {
        uint8_t selection = foodSelection->getSelection();
        switch (selection) {
        case 0:
            digimon->addWeight(1);
            digimon->reduceHunger(1);
            eatingAnimationScreen->setSprites(SYMBOL_MEAT, SYMBOL_HALF_MEAT, SYMBOL_EMPTY_MEAT);
            eatingAnimationScreen->startAnimation();
            stateMachine->setCurrentScreen(eatingAnimationScreenId);
            break;
        case 1:
            digimon->addWeight(2);
            digimon->addStrength(2);
            digimon->addDigimonPower(2);
            eatingAnimationScreen->setSprites(SYMBOL_PILL, SYMBOL_HALF_PILL, SYMBOL_EMPTY);
            eatingAnimationScreen->startAnimation();
            stateMachine->setCurrentScreen(eatingAnimationScreenId);
            break;

        case 2:
            eatingAnimationScreen->setSprites(SYMBOL_HEART, SYMBOL_HEARTEMPTY, SYMBOL_EMPTY);
            eatingAnimationScreen->startAnimation();
            stateMachine->setCurrentScreen(eatingAnimationScreenId);
            break;
        case 3:
            eatingAnimationScreen->setSprites(SYMBOL_POOP, SYMBOL_HALF_PILL, SYMBOL_EMPTY);
            eatingAnimationScreen->startAnimation();
            stateMachine->setCurrentScreen(eatingAnimationScreenId);
            break;

        }
        });

    //go back to food selection if pressed CONFIRM_SIGNAL again
    stateMachine->addTransition(eatingAnimationScreenId, foodSelectionId, CONFIRM_SIGNAL);
    //abort animation
    stateMachine->addTransitionAction(eatingAnimationScreenId, CONFIRM_SIGNAL, [this]() {
        eatingAnimationScreen->abortAnimation();
        });

    //adding functionality of buttons in fight screen:
    stateMachine->addTransition(fightSelectionId, fightSelectionId, NEXT_SIGNAL);
    stateMachine->addTransitionAction(fightSelectionId, NEXT_SIGNAL, [this]() {
        fightSelection->nextSelection();

        });


}


void VPet::loop(unsigned long delta) {

    digimon->loop(delta);
    digimonScreen->setNumberOfPoop(digimon->getNumberOfPoops());


    //updating the screens which need the loop
    digimonScreen->loop(delta);
    clockScreen->loop(delta);
    digiNameScreen->loop(delta);
    if (stateMachine->getCurrentScreen() == eatingAnimationScreen)
        eatingAnimationScreen->loop(delta);
    

    screen->renderScreen(stateMachine->getCurrentScreen());
    
}
