#ifndef VICTOR_H
#define VICTOR_H

#include "PCA9685.h"

class VICTOR_H
{
public:
  Victor(uint8_t addr, int PWMFreq, int bus, int pin);
  void setThrottle(int value);
private:
  PCA9685* i2c;
  uint8_t address;
};




#endif
