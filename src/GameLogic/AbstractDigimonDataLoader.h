#include <Arduino.h>
#include "Digimon.h"
//This Class provides an interface which reads the digimon Data from Progmem

class AbstractDigimonDataLoader {
public:
    const DigimonProperties* getDigimonProperties(uint16_t digimonIndex);


};