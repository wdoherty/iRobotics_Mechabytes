#ifndef BASKETBALLSHOOTER_H
#define BASKETBALLSHOOTER_H

#include "../../StandardLibraries/Victor/Victor.h"
#include "../../StandardLibraries/SinglePiston/SinglePiston.h"

class BasketballShooter
{
public:
    BasketballShooter(PCA9685* PWM, int stopperPin, int shooterPin, int turretPin, int stagingPin1, int stagingPin2);
    unsigned char updateBasketballShooter(unsigned char stage, unsigned char feed, unsigned char runShooter, int turretOfffset);
    unsigned char updateBasketballShooter(unsigned char turretL, unsigned char turretR);
    void failsafe();
private:
    PCA9685* controller;

    unsigned char shooterToggle;
    unsigned char prevShooterState;

    SinglePiston* stopper;
    int _stopperPin;
    Victor* shooter;
    int _shooterPin;
    Victor* turret;
    int _turretPin;
    Victor* staging1;
    int _stagingPin1;
    Victor* staging2;
    int _stagingPin2;
};

#endif
