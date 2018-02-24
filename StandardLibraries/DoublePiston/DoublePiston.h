#ifndef DOUBLEPISTON_H
#define DOUBLEPISTON_H

#include "../wiringPiLib/wiringPi/wiringPi.h"

class DoublePiston
{
public:
  DoublePiston(int address1, int address2);
  DoublePiston(int address1, int address2, int initState);
  int switchState();
  int setState(int newState);

private:
  void setPistons();
  int pin1, pin2;
  int state;
};

#endif
