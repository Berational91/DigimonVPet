#include "Digimon.h"

void Digimon::printSerial(){

  Serial.println(getDigimonIndex());
  Serial.println(getState());
  Serial.println(getAge());
  Serial.println(getWeight());
  Serial.println(getFeedCounter());
  Serial.println(getCareMistakes());
  Serial.println(getTrainingCounter());
  Serial.println(getPoopTimer());
  Serial.println(getAgeTimer());
  Serial.println(getEvolutionTimer());
}


void Digimon::loop(unsigned long delta){

    updateTimers(delta);
}


void Digimon::updateTimers(unsigned long delta){
    poopTimer += delta;
    if(poopTimer > properties->poopTimeSec*1000){
        poopTimer %= properties->poopTimeSec*1000;
        numberOfPoops++;
        loseWeight(1);
    }

    ageTimer += delta;
    uint32_t day = 1000*60*60*24;
    if(ageTimer >= day){
        ageTimer %= day;
        age++;
    }

    evolutionTimer += delta;
    if(evolutionTimer >= properties->evolutionTimeSec*1000){
        evolutionTimer =0;
        evolved = true;
    }

}