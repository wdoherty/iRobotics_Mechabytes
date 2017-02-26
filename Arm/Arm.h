//Drive base code for 2017 Mechabytes MRDC team
//Relay-style control for external and internal ball control rollers

#ifndef Arm_h
#define Arm_h

class Arm
{
public:

  Arm(int armPWM, int wristPWM);
  void setArm(int lTrigger, int rTrigger, int rButton, int lButton);
  void armFailsafe();

private:

  int _PWM1;
  int _PWM2;
  int armSpeed;
  int wristSpeed;
  void setArmSpeed(int state);
  void setWristSpeed(int state);
};

#endif
