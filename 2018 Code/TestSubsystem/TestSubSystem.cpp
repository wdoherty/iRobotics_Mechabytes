#include "TestSubSystem.h"

TestSubSystem::TestSubSystem(PCA9685& output): device(output){
    throttle(device, 0);
}

void TestSubSystem::setMotorSpeed(int speed)
{
	throttle.setThrottle(speed);
}
