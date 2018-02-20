#ifndef TEST_SUBSYSTEM_H
#define TEST_SUBSYSTEM_H

#include "../../StandardLibraries/Victor/Victor.h"
#include "../../StandardLibraries/PCA9685/PCA9685.h"

class TestSubsystem
{
public:
	TestSubsystem();
    TestSubsystem(PCA9685* output);
    void setMotorSpeed(int speed);
private:
    PCA9685* device;
    Victor* throttle;
};

#endif
