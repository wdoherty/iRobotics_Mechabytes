#include "Victor.h"

#include "PCA9685.h"

Victor::Victor(uint8_t addr, int PWMFreq, int bus, int pin){
  i2c = new PCA9685(bus, pin);
  this->address = addr;
  i2c->setPWMFreq(PWMFreq);
}

void Victor::setThrottle(int value){
  i2c->setPWM(value*(4095.0/360.0))
}
