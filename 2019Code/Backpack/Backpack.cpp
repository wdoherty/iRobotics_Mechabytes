#include "Backpack.h"
#include <math.h>
#include <stdlib.h>

Backpack::Backpack(PCA9685* PWM, int frontIntakePin, int backIntakePin, int linkagePin) : controller(PWM)
{
  _frontIntakePin = frontIntakePin;
  _backIntakePin = backIntakePin;
  _linkagePin = linkagePin;
  frontIntake = new Victor(controller, _frontIntakePin);
  backIntake = new Victor(controller, _backIntakePin);
  linkage = new Victor(controller, _linkagePin);
}

unsigned char* Backpack::updateBackpack(unsigned char manualRotate, unsigned char intake, unsigned char outtake)
{
  moveBackpack(manualRotate);

  if(intake > 0)
  {
    frontIntake->setThrottle(2585);
    backIntake->setThrottle(1785);
    BackpackVals[0] = 32;
  }
  else if(outtake > 0)
  {
    frontIntake->setThrottle(1785);
    backIntake->setThrottle(2585);
    BackpackVals[0] = 16;
  }
  else
  {
    frontIntake->setThrottle(2185);
    backIntake->setThrottle(2185);
    BackpackVals[0] = 0;
  }
  return BackpackVals;
}

void Backpack::moveBackpack(unsigned char manualRotate)
{
  int rotateMag = (int)manualRotate;
  rotateMag *= 1650;
  rotateMag /= 200;

  if(rotateMag > 619 && rotateMag < 1031) rotateMag = 820;
  BackpackVals[1] = rotateMag/16;
  if(BackpackVals[1] > 100) BackpackVals[1] = 100;

  rotateMag += 1360;

  linkage->setThrottle(rotateMag);
}

void Backpack::failsafe()
{
  frontIntake->setThrottle(2185);
  backIntake->setThrottle(2185);
  linkage->setThrottle(2185);
}
