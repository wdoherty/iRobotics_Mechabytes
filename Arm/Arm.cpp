#include "Arduino.h"
#include "Arm.h"
//this is my domain <3 :) -Jason
Arm::Arm(int armPWM, int wristPWM)
{
//subsystem setup, assigns pin number and initializes pin

  _PWM1 = armPWM;
  _PWM2 = wristPWM;

  pinMode(_PWM1, OUTPUT);
  pinMode(_PWM2, OUTPUT);
}

void Arm::setArmSpeed(byte _lTrigger, byte _rTrigger)
{
//for input -1, 0, 1, sets speed to half forward, half reverse, or off

  // armSpeed = 125 * state;
  armSpeed = 127 + (int) _rTrigger - (int) _lTrigger;
  // if(abs(armSpeed) > 255) armSpeed = 255 * (abs(armSpeed) / armSpeed);

//sends value to speed controller

   analogWrite(_PWM1, armSpeed);

}

void Arm::setWristSpeed(int state)
{
//for input -1, 0, 1, sets speed to half forward, half reverse, or off
  wristSpeed = 125 * state;

  //sends value to speed controller

    analogWrite(_PWM2, wristSpeed);
}

void Arm::armFailsafe()
{
  analogWrite(_PWM1, 0);
  analogWrite(_PWM2, 0);
}

void Arm::setArm(byte lTrigger, byte rTrigger, bool rButton, bool lButton)
{
//if left trigger held, run intake out
//if right trigger held, run intake in
//right trigger takes priority
// if(rTrigger) setArmSpeed();
// else if(lTrigger) setArmSpeed(-1);
// else setArmSpeed(0);
setArmSpeed((lTrigger >> 1), (rTrigger >> 1));

if(rButton) setWristSpeed(1);
else if(lButton) setWristSpeed(-1);
else setWristSpeed(0);

}
