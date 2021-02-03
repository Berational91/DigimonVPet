/////////////////////////////////////////////////////////////////
/*
  main.cpp - main programm to test the VPetLCD Class and the
  screen classes. JUST FOR TESTING PURPOSES This is the *.ino file
  from the arduino ide
  Created by Berat Özdemir, January 16 , 2021.
*/
/////////////////////////////////////////////////////////////////

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


#include "GameLogic/ScreenStateMachine.h"

#include "GameLogic/Digimon.h"
#include "SaveGame/SaveGameHandler.h"


SaveGameHandler savegame;
uint16_t digiIndex =DIGIMON_BOTAMON;
Digimon digimon(digiIndex);

//ESP32 Specific stuff
#include "VPetLCD/DisplayAdapter/TFT_eSPI_Displayadapter.h"
#include "VPetLCD/ESP32SpriteManager.h"
#include "GameLogic/ESP32DigimonDataLoader.h"

#include <TFT_eSPI.h>
#include "Button2.h"
#include <Arduino.h>


#define ADC_EN 14 //ADC_EN is the ADC detection enable port
#define ADC_PIN 34
#define BUTTON_1 35
#define BUTTON_2 0

Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);

int hours = 23;
int minutes = 59;
int seconds = 0;

boolean buttonPressed = false;

int displayHeight = 240;
int displayWidth = 135;


//TFT_eSPI-Only stuff
TFT_eSPI tft = TFT_eSPI(displayWidth, displayHeight); // Create object "tft"
TFT_eSprite img = TFT_eSprite(&tft);                  // Create Sprite object "img" with pointer to "tft" object
TFT_eSPI_DisplayAdapter displayAdapter(&img, displayHeight, displayWidth);         //create a DisplayAdapter for VPetLCD class
//--------

//ESP32 Only stuff
ESP32SpriteManager spriteManager;
ESP32DigimonDataLoader dataLoader;
//

//Creating all instances for the UI
VPetLCD screen(&displayAdapter, &spriteManager, 40, 16);
VPetLCDMenuBar32p menuBar(7,5,displayHeight);

V20::DigimonWatchingScreen digimonScreen(&spriteManager, digimon.getDigimonIndex(), -8, 40, 0, 0);
V20::DigimonNameScreen digiNameScreen(&spriteManager, dataLoader.getDigimonProperties(digiIndex)->digiName, digimon.getDigimonIndex(), 24);
V20::AgeWeightScreen ageWeightScreen(5, 21);
V20::HeartsScreen hungryScreen("Hungry", 2, 4);
V20::HeartsScreen strengthScreen("Strength", 3, 4);
V20::HeartsScreen effortScreen("Effort", 4, 4);
V20::ProgressBarScreen dpScreen("DP", 29, 40);
V20::PercentageScreen sPercentageScreen("WIN", 'S', 100);
V20::PercentageScreen tPercentageScreen("WIN", 'T', 93);
V20::SelectionScreen foodSelection(true);
V20::SelectionScreen fightSelection(true);
V20::ClockScreen clockScreen(true);
V20::EatingAnimationScreen eatingAnimationScreen(&spriteManager, digimon.getDigimonIndex());

//13 screens and 3 signals (one for each button)
uint8_t numberOfScreens = 13;
uint8_t numberOfSignals = 3;

uint8_t confirmSignal = 0;
uint8_t nextSignal = 1;
uint8_t backSignal = 2;

//Creating the ScreenStateMachine, which handles transitions between screens
//and the actions of the buttons; the buttons are just sending signals to the statemachine
ScreenStateMachine stateMachine(numberOfScreens, numberOfSignals);

