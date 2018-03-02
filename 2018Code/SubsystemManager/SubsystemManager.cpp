#include "SubsystemManager.h"

//class TestSubsytem();

SubsystemManager::SubsystemManager()
{
    //PCA9685(bus, address)
    PWM1 = new PCA9685(0x40);
}

void SubsystemManager::failsafe()
{

}

void SubsystemManager::initializeSubsystems()
{
	// test = new TestSubsystem(PWM1);

}

void SubsystemManager::runRobot(unsigned char controller[8])
{
	// int position;
	// while(true)
	// {
    // 	for(int i = 0; i < 400; i++)
    // 	{
    // 		position = 10 * i;
    // 		for(int j = 0; j < 100; j++)
    // 		{
    // 			test->setMotorSpeed(position);
    // 		}
    // 	}
	// }

    start = 1 & (controller[0] >> 6);

    driveThrottleRight = controller[7];
    driveThrottleLeft = controller[6];
    driveHeading = controller[4];

    SimonSaysArm = controller[2];
    SimonSays_UpperLeft = 1 & controller[1];
    SimonSays_UpperRight = 1 & (controller[1] >> 3);
    SimonSays_LowerLeft = 1 & (controller[1] >> 2);
    SimonSays_LowerRight = 1 & (controller[1] >> 1);

    FoamIntake = 1 & (controller[0] >> 5);
    SoccerIntake = 1 & (controller[0] >> 4);

    FoamArm = controller[3];
    RopeClamp = 1 & (controller[0] >> 2);
    Wheel = 1 & (controller[0] >> 3);
    FoamDoor = 1 & (controller[1] >> 6);

    FingerPosition = 1 & (controller[0] >> 1);
    SoccerDoor = 1 & (controller[0]);

}
