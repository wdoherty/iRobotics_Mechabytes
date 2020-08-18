#ifndef BACKPACK_H
#define BACKPACK_H

#include "../../StandardLibraries/Victor/Victor.h"

class Backpack
{
public:
    Backpack(PCA9685* PWM, int frontIntakePin, int backIntakePin, int linkagePin);
    unsigned char* updateBackpack(unsigned char manualRotate, unsigned char intake, unsigned char outtake);
    void moveBackpack(unsigned char manualRotate);
    void failsafe();
private:
    PCA9685* controller;

    Victor* frontIntake;
    int _frontIntakePin;
    Victor* backIntake;
    int _backIntakePin;
    Victor* linkage;
    int _linkagePin;
    unsigned char BackpackVals[2];
};

#endif
