#include "TestSubsystem.h"
#include <iostream>

TestSubsystem::TestSubsystem(){

}

TestSubsystem::TestSubsystem(PCA9685* output): device(output){
    throttle = new Victor(device, 1);
}

void TestSubsystem::setMotorSpeed(int speed)
{
	throttle->setThrottle(speed);
	std::cout << throttle->getThrottle() << std::endl;
}
