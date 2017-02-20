//Drive base code for 2017 Mechabytes MRDC team
//Relay-style control for external and internal ball control rollers

#ifndef Arm_h
#define Arm_h

class Arm
{
public:

  Arm(int PWM1, int PWM2);
  void setArm();

private:

  int _PWM1;
  int _PWM2;
  int speed;

};

#endif
