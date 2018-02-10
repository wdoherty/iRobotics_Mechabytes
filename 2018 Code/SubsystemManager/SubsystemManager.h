#ifndef SUBSYSTEMMANAGER_H
#define SUBSYSTEMMANAGER_H

#include "../../StandardLibraries/Victor/Victor.h"
#include "../../StandardLibraries/PCA9685/PCA9685.h"
#include "../TestSubsystem/TestSubSystem.h"

class SubsystemManager
{
public:
    SubsystemManager();
    void initializeSubsystems();
    void runRobot();
private:
    PCA9685* PWM1;
    //insert subsystems here
    TestSubSystem* test;

};

#endif
