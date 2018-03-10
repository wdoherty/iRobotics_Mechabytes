#include "SubsystemManager.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

SubsystemManager::SubsystemManager()
{
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
	 /*
    simonSays = new SimonSays(PWM1, 6, 7, 11, 13, 15); //Arm pin 6, GPIO 4,21,17,20,27,16,22,12 for pistons (Pi 7,40,11,38,13,36,15,32)
    intake = new Intake(PWM1, 4, 5, 33); //Foam intake pin 4, soccer intake pin 5, digital pin GPIO 13 (Pi 33)
    driveTrain = new TankDrive(PWM1, 0, 1, 2, 3); //Left drive on pins 0 & 1, Right drive on pins 2 & 3
    foamArm = new Arm(PWM1, 7, 8, 24, 21); //foam arm on pwm 7, wheel on pwm 8, clamp piston GPIO 8, door GPIO 9 (Pi 24,21)
    soccer = new SoccerOutput(23, 29); //Soccer finger GPIO 11, Soccer door GPIO 5 (Pi 23,29)
     */
    // /*
    simonSays = new SimonSays(PWM1, 6, 17, 27, 22, 23); //Arm pin 6, GPIO 17, 27, 22, 23 for pistons (Pi 11, 13, 15, 16)
    intake = new Intake(PWM1, 4, 5, 26); //Foam intake pin 4, soccer intake pin 5, digital pin GPIO 26 (Pi 37)
    driveTrain = new TankDrive(PWM1, 0, 1, 2, 3); //Left drive on pins 0 & 1, Right drive on pins 2 & 3
    foamArm = new Arm(PWM1, 7, 8, 24, 21); //foam arm on pwm 7, wheel on pwm 8, clamp piston GPIO 24, door GPIO 5 (Pi 18,29)
    soccer = new SoccerOutput(6, 13); //Soccer finger GPIO 6, Soccer door GPIO 13 (Pi 31,33)
    // */
    
    //test = new TestSubsystem(PWM1);
}

unsigned char* SubsystemManager::runRobot(unsigned char controller[8])
{
    //NOTE: For the motor speeds, full reverse is a value of 1360, neutral is between 2160 and 2210, and full forward is 3010
    //These values are from testing on a talon that wasn't accepting a new calibration with output 0-4095
     memset(returnValues,0,sizeof(returnValues));

     start = 1 & (controller[0] >> 6);

     driveThrottleRight = controller[7];
     driveThrottleLeft = controller[6];
     driveHeading = controller[4];

     SimonSaysArm = controller[2];
     SimonSays_UpperLeft = 1 & controller[1];
     SimonSays_UpperRight = 1 & (controller[1] >> 3);
     SimonSays_LowerLeft = 1 & (controller[1] >> 2);
     SimonSays_LowerRight = 1 & (controller[1] >> 1);

     doorReset = 1 & (controller[1] >> 5);

     FoamIntake = 1 & (controller[0] >> 5);
     SoccerIntake = 1 & (controller[0] >> 4);

     FoamArm = controller[3];
     RopeClamp = 1 & (controller[0] >> 2);
     Wheel = 1 & (controller[0] >> 3);
     FoamDoor = 1 & (controller[1] >> 6);

     FingerPosition = 1 & (controller[0] >> 1);
     SoccerDoor = 1 & (controller[0]);

     returnValues[3] += simonSays->updateSimonSays(SimonSaysArm, SimonSays_UpperLeft, SimonSays_UpperRight,
                                SimonSays_LowerLeft, SimonSays_LowerRight);
     returnValues[2] += intake->updateIntake(FoamIntake, SoccerIntake, doorReset);
     driveVals = driveTrain->updateDrive(driveThrottleRight, driveThrottleLeft, driveHeading);
     returnValues[0] = driveVals[0];
     returnValues[1] = driveVals[1];
     returnValues[2] += foamArm->updateArm(FoamArm, RopeClamp, FoamDoor, Wheel);
     returnValues[2] += soccer->updateSoccerOutput(FingerPosition, SoccerDoor);

     return returnValues;
}
