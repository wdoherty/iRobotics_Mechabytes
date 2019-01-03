#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "../wiringPiLib/wiringPi/wiringPi.h"

class Potentiometer
{
public:
    Potentiometer(int address);
    int readState();

private:
    int pin;
    int state = 0;
};

#endif
