#ifndef ANALOGSENSOR_H
#define ANALOGSENSOR_H

#include "../wiringPiLib/wiringPi/ads1115.h"

void init(int ADSBase, int pin);
int read();

int _pin;
int _ADSBase;

#endif
