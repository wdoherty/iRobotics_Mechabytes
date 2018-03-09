#ifndef INTAKE_H
#define INTAKE_H

#include "../../StandardLibraries/Victor/Victor.h"

class Intake
{
public:
    Intake(PCA9685* PWM, int foamPin, int soccerPin);
    void failsafe();
    unsigned char updateIntake(unsigned char foamTrigger, unsigned char soccerTrigger);
private:
    PCA9685* controller;
    int _foamPin, _soccerPin;
    unsigned char value;

    Victor* foamIntake;
    Victor* soccerIntake;
};

#endif
