//Drive base code for 2017 Mechabytes MRDC team
//Relay-style control for external and internal ball control rollers

#ifndef Intake_h
#define Intake_h

#include <Arduino.h>
#include <Servo.h>

class Intake
{
public:

  Intake(int PWM, int pistonIO);
  void runIntake(bool lTrigger, bool rTrigger, bool piston);
  void StopAllMotors();

private:
  Servo intake1;
  Servo intake2;
  bool piston_out = false;
  int _PISTON;
  int _PWM;
  int speed;
  bool prevState = false;
  void setSpeed(int state);
  void runPiston(bool piston);
};

#endif
