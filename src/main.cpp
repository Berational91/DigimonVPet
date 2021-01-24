/////////////////////////////////////////////////////////////////
/*
  main.cpp - main programm to test the VPetLCD Class and the 
  screen classes 
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

#include <TFT_eSPI.h>
#include "Button2.h"


int displayWidth = 135;
int displayHeight = 240;

TFT_eSPI    tft = TFT_eSPI(displayWidth, displayHeight);        // Create object "tft"
TFT_eSprite img = TFT_eSprite(&tft);// Create Sprite object "img" with pointer to "tft" object


#define BITS_PER_PIXEL 1              // How many bits per pixel in Sprite

#define PIXELSCALE 6

#define ADC_EN              14  //ADC_EN is the ADC detection enable port
#define ADC_PIN             34
#define BUTTON_1            35
#define BUTTON_2            0

Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);


boolean fpslock(long delta);
boolean randomDecision(int percent);

boolean debug = true;
int ax = 5;
int ay = 0;

boolean goleft = true;

int n_sprites = 2;
int currentSprite = 0;
int selection = 0;
int currentScreen = -1;
int subSelection = 0;
int maxSubmenues[] = {8, 4, 0, 2, 0};

int hours = 23;
int minutes = 59;
int seconds = 0;


boolean buttonPressed = false;

VPetLCD screen(&img, 48, 24);
V20::DigimonNameScreen digiNameScreen("Agumon",DIGIMON_AGUMON, 24);
V20::AgeWeightScreen ageWeightScreen(5,21);
V20::HeartsScreen hungryScreen("Hungry", 2, 4);
V20::HeartsScreen strengthScreen("Strength", 3, 4);
V20::HeartsScreen effortScreen("Effort", 4, 4);
V20::ProgressBarScreen dpScreen("DP", 29, 40);
V20::PercentageScreen sPercentageScreen("WIN",'S',100);
V20::PercentageScreen tPercentageScreen("WIN",'T',93);
V20::SelectionScreen foodSelection(true);
V20::SelectionScreen fightSelection(true);
V20::ClockScreen clockScreen(true);
V20::DigimonWatchingScreen digimonScreen(DIGIMON_AGUMON, -8, 40, 0, 16);

void button_init()
{
  btn1.setLongClickHandler([](Button2 & b) {
    currentScreen = -1;
    buttonPressed = true;
  });


  btn1.setPressedHandler([](Button2 & b) {
    if(currentScreen == -1){
      selection++;
      selection %= 5;
      screen.setSelectedMenuItemIndex(selection);
  
      buttonPressed = true;
    }
  });


  btn2.setPressedHandler([](Button2 & b) {
    if (currentScreen != selection) {
      currentScreen = selection;
      subSelection = 0;
    } else {
      subSelection++;
      if (subSelection >= maxSubmenues[selection]) {
        subSelection = 0;
        //currentScreen = -1;
      }
    }


    buttonPressed = true;
  });
}

void setupScreens(){
  screen.setSelectedMenuItemIndex(selection);
  screen.setLCDPos(24,32);
  screen.setLcdScale(4);

  //Positioning of the screens
  int screensOffsetX =0;

  ageWeightScreen.setPos(screensOffsetX,0);
  effortScreen.setPos(screensOffsetX,0);
  strengthScreen.setPos(screensOffsetX,0);
  hungryScreen.setPos(screensOffsetX,0);
  dpScreen.setPos(screensOffsetX,0);
  sPercentageScreen.setPos(screensOffsetX,0);
  tPercentageScreen.setPos(screensOffsetX,0);
  clockScreen.setPos(screensOffsetX,0);

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
void setup(void) {
  Serial.begin(115200);
  Serial.println("Start");

  pinMode(ADC_EN, OUTPUT);
  digitalWrite(ADC_EN, HIGH);

  randomSeed(analogRead(1));
  tft.init();


  tft.setRotation(1);
  tft.fillScreen(0x86CE);
  button_init();


  //screen.setDigimonAnimation(agumon_anim);
  setupScreens();
}
// =========================================================================



unsigned long ticker = 0;
unsigned long tickerResetValue = 1000;
unsigned long lastDelta = 0;

void loop() {

  //tft.fillScreen(0x86CE);
  unsigned long t1 = millis();

  boolean locked = fpslock(lastDelta);

  if ( !locked ) {
    digimonScreen.randomMoveDigimon();
    clockScreen.incrementSeconds();
    digiNameScreen.scrollText();
  }

  if ( !locked || buttonPressed ) {
    switch (currentScreen) {
      case 0:
        switch (subSelection) {
          case 0:
            screen.renderScreen(&digiNameScreen);
            break;
          case 1:
            screen.renderScreen(&ageWeightScreen);
            break;
          case 2:
            screen.renderScreen(&hungryScreen);
            break;
          case 3:
            screen.renderScreen(&strengthScreen);
            break;
          case 4:
            screen.renderScreen(&effortScreen);
            break;
          case 5:
            screen.renderScreen(&dpScreen);
            break;
          case 6:
            screen.renderScreen(&sPercentageScreen);
            break;
          case 7:
            screen.renderScreen(&tPercentageScreen);
            break;
        }
        break;

      case 1:
        foodSelection.setSelection(subSelection);
        screen.renderScreen(&foodSelection);
        break;

      case 2:
      screen.renderScreen(&clockScreen);
      break;

      case 3:
      fightSelection.setSelection(subSelection);
      screen.renderScreen(&fightSelection);
      break;

      default:
        screen.renderScreen(&digimonScreen);
        break;
    }

  }


  buttonPressed = false;



  if (debug == true) {
    tft.setTextColor(TFT_BLACK);
    tft.fillRect(0, 0 , 100, 10, 0xFFFF);
    tft.drawString(String((1000.0) / lastDelta) + " FPS", 0, 0);

    //tft.drawString(String(ax)+" ax", 0, 20);
    //tft.drawString(String(selection)+" selection", 0, 30);
  }

  btn1.loop();
  btn2.loop();

  unsigned long t2 = millis();
  lastDelta = t2 - t1;
}


boolean fpslock(long delta) {
  ticker += delta;
  if (ticker > tickerResetValue) {
    ticker = 0;
    return false;
  }
  return true;
}

