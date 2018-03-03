#ifndef ARM_H
#define ARM_H

#include "../../StandardLibraries/Victor/Victor.h"
// #include "../../StandardLibraries/DoublePiston/DoublePiston.h"
#include "../../StandardLibraries/SinglePiston/SinglePiston.h"

class Arm
{
public:
    // Arm(PCA9685* PWM, int armPin, int wheelPin, int clampPiston1, int clampPiston2, int doorPiston1, int doorPiston2); //for double solenoid
    Arm(PCA9685* PWM, int armPin, int wheelPin, int clampPin, int doorPin); //for single solenoid
    void updateArm(unsigned char ArmSpeed, unsigned char clampPos, unsigned char foamDoor, unsigned char wheel);
    void failsafe();

private:
    PCA9685* controller;
    int _armPin, _wheelPin;
    // int _clampPiston1, _clampPiston2, _doorPiston1, _doorPiston2;
    int _clampPin, _doorPin;
    int _clampPos, _foamDoor, _wheel;
    int _armSpeed;
    Victor* armPivot, *ropeWheel;
    // DoublePiston* clampPiston, *doorPiston;
    SinglePiston* clampPiston, *doorPiston;
};

#endif
