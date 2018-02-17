#include "TestSubsystem.h"

TestSubsystem::TestSubsystem(){

}

TestSubsystem::TestSubsystem(PCA9685* output): device(output){
    throttle = new Victor(device, 0);
}

void TestSubsystem::setMotorSpeed(int speed)
{
	throttle->setThrottle(speed);
}
