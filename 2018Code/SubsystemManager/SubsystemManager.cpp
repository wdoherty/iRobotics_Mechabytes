#include "SubsystemManager.h"

//class TestSubsytem();

SubsystemManager::SubsystemManager()
{
    //PCA9685(bus, address)
    PWM1 = new PCA9685(0x40);
}

void SubsystemManager::failsafe()
{
    simonSays->failsafe();
    intake->failsafe();
    driveTrain->failsafe();
    foamArm->failsafe();
}

void SubsystemManager::initializeSubsystems()
{
    simonSays = new SimonSays(PWM1, 6, 0, 1, 2, 3, 4, 5, 6, 7); //Arm pin 6, GPIO 0,1,2,3,4,5,6,7 for pistons
    intake = new Intake(PWM1, 4, 5); //Foam intake pin 4, soccer intake pin 5
    driveTrain = new TankDrive(PWM1, 0, 1, 2, 3); //Left drive on pins 0 & 1, Right drive on pins 2 & 3
    foamArm = new Arm(PWM1, 7, 8, 8, 9, 10, 11); //foam arm on pwm 7, wheel on pwm 8, clamp piston GPIO 8/9, door GPIO 10/11
    soccer = new SoccerOutput(12, 13);
}

void SubsystemManager::runRobot(unsigned char controller[8])
{
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

    simonSays->updateSimonSays(SimonSaysArm, SimonSays_UpperLeft, SimonSays_UpperRight,
                               SimonSays_LowerLeft, SimonSays_LowerRight);
    intake->updateIntake(FoamIntake, SoccerIntake);
    driveTrain->updateDrive(driveThrottleRight, driveThrottleLeft, driveHeading);
    foamArm->updateArm(FoamArm, RopeClamp, FoamDoor, Wheel);
    soccer->updateSoccerOutput(FingerPosition, SoccerDoor);
}
