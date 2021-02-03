#include <Arduino.h>
#include "Digimon.h"
//This Class provides an interface which reads the digimon Data from Progmem
class AbstractDigimonDataLoader {
public:
    // reads the digimon Data from Progmem and returns a pointer to the data
    const DigimonProperties* getDigimonProperties(uint16_t digimonIndex);


};