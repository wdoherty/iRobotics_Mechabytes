//Drive base code for 2017 Mechabytes MRDC team
//Relay-style control for external and internal ball control rollers

#ifndef DriveBase_h
#define DriveBase_h

class Intake
{
public:

  Intake(int PWM);
  void runIntake(bool lTrigger, bool rTrigger);

private:

  int _PWM;
  int speed;
  void setSpeed(int state);
};

#endif
