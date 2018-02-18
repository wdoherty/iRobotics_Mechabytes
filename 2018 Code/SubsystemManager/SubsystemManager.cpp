#include "SubsystemManager.h"

//class TestSubsytem();

SubsystemManager::SubsystemManager()
{
    //PCA9685(bus, address)
    PWM1 = new PCA9685(0x40);
}

void SubsystemManager::initializeSubsystems()
{
	test = new TestSubsystem(PWM1);
//	TestSubsystem foo(PWM1);
}

void SubsystemManager::runRobot()
{
	test->setMotorSpeed(255);
}
