#ifndef VICTOR_H
#define VICTOR_H

#include "PCA9685.h"

class VICTOR_H
{
public:
  Victor(PCA9685& output, int pin1);
  void setThrottle(int value);
  int getThrottle();
private:
  int pin;
};




#endif
