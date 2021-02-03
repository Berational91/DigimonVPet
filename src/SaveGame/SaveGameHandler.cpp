#include "SaveGameHandler.h"

void SaveGameHandler::loadDigimon(Digimon* digimon) {
    digimon->setDigimonIndex(EEPROM.readUShort(ADRESS_DIGIMONINDEX));
    digimon->setState(EEPROM.readByte(ADDRESS_STATE));
    digimon->setAge(EEPROM.readUShort(ADDRESS_AGE));
    digimon->setWeight(EEPROM.readUShort(ADDRESS_WEIGHT));
    digimon->setFeedCounter(EEPROM.readUShort(ADDRESS_FEEDCOUNTER));
    digimon->setCareMistakes(EEPROM.readUShort(ADDRESS_CAREMISTAKES));
    digimon->setTrainingCounter(EEPROM.readUShort(ADDRESS_TRAININGCOUNTER));
    digimon->setPoopTimer(EEPROM.readULong(ADDRESS_POOPTIMER));
    digimon->setAgeTimer(EEPROM.readULong(ADDRESS_AGETIMER));
    digimon->setEvolutionTimer(EEPROM.readULong(ADDRESS_EVOLUTIONETIMER));

    digimon->setNumberOfPoops(EEPROM.readByte(ADDRESS_NUMBEROFPOOPS));
    digimon->setHunger(EEPROM.readByte(ADDRESS_HUNGER));
    digimon->setStrength(EEPROM.readByte(ADDRESS_STRENGTH));
    digimon->setEffort(EEPROM.readByte(ADDRESS_EFFORT));
    digimon->setDigimonPower(EEPROM.readByte(ADDRESS_DIGIMONPOWER));
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