#ifndef INTAKE_H
#define INTAKE_H

#include "../../StandardLibraries/Victor/Victor.h"

class Intake
{
public:
    Intake(PCA9685* PWM, int foamPin, int soccerPin);
    void runIntake(int foamTrigger, int soccerTrigger);
private:
    PCA9685* controller;
    int _foamPin, _soccerPin;

    Victor* foamIntake;
    Victor* soccerIntake;
};

#endif
