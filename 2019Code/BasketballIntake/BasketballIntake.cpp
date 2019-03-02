#include "BasketballIntake.h"

BasketballIntake::BasketballIntake(PCA9685* PWM, int pivotPin, int intake1, int intake2) : controller(PWM)
{
  _pivotPin = pivotPin;
  _intake1 = intake1;
  _intake2 = intake2;
  armPivot = new Victor(controller, _pivotPin);
  intakeMotor_1 = new Victor(controller, _intake1);
  intakeMotor_2 = new Victor(controller, _intake2);
}

unsigned char BasketballIntake::updateBasketballIntake(unsigned char rotateUp, unsigned char rotateDown, unsigned char intakeIn, unsigned char intakeOut, unsigned char intakeHopper)
{
  unsigned char intakeState = 0;
  if(rotateUp > 0)
  {
    armPivot->setThrottle(1785); //Brings intake arm up towards hopper
  }
  else if(rotateDown > 0)
  {
    armPivot->setThrottle(2585); //Lowers intake arm to ground
  }
  else
  {
    armPivot->setThrottle(2185); //Stops arm
  }

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
  armPivot->setThrottle(2185); //stop foam intake
  intakeMotor_1->setThrottle(2185); //stop soccer intake
  intakeMotor_2->setThrottle(2185); //stop soccer intake
}
