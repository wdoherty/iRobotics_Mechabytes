#ifndef VICTOR_H
#define VICTOR_H

#include "../PCA9685/PCA9685.h"

class Victor
{
public:
  Victor(PCA9685* output, int pin1);
  void setThrottle(int value);
  int getThrottle();
private:
  PCA9685* device;
  int pin;
};




#endif