uint8_t digimonScreenId = stateMachine.addScreen(&digimonScreen);
uint8_t digiNameScreenId = stateMachine.addScreen(&digiNameScreen);
uint8_t ageWeightScreenId = stateMachine.addScreen(&ageWeightScreen);
uint8_t hungryScreenId = stateMachine.addScreen(&hungryScreen);
uint8_t strengthScreenId = stateMachine.addScreen(&strengthScreen);
uint8_t effortScreenId = stateMachine.addScreen(&effortScreen);
uint8_t dpScreenId = stateMachine.addScreen(&dpScreen);
uint8_t sPercentageScreenId = stateMachine.addScreen(&sPercentageScreen);
uint8_t tPercentageScreenId = stateMachine.addScreen(&tPercentageScreen);
uint8_t foodSelectionId = stateMachine.addScreen(&foodSelection);
uint8_t fightSelectionId = stateMachine.addScreen(&fightSelection);
uint8_t clockScreenId = stateMachine.addScreen(&clockScreen);
uint8_t eatingAnimationScreenId = stateMachine.addScreen(&eatingAnimationScreen);

uint8_t poop=0;

void stateMachineInit() {
  const DigimonProperties *properties = dataLoader.getDigimonProperties(digimon.getDigimonIndex());
  digimon.setProperties(properties);
  digimon.printSerial();


  //return to food selection screen after showing eating animation
  eatingAnimationScreen.setAnimationEndAction([]() {
    stateMachine.setCurrentScreen(foodSelectionId);

    });

  // in order to be able to go back to the digimon watching screen
  // we will add a transition from every screen to the digimon watching screen
  //triggered by the backsignal (backbutton)
  for (int i = 1; i <= numberOfScreens + 1;i++) {
    stateMachine.addTransition(i, digimonScreenId, backSignal);
  }

  //The Scale Menu transitions
  stateMachine.addTransition(digiNameScreenId, ageWeightScreenId, nextSignal);
  stateMachine.addTransition(ageWeightScreenId, hungryScreenId, nextSignal);
  stateMachine.addTransition(hungryScreenId, strengthScreenId, nextSignal);
  stateMachine.addTransition(strengthScreenId, effortScreenId, nextSignal);
  stateMachine.addTransition(effortScreenId, dpScreenId, nextSignal);
  stateMachine.addTransition(dpScreenId, sPercentageScreenId, nextSignal);
  stateMachine.addTransition(sPercentageScreenId, tPercentageScreenId, nextSignal);
  stateMachine.addTransition(tPercentageScreenId, digiNameScreenId, nextSignal);

  //Transitions between clock screen and digimon watching screen
  stateMachine.addTransition(digimonScreenId, clockScreenId, backSignal);
  stateMachine.addTransition(clockScreenId, digimonScreenId, backSignal);


  //Conditional transtitions from digimonScreen to the others (menuselection)
  //this must be set, because unset transitions wont trigger transitionActions
  stateMachine.addTransition(digimonScreenId, digimonScreenId, nextSignal);

  //if nextSignal is sent (nextbutton pressed), the menuselection will be
  //incremented and the selection will be set
  stateMachine.addTransitionAction(digimonScreenId, nextSignal, []() {
      menuBar.nextSelection();
    });

  //Here are the conditional transitions handled.
  stateMachine.addTransition(digimonScreenId, digimonScreenId, confirmSignal);
  stateMachine.addTransitionAction(digimonScreenId, confirmSignal, []() {
    uint8_t maxdp = digimon.getProperties()->maxDigimonPower;
    switch (menuBar.getSelection()) {
    case 0:
      digiNameScreen.setDigimonSpriteIndex(digimon.getDigimonIndex());
      hungryScreen.setHearts(4-4*digimon.getHunger()/10);
      
      if(maxdp >0){
        dpScreen.setFillPercentage((digimon.getDigimonPower()*100)/maxdp);
      }else{
        dpScreen.setFillPercentage(0);
      }
      ageWeightScreen.setAge(digimon.getAge());
      ageWeightScreen.setWeight(digimon.getWeight());
      stateMachine.setCurrentScreen(digiNameScreenId);
      break;
    case 1:
      foodSelection.setSelection(0);
      stateMachine.setCurrentScreen(foodSelectionId);
      break;
    case 3:
      fightSelection.setSelection(0);
      stateMachine.setCurrentScreen(fightSelectionId);
      break;

    case 4:
      
      digimonScreen.flushPoop();
      digimon.setNumberOfPoops(0);
      break;

    case 2:

      break;
    }
    });


  //adding functionality of buttons in food screen:
  stateMachine.addTransition(foodSelectionId, foodSelectionId, nextSignal);
  stateMachine.addTransitionAction(foodSelectionId, nextSignal, []() {
    foodSelection.nextSelection();
    });

  //adding functionality of buttons in food screen:
  stateMachine.addTransition(foodSelectionId, foodSelectionId, confirmSignal);
  stateMachine.addTransitionAction(foodSelectionId, confirmSignal, []() {
    uint8_t selection = foodSelection.getSelection();
    switch (selection) {
    case 0:
      digimon.addWeight(1);
      digimon.reduceHunger(1);
      eatingAnimationScreen.setSprites(SYMBOL_MEAT, SYMBOL_HALF_MEAT,SYMBOL_EMPTY_MEAT);
      eatingAnimationScreen.startAnimation();
      stateMachine.setCurrentScreen(eatingAnimationScreenId);
      break;
    case 1:
      digimon.addWeight(2);
      digimon.addStrength(2);
      digimon.addDigimonPower(2);
      eatingAnimationScreen.setSprites(SYMBOL_PILL, SYMBOL_HALF_PILL,SYMBOL_EMPTY);
      eatingAnimationScreen.startAnimation();
      stateMachine.setCurrentScreen(eatingAnimationScreenId);
      break;

    case 2:
      eatingAnimationScreen.setSprites(SYMBOL_HEART, SYMBOL_HEARTEMPTY,SYMBOL_EMPTY);
      eatingAnimationScreen.startAnimation();
      stateMachine.setCurrentScreen(eatingAnimationScreenId);
      break;
    case 3:
      eatingAnimationScreen.setSprites(SYMBOL_POOP,SYMBOL_HALF_PILL,SYMBOL_EMPTY);
      eatingAnimationScreen.startAnimation();
      stateMachine.setCurrentScreen(eatingAnimationScreenId);
      break;

    }
    });

    //go back to food selection if pressed confirm again
    stateMachine.addTransition(eatingAnimationScreenId, foodSelectionId, confirmSignal);
    //abort animation
    stateMachine.addTransitionAction(eatingAnimationScreenId, confirmSignal, [](){
      eatingAnimationScreen.abortAnimation();
    });

  //adding functionality of buttons in fight screen:
  stateMachine.addTransition(fightSelectionId, fightSelectionId, nextSignal);
  stateMachine.addTransitionAction(fightSelectionId, nextSignal, []() {
    fightSelection.nextSelection();

    });



}


