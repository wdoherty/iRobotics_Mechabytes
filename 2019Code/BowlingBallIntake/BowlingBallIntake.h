#ifndef BOWLINGBALLINTAKE_H
#define BOWLINGBALLINTAKE_H

#include "../../StandardLibraries/Victor/Victor.h"

class BowlingBallIntake
{
public:
    BowlingBallIntake(PCA9685* PWM, int pivotPin, int intakePin, int liftPin);
    unsigned char* updateBowlingBallIntake(unsigned char intakeIn, unsigned char intakeOut, unsigned char manualRotate, unsigned char liftUp, unsigned char liftDown);
    void moveIntake(unsigned char manualRotate);
    void failsafe();
private:
    PCA9685* controller;

    Victor* intakePivot;
    int _pivotPin;
    Victor* intakeRoller;
    int _intakePin;
    Victor* ballLift;
    int _liftPin;
    unsigned char bowlingVals[2];
};

#endif
