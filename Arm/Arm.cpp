#include "Arduino.h"
#include "Arm.h"
//this is my domain <3 :) -Jason
Arm::Arm(int PWM1, int PWM2)
{
//subsystem setup, assigns pin number and initializes pin

  _PWM1 = PWM1;
  _PWM2 = PWM2;

  pinMode(_PWM1, OUTPUT);
  pinMode(_PWM2, OUTPUT);
}

// void Arm::setSpeed(int state)
// {
// //for input -1, 0, 1, sets speed to full forward, full reverse, or off
//
//   speed = 255 * state;
//
// //sends value to speed controller
//
//   analogWrite(_PWM, speed);
// }

void Arm::setArm()
{
//if left trigger held, run intake out
//if right trigger held, run intake in
//right trigger taakes priority


}
