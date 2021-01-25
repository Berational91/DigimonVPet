/////////////////////////////////////////////////////////////////
/*
  Created by Berat Özdemir, January 24 , 2021.
*/
/////////////////////////////////////////////////////////////////

#include "../VPetLCD.h"

namespace V20 {



  class AgeWeightScreen : public VPetLCD::Screen {
  private:
    uint16_t age;
    uint16_t weight;

  public:
    AgeWeightScreen(uint16_t _age, uint16_t _weight) { age = _age;weight = _weight; };
    void draw(VPetLCD* lcd);
    void setAge(uint16_t _age) { age = _age; };
    void setWeight(uint16_t _weight) { weight = _weight; };

  };

}