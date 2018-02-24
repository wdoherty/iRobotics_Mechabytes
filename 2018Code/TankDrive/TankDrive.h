#ifndef TANKDRIVE_H
#define TANKDRIVE_H

#include "../../StandardLibraries/Victor/Victor.h"

class TankDrive
{
public:
    TankDrive(PCA9685* PWM, int leftPin1, int leftPin2, int rightPin1, int rightPin2);
    void updateDrive(byte lStickY, byte rStickX);

private:
    void setThrottle();

    PCA9685* controller;

    Victor* left1;
    int _leftPin1;
    Victor* left2;
    int _leftPin2;
    Victor* right1;
    int _rightPin1;
    Victor* right2;
    int _rightPin2


    int lSpeed;
    int rSpeed;
    byte _lStickY;
    byte _rStickX;

};



#endif
