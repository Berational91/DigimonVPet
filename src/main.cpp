/////////////////////////////////////////////////////////////////
/*
  main.cpp - main programm to test the VPetLCD Class and the
  screen classes. JUST FOR TESTING PURPOSES This is the *.ino file
  from the arduino ide
  Created by Berat Özdemir, January 16 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "VPet/VPet.h"
#include "SaveGame/SaveGameHandler.h"


//ESP32 Specific stuff
#include "VPetLCD/DisplayAdapter/TFT_eSPI_Displayadapter.h"
#include "VPetLCD/ESP32SpriteManager.h"
#include "GameLogic/ESP32DigimonDataLoader.h"

#include "VPetLCD/DisplayAdapter/MAX72XX_Display_Adapter.h"
#include "LedControl_SW_SPI.h"

//ESP8266 Specific stuff
#include "Wire.h"
#include "Adafruit_SSD1306.h"
#include "VPetLCD/DisplayAdapter/SSD1306DisplayAdapter.h"

/*
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 ssddisplay(128, 64, &Wire, OLED_RESET);
SSD1306DisplayAdapter ssddisplayAdapter(&ssddisplay,128,64);
*/

/*ttgo tdisplay */
#define DIN 32
#define CS 33
#define CLK 25

/*
#define DIN 13
#define CS 12
#define CLK 14
*/
/*
LedControl_SW_SPI ledDisplay;
MAX72XX_Display_Adapter ledDisplayAdapter(&ledDisplay);
*/

#include <TFT_eSPI.h>
#include "Button2.h"
#include <Arduino.h>


#define ADC_EN 14 //ADC_EN is the ADC detection enable port
#define ADC_PIN 34
#define BUTTON_1 35
#define BUTTON_2 0

Button2 btn1(BUTTON_1);
Button2 btn2(BUTTON_2);


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

/*
const int rs = 0, en = 1, d4 = 2, d5 = 3, d6 = 4, d7 = 5;
LiquidCrystal lcd = LiquidCrystal(rs,en,d4,d5,d6,d7);
HD44870_DisplayAdapter hDisplayAdapter = HD44870_DisplayAdapter(&lcd,16,16);
*/
SaveGameHandler saveGame;

VPet vpet(&displayAdapter, &spriteManager, &dataLoader,&saveGame);


void button_init()
{
  btn1.setLongClickHandler([](Button2& b) {
    vpet.sendSignal(BACK_SIGNAL);
    buttonPressed = true;
    });

  btn1.setPressedHandler([](Button2& b) {
    vpet.sendSignal(NEXT_SIGNAL);
    buttonPressed = true;
    });

  btn2.setPressedHandler([](Button2& b) {
    vpet.sendSignal(CONFIRM_SIGNAL);
    buttonPressed = true;
    });
}

// =========================================================================
void setup(void)
{
  Serial.begin(115200);
  Serial.println("Start");
  pinMode(ADC_EN, OUTPUT);
  pinMode(DIN, OUTPUT);
  pinMode(CLK, OUTPUT); 
  pinMode(CS, OUTPUT);
  digitalWrite(ADC_EN, HIGH);

  /*ledDisplay.begin(DIN, CLK,CS,8);
  for(int i =0; i <8; i++){
    ledDisplay.shutdown(i, false);
    ledDisplay.setIntensity(i, 1);
     ledDisplay.clearDisplay(i);
     ledDisplay.setLed(i,i,0,true);
  }
 // ledDisplayAdapter.deleteCanvas();
    // ledDisplayAdapter.fillRect(0,4,24,8,1);
    // ledDisplayAdapter.pushCanvas(0,0,1);
*/
 
/*
  if(!ssddisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }*/
  randomSeed(analogRead(1));
 // savegame.init();
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
  
  vpet.setup();
  //vpet.hideMenuBar();
//init functions
  button_init();
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


  
  vpet.loop(lastDelta);
  buttonPressed = false;

  if (debug == true)
  {
    /*
    //here should be debug stuff but its only fps lol
    tft.setTextColor(TFT_BLACK);
    tft.fillRect(0, 0, 100, 20, 0xFFFF);
    tft.drawString(String((1000.0) / lastDelta) + " FPS", 0, 0);
    tft.drawString( "Fragmentation: "+String(getFragmentation()) , 0, 10);
    */
  }

  btn1.loop();
  btn2.loop();

  unsigned long t2 = millis();
  lastDelta = t2 - t1;
}




//measure the HeapFragmentation
float getFragmentation() {
  return 0;
  //return 100 - heap_caps_get_largest_free_block(MALLOC_CAP_8BIT) * 100.0 / heap_caps_get_free_size(MALLOC_CAP_8BIT);
}