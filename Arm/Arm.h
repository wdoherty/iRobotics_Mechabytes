//Drive base code for 2017 Mechabytes MRDC team
//Relay-style control for external and internal ball control rollers

#ifndef Arm_h
#define Arm_h

#include <Arduino.h>

class Arm
{
public:

  Arm(int armPWM, int wristPWM);
  void setArm(byte lTrigger, byte rTrigger, bool rButton, bool lButton);
  void armFailsafe();

private:

  int _PWM1;
  int _PWM2;
  int armSpeed;
  int wristSpeed;
  void setArmSpeed(byte _lTrigger, byte _rTrigger);
  void setWristSpeed(int state);
};

#endif
