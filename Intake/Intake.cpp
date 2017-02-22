#include "Arduino.h"
#include "Intake.h"
//Kyle Patel
Intake::Intake(int PWM)
{
//subsystem setup, assigns pin number and initializes pin

  _PWM = PWM;

  pinMode(_PWM, OUTPUT);
}

void Intake::setSpeed(int state)
{
//for input -1, 0, 1, sets speed to full forward, full reverse, or off

  speed = 255 * state;

//sends value to speed controller

  analogWrite(_PWM, speed);
}

void Intake::runIntake(bool lTrigger, bool rTrigger)
{
//if left trigger held, run intake out
//if right trigger held, run intake in
//right trigger takes priority

if(rTrigger)
{
  setSpeed(1);
}
else if(lTrigger)
{
  setSpeed(-1);
}
else setSpeed(0);

}
