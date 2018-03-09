#ifndef INTAKE_H
#define INTAKE_H

#include "../../StandardLibraries/Victor/Victor.h"
#include "../../StandardLibraries/SinglePiston/SinglePiston.h"

class Intake
{
public:
    Intake(PCA9685* PWM, int foamPin, int soccerPin, int hoodPin);
    void failsafe();
    unsigned char updateIntake(unsigned char foamTrigger, unsigned char soccerTrigger, unsigned char doorReset);
private:
    PCA9685* controller;
    int _foamPin, _soccerPin, _hoodPin;
    unsigned char value;
    bool hoodHold;

    Victor* foamIntake;
    Victor* soccerIntake;
    SinglePiston* hood;
};

#endif
