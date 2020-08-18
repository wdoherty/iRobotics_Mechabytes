#include "SubsystemManager.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
// using namespace std;
// intitalizes the subsystem manager and all global objects
SubsystemManager::SubsystemManager()
{
// declares new instance of PWM driver at default I2C address
    PWM1 = new PCA9685(0x40);
    int i = 0;
    for(; i < 8; i++)
    {
      controllerArray[i] = 0;
    }
    controller = new Controller(controllerArray);
    mode = 0;
    prev_modeUp = 0;
    prev_modeDown = 0;
}

// calls all subsystem failsafes
void SubsystemManager::failsafe()
{
    simonSays->failsafe();
    bowlingBall->failsafe();
    driveTrain->failsafe();
    backpack->failsafe();
    basketball_shooter->failsafe();
}

// creates a new instance of each robot subsystem
// passes a pointer to the PWM driver, motor PWM pins, and solenoid GPIO pins

void SubsystemManager::initializeSubsystems()
{
    driveTrain = new TankDrive(PWM1, 12, 1, 2, 3, 4, 5); //left drive 0, 1, 2; right drive 3, 4, 5
    backpack = new Backpack(PWM1, 6, 7, 8); //frontIntake pin 6, rearIntake pin 7, linkage pin 8
    bowlingBall = new BowlingBallIntake(PWM1, 9, 10, 11); //pivot pin 9, intake pin 10, lift pin 11
    simonSays = new SimonSays(17, 27, 22, 18); //GPIO 17, 27, 22, 23 for pistons (Pi 11, 13, 15, 16)
    basketball_shooter = new BasketballShooter(PWM1,23,13,0,14,15); //no stopper, no shooter, turret pin 0, no staging1, no staging2
}

// looping function
// distributes controller inputs to subsystems for handling
// returns an array of values sent back to driver station with state data
unsigned char* SubsystemManager::runRobot(unsigned char controllerIn[8])
{
    //NOTE: For the motor speeds, full reverse is a value of 1360, neutral is between 2160 and 2210, and full forward is 3010
    //These values are from testing on a talon that wasn't accepting a new calibration with output 0-4095
     // controllerArray = controllerIn;
     int i = 0;
     for(; i < 8; i++)
     {
       controllerArray[i] = controllerIn[i];
     }

     intakeVals = 0;

     memset(returnValues,0,sizeof(returnValues));
     // cout << "Reading controller" << endl;
     // assigns values of XBox controller to specific functions
      driveThrottleRight = controller->RTrigger();
      driveThrottleLeft = controller->LTrigger();
      driveHeading = controller->LeftStickX();

      SimonSays_UpperLeft = controller->Y();
      SimonSays_UpperRight = controller->B();
      SimonSays_LowerLeft = controller->X();
      SimonSays_LowerRight = controller->A();

      backpack_intake = controller->LB();
      backpack_outtake = controller->RB();
      backpack_presetUp = controller->Y();
      backpack_presetLevel = controller->X();
      backpack_presetDown = controller->A();
      backpack_manual = controller->RightStickY();

      // turretLeft = controller->X();
      // turretRight = controller->Y();

      bowlingball_intake = controller->RB();
      bowlingball_outtake = controller->LB();
      bowlingball_liftUp = controller->Y();
      bowlingball_liftDown = controller->X();
      bowlingball_presetOut = controller->B();
      bowlingball_presetIn = controller->A();
      bowlingball_manual = controller->RightStickY();
      bowlingball_tapUp = controller->select();

      modeUp = controller->DPadRight();
      modeDown = controller->DPadLeft();
      // cout << "Read controller" << endl;
      setMode();

      driveVals = driveTrain->updateDrive(driveThrottleRight, driveThrottleLeft, driveHeading);


      if(mode == 0)
      {
        basketball_shooter->updateBasketballShooter(turretLeft, turretRight);
        bowlingVals = bowlingBall->updateBowlingBallIntake(0, 0, 0, 0, 0);
        // intakeVals += bowlingVals[0];
        intakeVals += 0;
        intakeVals += simonSays->updateSimonSays(SimonSays_UpperLeft, SimonSays_UpperRight, SimonSays_LowerLeft, SimonSays_LowerRight);
        backpackVals = backpack->updateBackpack(100, 0, 0);
        intakeVals += backpackVals[0];
      }
      else if(mode == 1)
      {
        basketball_shooter->updateBasketballShooter(0, 0);
        bowlingVals = bowlingBall->updateBowlingBallIntake(0, 0, 0, 0, 0);
        // intakeVals += bowlingVals[0];
        intakeVals += 0;
        intakeVals += simonSays->updateSimonSays(0, 0, 0, 0);
        backpackVals = backpack->updateBackpack(backpack_manual, backpack_intake, backpack_outtake);
        intakeVals += backpackVals[0];
      }
      else
      {
        basketball_shooter->updateBasketballShooter(0, 0);
        bowlingVals = bowlingBall->updateBowlingBallIntake(bowlingball_intake, bowlingball_outtake, bowlingball_manual, bowlingball_liftUp, bowlingball_liftDown);
        // intakeVals += bowlingVals[0];
        intakeVals += 0;
        intakeVals += simonSays->updateSimonSays(0, 0, 0, 0);
        backpackVals = backpack->updateBackpack(100, 0, 0);
        intakeVals += backpackVals[0];
      }

     //sends feedback to DS

     returnValues[0] = driveVals[0];
     returnValues[1] = driveVals[1];
     returnValues[2] = mode;
     returnValues[3] = intakeVals;
     returnValues[4] = backpackVals[1];
     returnValues[5] = bowlingVals[1];

     return returnValues;
}

void SubsystemManager::setMode()
{
  if(modeUp > 0 && modeUp != prev_modeUp)
  {
    mode++;
    mode %= 3;
  }
  else if(modeDown > 0 && modeDown != prev_modeDown)
  {
    if(mode == 0) mode = 2;
    else mode--;
  }
  prev_modeUp = modeUp;
  prev_modeDown = modeDown;
}
