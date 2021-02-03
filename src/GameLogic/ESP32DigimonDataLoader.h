#include "AbstractDigimonDataLoader.h"

#include "../VPetLCD/ImageData/DigimonSprites.h"

class ESP32DigimonDataLoader : public AbstractDigimonDataLoader{
    DigimonProperties properties;
    public:
    const DigimonProperties* getDigimonProperties(uint16_t digimonIndex){
        properties = DIGIMON_DATA[digimonIndex];
        return &DIGIMON_DATA[digimonIndex];
    }
};