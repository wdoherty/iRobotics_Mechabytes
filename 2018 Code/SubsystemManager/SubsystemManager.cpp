#include "SubsystemManager.h"

SubsystemManager::SubsystemManager()
{
    //PCA9685(bus, address)
    PWM1 = new PCA9685(1, 0x40);
}

void SubsystemManager::initializeSubsystems()
{
	test = new TestSubSystem(*PWM1);
}

void SubsystemManager::runRobot()
{
	test->setMotorSpeed(255);
}
