
#include <Arduino.h>
#include <EEPROM.h>
#include "../GameLogic/Digimon.h"

#define EEPROM_SIZE 256 

#define ADRESS_DIGIMONINDEX 0 //2byte
#define ADDRESS_STATE 2 //1byte
#define ADDRESS_AGE 3 //2byte
#define ADDRESS_WEIGHT 5 //2byte
#define ADDRESS_FEEDCOUNTER 7//2byte
#define ADDRESS_CAREMISTAKES 9//2byte
#define ADDRESS_TRAININGCOUNTER 11//2byte
#define ADDRESS_NUMBEROFPOOPS 13//1byte
#define ADDRESS_HUNGER 14//1byte
#define ADDRESS_STRENGTH 15//1byte
#define ADDRESS_EFFORT 16//1byte
#define ADDRESS_POOPTIMER 17//4byte
#define ADDRESS_AGETIMER 21//4byte
#define ADDRESS_EVOLUTIONETIMER 25 //4byte
#define ADDRESS_DIGIMONPOWER 26 //1byte

class SaveGameHandler{

    public:
        SaveGameHandler(){};
        void init(){EEPROM.begin(EEPROM_SIZE);}
        void loadDigimon(Digimon* digimon);
        void saveDigimon(Digimon* digimon);


};