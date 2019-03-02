#ifndef BASKETBALLINTAKE_H
#define BASKETBALLINTAKE_H

#include "../../StandardLibraries/Victor/Victor.h"

class BasketballIntake
{
public:
    BasketballIntake(PCA9685* PWM, int pivotPin, int intake1, int intake2);
    unsigned char updateBasketballIntake(unsigned char rotateUp, unsigned char rotateDown, unsigned char intakeIn, unsigned char intakeOut, unsigned char intakeHopper);
    void failsafe();
private:
    PCA9685* controller;

    Victor* armPivot;
    int _pivotPin;
    Victor* intakeMotor_1;
    int _intake1;
    Victor* intakeMotor_2;
    int _intake2;
};

#endif
