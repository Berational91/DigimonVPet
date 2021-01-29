#pragma once

#include "Arduino.h"
#include "../VPetLCD/VPetLCD.h"
#include <functional>

/**
 * A Class for controlling the screens and transitions between them. One can specify how many
 * screens there are and how many signals, which can trigger transitions between screens.
 *  
 * 
 * 
 * */
class ScreenStateMachine{

private:


    //Array of screens
    VPetLCD::Screen** screens;


    //Array of array of uint8_t. First dimension is numberOfScreens
    //and second one are the number of signals
    //for each screen there will be an array of numberOfSignals transitions
    // for example transition[screenIndex1][signalid] will determine
    // the destination Screen of the transistion starting from screenIndex triggered by signalid 
    uint8_t** transitions;

    std::function<void(void)> **transitionActions;

    uint8_t screenCounter;

    uint8_t numberOfScreens;
    uint8_t numberOfSignals;
    
    uint8_t currentScreenId;


    //Method to calculate the index of the screens in the array out of the id
    uint8_t getIndex(uint8_t screenId){ return screenId-1;};

    //Method to calculate the id of the screens in the array out of their index 
    uint8_t getId(uint8_t index){ return index+1;};


public:

    ScreenStateMachine(uint8_t _numberOfScreens, uint8_t _numberOfSignals);


    uint8_t addScreen(VPetLCD::Screen* screen);

    boolean addTransition(uint8_t screenId1, uint8_t screenId2, uint8_t signalId);
    boolean addTransitionAction(uint8_t screenId1, uint8_t signalId, std::function<void(void)> transitionAction);

    boolean sendSignal(uint8_t signalId);

    VPetLCD::Screen* getCurrentScreen();

    void setCurrentScreen(uint8_t screenId);
    
    void printTransitions();

};