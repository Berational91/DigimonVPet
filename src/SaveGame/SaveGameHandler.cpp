#include "SaveGameHandler.h"

void SaveGameHandler::loadDigimon(Digimon* digimon) {
    uint16_t digiIndex =0;
    EEPROM.get(ADRESS_DIGIMONINDEX, digiIndex);
    digimon->setDigimonIndex(digiIndex);

    uint8_t state =0;
    EEPROM.get(ADDRESS_STATE, state);    
    digimon->setState(state);

    uint16_t age =0;
    EEPROM.get(ADDRESS_AGE, age);
    digimon->setAge(age);

    uint16_t weight =0;
    EEPROM.get(ADDRESS_WEIGHT, weight);
    digimon->setWeight(weight);

    uint16_t feedcounter =0;
    EEPROM.get(ADDRESS_FEEDCOUNTER, feedcounter);
    digimon->setFeedCounter(feedcounter);

    uint16_t careMistakes =0;
    EEPROM.get(ADDRESS_CAREMISTAKES, careMistakes);
    digimon->setCareMistakes(careMistakes);

    uint16_t tCounter =0;
    EEPROM.get(ADDRESS_TRAININGCOUNTER, tCounter);
    digimon->setTrainingCounter(tCounter);

    unsigned long poopTimer =0;
    EEPROM.get(ADDRESS_POOPTIMER, poopTimer);
    digimon->setPoopTimer(poopTimer);

    unsigned long ageTimer =0;
    EEPROM.get(ADDRESS_AGETIMER, ageTimer);
    digimon->setAgeTimer(ageTimer);

    unsigned long evolutionTimer =0;
    EEPROM.get(ADDRESS_EVOLUTIONETIMER, evolutionTimer);
    digimon->setEvolutionTimer(evolutionTimer);


    byte numPoops =0;
    EEPROM.get(ADDRESS_NUMBEROFPOOPS, numPoops);
    digimon->setNumberOfPoops(numPoops);

    byte hunger =0;
    EEPROM.get(ADDRESS_HUNGER, hunger);
    digimon->setHunger(hunger);
    
    byte strength =0;
    EEPROM.get(ADDRESS_STRENGTH, strength);
    digimon->setStrength(strength);

    byte effort =0;
    EEPROM.get(ADDRESS_EFFORT, effort);
    digimon->setEffort(effort);

    byte dPower =0;
    EEPROM.get(ADDRESS_DIGIMONPOWER, dPower);
    digimon->setDigimonPower(dPower);
}

void SaveGameHandler::saveDigimon(Digimon* digimon) {
    EEPROM.put(ADRESS_DIGIMONINDEX,digimon->getDigimonIndex());
    EEPROM.put(ADDRESS_STATE,digimon->getState());
    EEPROM.put(ADDRESS_AGE,digimon->getAge());
    EEPROM.put(ADDRESS_WEIGHT,digimon->getWeight());
    EEPROM.put(ADDRESS_FEEDCOUNTER,digimon->getFeedCounter());
    EEPROM.put(ADDRESS_CAREMISTAKES,digimon->getCareMistakes());
    EEPROM.put(ADDRESS_TRAININGCOUNTER,digimon->getTrainingCounter());
    EEPROM.put(ADDRESS_POOPTIMER,digimon->getPoopTimer());
    EEPROM.put(ADDRESS_AGETIMER,digimon->getAgeTimer());
    EEPROM.put(ADDRESS_EVOLUTIONETIMER,digimon->getEvolutionTimer());
    EEPROM.put(ADDRESS_NUMBEROFPOOPS,digimon->getNumberOfPoops());
    EEPROM.put(ADDRESS_HUNGER,digimon->getHunger());
    EEPROM.put(ADDRESS_STRENGTH,digimon->getStrength());
    EEPROM.put(ADDRESS_EFFORT,digimon->getEffort());
    EEPROM.put(ADDRESS_DIGIMONPOWER,digimon->getDigimonPower());
    EEPROM.commit();
}