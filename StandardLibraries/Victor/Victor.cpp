#include "Victor.h"

#include "PCA9685.h"

Victor::Victor(PCA9685& output, int pin1) : device(output), pin(pin1){
    //PCA9685(int bus, int address)
    /* nothing */
}

void Victor::setThrottle(int value){
  device.setPWM(pin, value*(4095/255));
}

int Victor::getThrottle(){
  return device.getPWM(pin);
}
