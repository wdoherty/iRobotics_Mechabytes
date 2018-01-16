#ifndef SUBSYSTEMMANAGER_H
#define SUBSYSTEMMANAGER_H

#include "../../StandardLibraries/Victor/Victor.h"

class SubsystemManager
{
public:
    SubsystemManager();
    void initializeSubsystems();
private:
    PCA9685 PWM1;
    //insert subsystems here

};

#endif
