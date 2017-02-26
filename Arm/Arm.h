//Drive base code for 2017 Mechabytes MRDC team
//Relay-style control for external and internal ball control rollers

#ifndef Arm_h
#define Arm_h

class Arm
{
public:

  Arm(int armPWM1, int armPWM2, int clawPWM1, int clawPWM2);
  void setArm(int lTrigger, int rTrigger, int rButton, int lButton);

private:

  int _PWM1;
  int _PWM2;
  int _PWM3;
  int _PWM4;
  int armSpeed;
  int clawSpeed;
  void setArmSpeed(int state);
  void setClawSpeed(int state);
};

#endif
