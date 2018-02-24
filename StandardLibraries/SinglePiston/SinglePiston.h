#ifndef SINGLEPISTON_H
#define SINGLEPISTON_H

#include "../wiringPiLib/wiringPi/wiringPi.h"

class SinglePiston
{
    public:
        SinglePiston(int address);
        SinglePiston(int address, int initState);
        int switchState();
        int setState(int newState);

    private:
        void setPiston();
        int pin;
        int state;
};

#endif
