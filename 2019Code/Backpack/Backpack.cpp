#include "Backpack.h"

Backpack::Backpack(PCA9685* PWM, int frontIntakePin, int backIntakePin, int linkagePin) : controller(PWM)
{
  _frontIntakePin = frontIntakePin;
  _backIntakePin = backIntakePin;
  _linkagePin = linkagePin;
  frontIntake = new Victor(controller, _frontIntakePin);
  backIntake = new Victor(controller, _backIntakePin);
  linkage = new Victor(controller, _linkagePin);
}

unsigned char Backpack::updateBackpack(unsigned char rotateUp, unsigned char rotateDown, unsigned char intake, unsigned char outtake)
{
  if(rotateUp > 0)
  {
    linkage->setThrottle(2585);
  }
  else if(rotateDown > 0)
  {
    linkage->setThrottle(1785);
  }
  else
  {
    linkage->setThrottle(2185);
  }

  if(intake > 0)
  {
    frontIntake->setThrottle(2585);
    backIntake->setThrottle(1785);
  }
  else if(outtake > 0)
  {
    frontIntake->setThrottle(1785);
    backIntake->setThrottle(2585);
  }
  else
  {
    frontIntake->setThrottle(2185);
    backIntake->setThrottle(2185);
  }
  return 1;
}

void Backpack::failsafe()
{
  frontIntake->setThrottle(2185);
  backIntake->setThrottle(2185);
  linkage->setThrottle(2185);
}
