/////////////////////////////////////////////////////////////////
/*
  main.cpp - main programm to test the VPetLCD Class and the
  screen classes. JUST FOR TESTING PURPOSES This is the *.ino file
  from the arduino ide
  Created by Berat Özdemir, January 16 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "VPetLCD/VPetLCD.h"
#include "VPetLCD/Screens/AgeWeightScreen.h"
#include "VPetLCD/Screens/DigimonNameScreen.h"
#include "VPetLCD/Screens/HeartsScreen.h"
#include "VPetLCD/Screens/ProgressBarScreen.h"
#include "VPetLCD/Screens/PercentageScreen.h"
#include "VPetLCD/Screens/SelectionScreen.h"
#include "VPetLCD/Screens/ClockScreen.h"
#include "VPetLCD/Screens/DigimonWatchingScreen.h"

#include "GameLogic/ScreenStateMachine.h"

#include "VPetLCD/DisplayAdapter/TFT_eSPI_Displayadapter.h"

#include <TFT_eSPI.h>
#include "Button2.h"

int displayHeight = 240;
int displayWidth =135 ;

TFT_eSPI tft = TFT_eSPI(displayWidth, displayHeight); // Create object "tft"
TFT_eSprite img = TFT_eSprite(&tft);                  // Create Sprite object "img" with pointer to "tft" object
TFT_eSPI_DisplayAdapter displayAdapter(&img,displayHeight,displayWidth);         //create a DisplayAdapter for VPetLCD class


#define ADC_EN 14 //ADC_EN is the ADC detection enable port
#define ADC_PIN 34
#define BUTTON_1 35
#define BUTTON_2 0

Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);

//method for being fps independent
boolean fpslock(long delta);

boolean debug = true;

uint32_t menuSelection = 0;
int numberOfMenuEntries = 5;

uint8_t menuFoodSelection = 0;
uint8_t menuFoodSelectionMax = 4;

int hours = 23;
int minutes = 59;
int seconds = 0;

boolean buttonPressed = false;

VPetLCD screen(&displayAdapter, 40, 16);

V20::DigimonWatchingScreen digimonScreen(DIGIMON_AGUMON, -8, 40, 0, 0);
V20::DigimonNameScreen digiNameScreen("Agumon", DIGIMON_AGUMON, 24);
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


//12 screens and 3 signals (one for each button)
uint8_t numberOfScreens = 12;

uint8_t confirmSignal = 0;
uint8_t nextSignal = 1;
uint8_t backSignal = 2;

ScreenStateMachine stateMachine(numberOfScreens, 3);

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





void stateMachineInit() {
  stateMachine.printTransitions();
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

    menuSelection++;
    menuSelection %= numberOfMenuEntries;
    screen.setSelectedMenuItemIndex(menuSelection);
    });

  //Here are the conditional transitions handled.
  stateMachine.addTransition(digimonScreenId, digimonScreenId, confirmSignal);
  stateMachine.addTransitionAction(digimonScreenId, confirmSignal, []() {
    Serial.print(menuSelection);
    switch (menuSelection) {
    case 0:
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
    }
    });


  //adding functionality of buttons in food screen:
  stateMachine.addTransition(foodSelectionId, foodSelectionId, nextSignal);
  stateMachine.addTransitionAction(foodSelectionId, nextSignal, []() {
    foodSelection.nextSelection();
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
  screen.setSelectedMenuItemIndex(menuSelection);
  screen.setLCDPos(0, 32);
  screen.setLcdScale(6);

  //Positioning of the screens
  int screensOffsetX = 4;

  ageWeightScreen.setPos(screensOffsetX, 0);
  effortScreen.setPos(screensOffsetX, 0);
  strengthScreen.setPos(screensOffsetX, 0);
  hungryScreen.setPos(screensOffsetX, 0);
  dpScreen.setPos(screensOffsetX, 0);
  sPercentageScreen.setPos(screensOffsetX, 0);
  tPercentageScreen.setPos(screensOffsetX, 0);
  clockScreen.setPos(screensOffsetX, 0);

  foodSelection.addOption("Meat", SYMBOL_MEAT);
  foodSelection.addOption("PILL", SYMBOL_PILL);

  foodSelection.addOption("LOVE", SYMBOL_HEART);

  foodSelection.addOption("SHIT", SYMBOL_POOP);
  //foodSelection.addOption("FOUR", SYMBOL_TRIANGLE);
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

  //Some tft initialization stuff
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(0x86CE);

  button_init();

  setupScreens();
  stateMachineInit();
}
// =========================================================================

unsigned long ticker = 0;
unsigned long tickerResetValue = 1000;
unsigned long lastDelta = 0;

void loop()
{

  //tft.fillScreen(0x86CE);
  unsigned long t1 = millis();

  boolean locked = fpslock(lastDelta);

  if (!locked)
  {
    digimonScreen.randomMoveDigimon();
    clockScreen.incrementSeconds();
    digiNameScreen.scrollText();
  }


  if (!locked || buttonPressed || true)
  {
    screen.renderScreen(stateMachine.getCurrentScreen());
  }

  buttonPressed = false;

  if (debug == true)
  {
    tft.setTextColor(TFT_BLACK);
    tft.fillRect(0, 0, 100, 10, 0xFFFF);
    tft.drawString(String((1000.0) / lastDelta) + " FPS", 0, 0);

    //tft.drawString(String(ax)+" ax", 0, 20);
    //tft.drawString(String(selection)+" selection", 0, 30);
  }

  btn1.loop();
  btn2.loop();

  unsigned long t2 = millis();
  lastDelta = t2 - t1;
}

boolean fpslock(long delta)
{
  ticker += delta;
  if (ticker > tickerResetValue)
  {
    ticker = 0;
    return false;
  }
  return true;
}
