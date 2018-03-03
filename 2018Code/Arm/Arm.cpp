#include "Arm.h"

// Arm::Arm(PCA9685* PWM, int armPin, int wheelPin, int clampPiston1, int clampPiston2, int doorPiston1, int doorPiston2) : controller(PWM)
// {
//     _armPin = armPin;
//     _wheelPin = wheelPin;
//     armPivot = new Victor(controller, _armPin);
//     ropeWheel = new Victor(controller, _wheelPin);
//     _clampPiston1 = clampPiston1;
//     _clampPiston2 = clampPiston2;
//     _doorPiston1 = doorPiston1;
//     _doorPiston2 = doorPiston2;
//     clampPiston = new DoublePiston(_clampPiston1, _clampPiston2, false);
//     doorPiston = new DoublePiston(_doorPiston1, _doorPiston2, false);
// } Double Solenoid

Arm::Arm(PCA9685* PWM, int armPin, int wheelPin, int clampPin, int doorPin) : controller(PWM)
{
    _armPin = armPin;
    _wheelPin = wheelPin;
    armPivot = new Victor(controller, _armPin);
    ropeWheel = new Victor(controller, _wheelPin);
    _clampPin = clampPin;
    _doorPin = doorPin;
    clampPiston = new SinglePiston(_clampPin);
    doorPiston = new SinglePiston(_doorPin);
}

void Arm::failsafe()
{
    armPivot->setThrottle(2048);
    ropeWheel->setThrottle(2048);
}

void Arm::updateArm(unsigned char ArmSpeed, unsigned char clampPos, unsigned char foamDoor, unsigned char wheel)
{
    _armSpeed = (int)(ArmSpeed);
    _armSpeed *= 4095;
    _armSpeed /= 200;

    if(_armSpeed > 1023 && _armSpeed < 3072) _armSpeed = 2048;
    armPivot->setThrottle(_armSpeed);

    _clampPos = (int) clampPos;
    _foamDoor = (int) foamDoor;
    _wheel = (int) wheel;

    if(_wheel == 1) ropeWheel->setThrottle(4095);
    else ropeWheel->setThrottle(2048);

    clampPiston->setState(_clampPos);
    doorPiston->setState(_foamDoor);
}