void button_init()
{
  btn1.setLongClickHandler([](Button2& b) {
    stateMachine.sendSignal(backSignal);
    buttonPressed = true;
    });

  btn1.setPressedHandler([](Button2& b) {
    stateMachine.sendSignal(nextSignal);
    buttonPressed = true;
    });

  btn2.setPressedHandler([](Button2& b) {
    stateMachine.sendSignal(confirmSignal);
    buttonPressed = true;
    });
}

void setupScreens()
{
  menuBar.setIconOnIndex(0,0);
  menuBar.setIconOnIndex(1,1);
  menuBar.setIconOnIndex(2,2);
  menuBar.setIconOnIndex(3,3);
  menuBar.setIconOnIndex(4,4);
  menuBar.setIconOnIndex(5,5);
  menuBar.setIconOnIndex(6,6);


  screen.setMenuBar(&menuBar);
  screen.setLCDPos(0, 32);
  screen.setLcdScale(6);

  //Positioning of the screens
  int screensOffsetX = 4;


  //set offset of the screens
  ageWeightScreen.setPos(screensOffsetX, 0);
  effortScreen.setPos(screensOffsetX, 0);
  strengthScreen.setPos(screensOffsetX, 0);
  hungryScreen.setPos(screensOffsetX, 0);
  dpScreen.setPos(screensOffsetX, 0);
  sPercentageScreen.setPos(screensOffsetX, 0);
  tPercentageScreen.setPos(screensOffsetX, 0);
  clockScreen.setPos(screensOffsetX, 0);
  eatingAnimationScreen.setPos(screensOffsetX, 0);
  


  //adding the food selection options
  foodSelection.addOption("Meat", SYMBOL_MEAT);
  foodSelection.addOption("PILL", SYMBOL_PILL);
  foodSelection.addOption("LOVE", SYMBOL_HEART);
  foodSelection.addOption("SHIT", SYMBOL_POOP);

  //adding the battle options
  fightSelection.setShowIcons(false);
  fightSelection.addOption("SINGLE");
  fightSelection.addOption("TAG");

  clockScreen.setHours(hours);
  clockScreen.setMinutes(minutes);
  clockScreen.setSeconds(seconds);
}

