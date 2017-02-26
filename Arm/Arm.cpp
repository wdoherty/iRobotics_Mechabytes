#include "Arduino.h"
#include "Arm.h"
//this is my domain <3 :) -Jason
Arm::Arm(int armPWM1, int armPWM2, int clawPWM1, int clawPWM2)
{
//subsystem setup, assigns pin number and initializes pin

  _PWM1 = armPWM1;
  _PWM2 = armPWM2;
  _PWM3 = clawPWM1;
  _PWM4 = clawPWM2;

  pinMode(_PWM1, OUTPUT);
  pinMode(_PWM2, OUTPUT);
  pinMode(_PWM3, OUTPUT);
  pinMode(_PWM4, OUTPUT);
}

void Arm::setArmSpeed(int state)
{
//for input -1, 0, 1, sets speed to half forward, half reverse, or off

  armSpeed = 125 * state;

//sends value to speed controller

  analogWrite(_PWM1, armSpeed);
  analogWrite(_PWM2, -armSpeed);
}

void Arm::setClawSpeed(int state)
{
//for input -1, 0, 1, sets speed to half forward, half reverse, or off
  clawSpeed = 125 * state;

  //sends value to speed controller

    analogWrite(_PWM3, clawSpeed);
    analogWrite(_PWM4, -clawSpeed);
}

void Arm::armFailsafe()
{
  analogWrite(_PWM1, 0);
  analogWrite(_PWM2, 0);

  analogWrite(_PWM3, 0);
  analogWrite(_PWM4, 0);
}

void Arm::setArm(int lTrigger, int rTrigger, int rButton, int lButton)
{
//if left trigger held, run intake out
//if right trigger held, run intake in
//right trigger takes priority
if(rTrigger) setArmSpeed(1);
else if(lTrigger) setArmSpeed(-1);
else setArmSpeed(0);

if(rButton) setClawSpeed(1);
else if(lButton) setClawSpeed(-1);
else setArmSpeed(0);

}
