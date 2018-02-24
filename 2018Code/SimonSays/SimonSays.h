#ifndef SIMONSAYS_H
#define SIMONSAYS_H

#include "../../StandardLibraries/Victor/Victor.h"

class SimonSays
{
public:
    SimonSays(PCA9685* PWM, int pivotPin);
    void updateSimonSays(int runUp, int runDown);
private:
    PCA9685* controller;
    int _pivotPin;
    Victor* pivot;

};

#endif
