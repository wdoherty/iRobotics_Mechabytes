#ifndef DIGITALSENSOR_H
#define DIGITALSENSOR_H

#include "../wiringPiLib/wiringPi/wiringPi.h"
// #include <pigpio.h>

class DigitalSensor
{
    public:
        DigitalSensor(int address);
        int readState();

    private:
        int pin;
};

#endif
