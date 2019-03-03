#ifndef BASKETBALLINTAKE_H
#define BASKETBALLINTAKE_H

#include "../../StandardLibraries/Victor/Victor.h"
#include "../../StandardLibraries/SinglePiston/SinglePiston.h"

class BasketballIntake
{
public:
    BasketballIntake(PCA9685* PWM, int pivotPin, int intake1, int intake2);
    unsigned char updateBasketballIntake(unsigned char rotate, unsigned char intakeIn, unsigned char intakeOut, unsigned char intakeHopper);
    void failsafe();
private:
    PCA9685* controller;

    SinglePiston* armPivot;
    int _pivotPin;
    Victor* intakeMotor_1;
    int _intake1;
    Victor* intakeMotor_2;
    int _intake2;

    unsigned char armToggle;
    unsigned char oldToggleState;
};

#endif
