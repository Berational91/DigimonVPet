#include "ScreenStateMachine.h"

/**
 * Constructor initilizing the inner structure of the Class. The starting screen is the first screen added.
 *
 * @param _numberOfScreens value between 0-255 determining how many screens there are
 * @param _numberOfSignals value between 0-255 determining how many signals, which can trigger transistions, there are
 *
 * */
ScreenStateMachine::ScreenStateMachine(uint8_t _numberOfScreens, uint8_t _numberOfSignals) {
    currentScreenId=1;
    screenCounter = 0;
    numberOfScreens = _numberOfScreens;
    numberOfSignals = _numberOfSignals;
    //creating array of screen-pointers
    screens = new VPetLCD::Screen* [numberOfScreens];

    //Array of array of uint8_t. First dimension is numberOfScreens
    //and second one are the number of signals
    //for each screen there will be an array of numberOfSignals transitions
    // for example transition[screenIndex1][signalid] will determine
    // the destination Screen of the transistion starting from screenIndex triggered by signalid 
    transitions = new uint8_t * [numberOfScreens];
    for (int i = 0; i < numberOfScreens; i++) {
        transitions[i] = new uint8_t[numberOfSignals];
    }


    //creating an array of transitionActions for every transition
    transitionActions = new std::function<void(void)>*[numberOfScreens];
    for (int i = 0; i < numberOfScreens; i++) {
        transitionActions[i] = new std::function<void(void)>[numberOfSignals];
    }

//initializing transitions to "no transition" and transitionActions to NULL
    for(int i=0; i<numberOfScreens;i++){

        for(int j=0; j < numberOfSignals;j++){
            transitions[i][j] = 0;
            transitionActions[i][j] = NULL;
        }
    }

}

/**
 *
 * Adds the screen to the ScreenStateMachine ans assigns it an id for the {@link #addTransition(uint8_t,uint8_t,uint8_t)} method.
 *
 * @param screen pointer to the Screen which should be added
 * @return id of the added screen
 */
uint8_t ScreenStateMachine::addScreen(VPetLCD::Screen* screen) {

    //the id of the screen is the screens index in the array plus 1 (id 0 is reserved for "no transition")
    screens[screenCounter] = screen;
    screenCounter++;
    return screenCounter;
}


/**
 * Adds an transition-rule for the calculation of the {@link #sendSignal(uint8_t)} method.
 * A transition is the change of the internal state to another state.
 * E.g. the rule are like "change from screen screenId1 to screen screenId2 if signal signalId is sent"
 * If a transition is triggered the specified transitionAction will also be performed
 *
 * @param screenId1 id of the start of the transition
 * @param screenId2 id of the destination of the transition
 * @param signalId id of the signal, which should be added
 *
 * @return true if transition is added, false if parameter are bad
 */
boolean ScreenStateMachine::addTransition(uint8_t screenId1, uint8_t screenId2, uint8_t signalId) {
    if (screenId1 <= screenCounter && screenId2 <= screenCounter && screenId1 > 0 && screenId2 > 0 && signalId < numberOfSignals) {
        transitions[getIndex(screenId1)][signalId] = screenId2;
    }
}


/**
 * The given lambdaFunction transitionAction will be performed, when a transition from screen screenId1 is triggered by signal signalId
 * 
 * @returns true if transistion is added, false if not
 * */
boolean ScreenStateMachine::addTransitionAction(uint8_t screenId1, uint8_t signalId, std::function<void(void)> transitionAction) {
    if (signalId < numberOfSignals) {
        transitionActions[getIndex(screenId1)][signalId] = transitionAction;
        
        return true;
    }else{
        return false;
    }

}

void ScreenStateMachine::printTransitions(){
    for(int i=0; i<numberOfScreens;i++){
        Serial.println("-------------------------");
        for(int j=0; j < numberOfSignals;j++){
            Serial.print("Current Screen: ");
            Serial.println(i+1);
            Serial.print("Current Signal: ");
            Serial.println(j);
            Serial.print("Destination: ");
            Serial.println( transitions[i][j]);

        }
    }
}


/**
 * Triggers a transition from the current state to another state defined by the added transitions. 
 * If for the current screen and given signal is an transitionAction is defined, it will be performed.
 * 
 * @param signalId the id of the triggering signal
 *
 * @return true if any transition was performed, false if signalId was bad or no transition from the current screen triggered by given signal was defined
 *
 * */
boolean ScreenStateMachine::sendSignal(uint8_t signalId) {

    if (signalId >= numberOfSignals) {
        return false;
    }

    uint8_t nextScreenId = transitions[getIndex(currentScreenId)][signalId];
    uint8_t oldCurrentScreenId = currentScreenId;
    if (nextScreenId > 0) {


        currentScreenId = nextScreenId;

        //call transitionAction function if defined
        if( transitionActions[getIndex(oldCurrentScreenId)][signalId] != NULL){
            transitionActions[getIndex(oldCurrentScreenId)][signalId]();
        }
    }    
else {
        return false;
    }
}


/**
 * Returns the current screen
 */
VPetLCD::Screen* ScreenStateMachine::getCurrentScreen() {
    return screens[getIndex(currentScreenId)];
}

/**
 * Sets the current screen to given Screen, without triggering a transition or transitionAction
 * @param screenId the screen to be set
 */
void ScreenStateMachine::setCurrentScreen(uint8_t screenId){currentScreenId = screenId;}