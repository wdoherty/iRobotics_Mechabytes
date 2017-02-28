#include "Arduino.h"
#include "Intake.h"
//Kyle Patel
//piston runs the arm that opens the door
Intake::Intake(int PWM, int pistonIO)
{
//subsystem setup, assigns pin number and initializes pin

  _PWM = PWM;
  _PISTON = pistonIO;
  pinMode(_PISTON, OUTPUT);//pin for piston control
  pinMode(_PWM, OUTPUT);
}

void Intake::setSpeed(int state)
{
//for input -1, 0, 1, sets speed to full forward, full reverse, or off

  speed = 127 * state;

//sends value to speed controller

  analogWrite(_PWM, speed);
}

void Intake::runPiston(bool piston)//accepts piston as state of button
{
    digitalWrite(_PISTON, piston);//send 'pressed' to _PISTON
}

void Intake::StopAllMotors()
{
  analogWrite(_PWM, 0);
}

void Intake::runIntake(bool lTrigger, bool rTrigger, bool piston)
{
//if left trigger held, run intake out
//if right trigger held, run intake in
//right trigger takes priority
if(rTrigger)
{
  setSpeed(1);//run intake in
}
else if(lTrigger)
{
  setSpeed(-1);//run intake out
}
else setSpeed(0);//do nothing

if(piston && piston != prevState)
{
  runPiston(!piston_out);
  piston_out = !piston_out;
  prevState = piston;
}
else if(!piston)
{
  prevState = piston;
}
}