// =========================================================================
void setup(void)
{
  Serial.begin(115200);
  Serial.println("Start");

  pinMode(ADC_EN, OUTPUT);
  digitalWrite(ADC_EN, HIGH);

  randomSeed(analogRead(1));
  savegame.init();
  /*
  digimon.setDigimonIndex(10);
    digimon.setState(20);
    digimon.setAge(30);
    digimon.setWeight(40);
    digimon.setFeedCounter(50);
    digimon.setCareMistakes(60);
    digimon.setTrainingCounter(70);
    digimon.setTimeUntilEvolution(80);
    digimon.setPoopTimer(90);
    digimon.setAgeTimer(100);
    digimon.setEvolutionTimer(110);
    Serial.println(digimon.getDigimonIndex());
  Serial.println(digimon.getState());
  Serial.println(digimon.getAge());
  Serial.println(digimon.getWeight());
  Serial.println(digimon.getFeedCounter());
  Serial.println(digimon.getCareMistakes());
  Serial.println(digimon.getTrainingCounter());
  Serial.println(digimon.getTimeUntilEvolution());
  Serial.println(digimon.getPoopTimer());
  Serial.println(digimon.getAgeTimer());
  Serial.println(digimon.getEvolutionTimer());
  savegame.saveDigimon(&digimon);
  */

 //savegame.loadDigimon(&digimon);

  //Some tft initialization stuff
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(0x86CE);

//init functions
  button_init();
  setupScreens();
  stateMachineInit();
}
// =========================================================================

unsigned long ticker = 0;
unsigned long tickerResetValue = 1000;
unsigned long lastDelta = 0;
float getFragmentation() ;
boolean debug=false;

void loop()
{

  //tft.fillScreen(0x86CE);
  unsigned long t1 = millis();


  digimon.loop(lastDelta);
  digimonScreen.setNumberOfPoop(digimon.getNumberOfPoops());


  //updating the screens which need the loop
  digimonScreen.loop(lastDelta);
  clockScreen.loop(lastDelta);
  digiNameScreen.loop(lastDelta);


  //switch to next frame only when the screen is active
  if (stateMachine.getCurrentScreen() == &eatingAnimationScreen)
    eatingAnimationScreen.loop(lastDelta);
  
  screen.renderScreen(stateMachine.getCurrentScreen());
  

  buttonPressed = false;

  if (debug == true)
  {
    //here should be debug stuff but its only fps lol
    tft.setTextColor(TFT_BLACK);
    tft.fillRect(0, 0, 100, 20, 0xFFFF);
    tft.drawString(String((1000.0) / lastDelta) + " FPS", 0, 0);
    tft.drawString( "Fragmentation: "+String(getFragmentation()) , 0, 10);
  
  }

  btn1.loop();
  btn2.loop();

  unsigned long t2 = millis();
  lastDelta = t2 - t1;
}




//measure the HeapFragmentation
float getFragmentation() {
  
  return 100 - heap_caps_get_largest_free_block(MALLOC_CAP_8BIT) * 100.0 / heap_caps_get_free_size(MALLOC_CAP_8BIT);
}