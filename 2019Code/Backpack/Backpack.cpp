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

unsigned char Backpack::updateBackpack(unsigned char manualRotate, unsigned char intake, unsigned char outtake)
{
  unsigned char retval;
  moveBackpack(manualRotate);

  if(intake > 0)
  {
    frontIntake->setThrottle(2585);
    backIntake->setThrottle(1785);
    retval = 32;
  }
  else if(outtake > 0)
  {
    frontIntake->setThrottle(1785);
    backIntake->setThrottle(2585);
    retval = 16;
  }
  else
  {
    frontIntake->setThrottle(2185);
    backIntake->setThrottle(2185);
    retval = 0;
  }
  return retval;
}

void Backpack::moveBackpack(unsigned char manualRotate)
{
  int rotateMag = manualRotate;
  rotateMag *= 1650;
  rotateMag /= 200;

  if(rotateMag > 743 && rotateMag < 907) rotateMag = 825;

  double rotateThrottle = abs(rotateMag - 825) * (rotateMag < 825 ? -1 : 1);

  rotateThrottle += 1360;

  linkage->setThrottle(rotateThrottle);
}

void Backpack::failsafe()
{
  frontIntake->setThrottle(2185);
  backIntake->setThrottle(2185);
  linkage->setThrottle(2185);
}
