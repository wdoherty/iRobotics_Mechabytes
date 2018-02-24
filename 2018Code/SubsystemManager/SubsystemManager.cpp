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
	int position;
	while(true)
	{
    	for(int i = 0; i < 400; i++)
    	{
    		position = 10 * i;
    		for(int j = 0; j < 100; j++)
    		{
    			test->setMotorSpeed(position);
    		}
    	}
	}
}
