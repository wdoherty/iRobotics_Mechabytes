#ifndef ARM_H
#define ARM_H

#include "../../StandardLibraries/Victor/Victor.h"

class Arm
{
public:
    Arm(PCA9685* PWM, int armPin);
    void updateArm(int armUp, int armDown);

private:
    PCA9685* controller;
    int _armPin;
    Victor* armPivot;

};

#endif
