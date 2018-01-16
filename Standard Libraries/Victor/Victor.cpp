#include "Victor.h"

#include "PCA9685.h"

Victor::Victor(PCA9685& output, int pin1){
    //PCA9685(int bus, int address)
  pin = pin1;
}

void Victor::setThrottle(int value){
  output.setPWM(value*(4095.0/360.0))
}

int Victor::getThrottle(){
  return output.getPWM(pin);
}
