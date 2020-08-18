#include "BowlingBallIntake.h"
#include <math.h>
#include <stdlib.h>

BowlingBallIntake::BowlingBallIntake(PCA9685* PWM, int pivotPin, int intakePin, int liftPin) : controller(PWM)
{
  _pivotPin = pivotPin;
  _intakePin = intakePin;
  _liftPin = liftPin;
  intakePivot = new Victor(controller, _pivotPin);
  intakeRoller = new Victor(controller, _intakePin);
  ballLift = new Victor(controller, _liftPin);
}

unsigned char* BowlingBallIntake::updateBowlingBallIntake(unsigned char intakeIn, unsigned char intakeOut, unsigned char manualRotate,
  unsigned char liftUp, unsigned char liftDown)
  {
    //handles intake state
    if(intakeIn > 0)
    {
      intakeRoller->setThrottle(2485);
      bowlingVals[0] = 128;
    }
    else if(intakeOut > 0)
    {
      intakeRoller->setThrottle(1885);
      bowlingVals[0] = 64;
    }
    else
    {
      intakeRoller->setThrottle(2185);
      bowlingVals[0] = 0;
    }

    //handles manual rotation of intake roller position
    moveIntake(manualRotate);

    //handles elevation of the ball lift
    if(liftUp > 0)
    {
      ballLift->setThrottle(2585);
    }
    else if(liftDown > 0)
    {
      ballLift->setThrottle(1785);
    }
    else
    {
      ballLift->setThrottle(2185);
    }
    return bowlingVals;
  }

void BowlingBallIntake::moveIntake(unsigned char manualRotate)
{
  int rotateMag = (int)manualRotate;
  rotateMag *= 1650;
  rotateMag /= 200;

  if(rotateMag > 743 && rotateMag < 907) rotateMag = 825;
  bowlingVals[1] = rotateMag/16;
  if(bowlingVals[1] > 100) bowlingVals[1] = 100;

  rotateMag += 1360;

  intakePivot->setThrottle(rotateMag);
}

void BowlingBallIntake::failsafe()
{
  intakePivot->setThrottle(2185);
  intakeRoller->setThrottle(2185);
  ballLift->setThrottle(2185);
}
