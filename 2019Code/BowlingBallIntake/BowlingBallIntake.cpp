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

unsigned char BowlingBallIntake::updateBowlingBallIntake(unsigned char intakeIn, unsigned char intakeOut, unsigned char manualRotate,
  unsigned char liftUp, unsigned char liftDown)
  {
    unsigned char intakeState = 0;
    //handles intake state
    if(intakeIn > 0)
    {
      intakeRoller->setThrottle(2585);
      intakeState = 1;
    }
    else if(intakeOut > 0)
    {
      intakeRoller->setThrottle(1785);
      intakeState = 2;
    }
    else
    {
      intakeRoller->setThrottle(2185);
      intakeState = 0;
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
    return intakeState;
  }

void BowlingBallIntake::moveIntake(unsigned char manualRotate)
{
  int rotateMag = manualRotate;
  rotateMag *= 1650;
  rotateMag /= 200;

  if(rotateMag > 743 && rotateMag < 907) rotateMag = 825;

  double rotateThrottle = abs(rotateMag - 825) * (rotateMag < 825 ? -1 : 1);

  rotateThrottle += 1360;

  intakePivot->setThrottle(rotateThrottle);
}

void BowlingBallIntake::failsafe()
{
  intakePivot->setThrottle(2185);
  intakeRoller->setThrottle(2185);
  ballLift->setThrottle(2185);
}
