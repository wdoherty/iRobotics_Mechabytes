#include "BasketballIntake.h"

BasketballIntake::BasketballIntake(PCA9685* PWM, int pivotPin, int intake1, int intake2) : controller(PWM)
{
  _pivotPin = pivotPin;
  _intake1 = intake1;
  _intake2 = intake2;
  armPivot = new SinglePiston(_pivotPin, 0);
  intakeMotor_1 = new Victor(controller, _intake1);
  intakeMotor_2 = new Victor(controller, _intake2);

  armToggle = 0;
  oldToggleState = armToggle;
}

unsigned char BasketballIntake::updateBasketballIntake(unsigned char rotate, unsigned char intakeIn, unsigned char intakeOut, unsigned char intakeHopper)
{
  unsigned char intakeState = 0;

  if(rotate > 0 && rotate != oldToggleState)
  {
    if(armToggle == 0) armToggle = 1;
    else armToggle = 0;

    armPivot->setState(armToggle);
  }
  oldToggleState = rotate;

  if(intakeIn > 0)
  {
    //run front rollers in and run back rollers out to keep balls in the chamber
    intakeMotor_1->setThrottle(2585);
    intakeMotor_2->setThrottle(1785);
    intakeState = 1;
  }
  else if(intakeHopper > 0)
  {
    //run front and back rollers in to drop balls into the hopper
    intakeMotor_1->setThrottle(2585);
    intakeMotor_2->setThrottle(2585);
    intakeState = 2;
  }
  else if(intakeOut > 0)
  {
    //run front and back rollers out to remove balls
    intakeMotor_1->setThrottle(1785);
    intakeMotor_2->setThrottle(1785);
    intakeState = 3;
  }
  else
  {
    //stop intake
    intakeMotor_1->setThrottle(2185);
    intakeMotor_2->setThrottle(2185);
    intakeState = 0;
  }
  return intakeState;
}

void BasketballIntake::failsafe()
{
  intakeMotor_1->setThrottle(2185); //stop soccer intake
  intakeMotor_2->setThrottle(2185); //stop soccer intake
}
