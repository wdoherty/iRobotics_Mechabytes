#ifndef SUBSYSTEMMANAGER_H
#define SUBSYSTEMMANAGER_H

#include "../../StandardLibraries/Victor/Victor.h"
#include "../../StandardLibraries/PCA9685/PCA9685.h"
#include "../TestSubsystem/TestSubsystem.h"
#include "../SimonSays/SimonSays.h"
#include "../Intake/Intake.h"
#include "../TankDrive/TankDrive.h"
#include "../Arm/Arm.h"
#include "../SoccerOutput/SoccerOutput.h"

class SubsystemManager
{
public:
    SubsystemManager();
    void initializeSubsystems();
    void failsafe();
    void runRobot(unsigned char controller[8]);
private:
    PCA9685* PWM1;
    //insert subsystems here
    // TestSubsystem* test;
    SimonSays* simonSays;
    Intake* intake;
    TankDrive* driveTrain;
    Arm* foamArm;
    SoccerOutput* soccer;


    unsigned char driveThrottleRight;
    unsigned char driveThrottleLeft;
    unsigned char driveHeading;

    unsigned char SimonSaysArm;
    unsigned char SimonSays_UpperLeft;
    unsigned char SimonSays_UpperRight;
    unsigned char SimonSays_LowerLeft;
    unsigned char SimonSays_LowerRight;

    unsigned char FoamIntake;
    unsigned char SoccerIntake;

    unsigned char FoamArm;
    unsigned char RopeClamp;
    unsigned char Wheel;
    unsigned char FoamDoor;

    unsigned char FingerPosition;
    unsigned char SoccerDoor;

    unsigned char start;
};

#endif
