#ifndef SUBSYSTEMMANAGER_H
#define SUBSYSTEMMANAGER_H

#include "../../StandardLibraries/Victor/Victor.h"
#include "../../StandardLibraries/PCA9685/PCA9685.h"
#include "../../StandardLibraries/Controller/Controller.h"
#include "../Backpack/Backpack.h"
#include "../BasketballIntake/BasketballIntake.h"
#include "../BasketballShooter/BasketballShooter.h"
#include "../BowlingBallIntake/BowlingBallIntake.h"
#include "../SimonSays/SimonSays.h"
#include "../TankDrive/TankDrive.h"

class SubsystemManager
{
public:
    SubsystemManager();
    void initializeSubsystems();
    void failsafe();
    unsigned char* runRobot(unsigned char controllerIn[8]);
private:
    PCA9685* PWM1;
    //insert subsystems here
    SimonSays* simonSays;
    Backpack* backpack;
    TankDrive* driveTrain;
    // BasketballIntake* basketball_intake;
    // BasketballShooter* basketball_shooter;
    BowlingBallIntake* bowlingBall;

    Controller* controller;
    unsigned char* controllerArray;

    unsigned char returnValues[10];
    unsigned char* driveVals;

    unsigned char driveThrottleRight;
    unsigned char driveThrottleLeft;
    unsigned char driveHeading;

    unsigned char SimonSays_UpperLeft;
    unsigned char SimonSays_UpperRight;
    unsigned char SimonSays_LowerLeft;
    unsigned char SimonSays_LowerRight;

    unsigned char backpack_intake;
    unsigned char backpack_outtake;
    unsigned char backpack_presetUp;
    unsigned char backpack_presetLevel;
    unsigned char backpack_presetDown;
    unsigned char backpack_manual;

    unsigned char bowlingball_intake;
    unsigned char bowlingball_outtake;
    unsigned char bowlingball_liftUp;
    unsigned char bowlingball_liftDown;
    unsigned char bowlingball_presetOut;
    unsigned char bowlingball_presetIn;
    unsigned char bowlingball_manual;
    unsigned char bowlingball_tapUp;


};

#endif
