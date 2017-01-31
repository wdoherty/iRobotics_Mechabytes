//Drive base code for 2017 Mechabytes MRDC team
//Standard 8wd "Halo" drive control with passive omni drop down for pinpoint turns
//Written by Billy Doherty

#ifndef DriveBase_h
#define DriveBase_h

#include "Arduino.h"

Class DriveBase
{
public:

  DriveBase(int leftPWM, int rightPWM);
  updateDrive(double lStickY, double rStickX, boolean propToggle);

private:

  int lPWM;
  int rPWM;
  int _omniSolenoid;
  double _lStickY = 0.0;
  double _rStickX = 0.0;
  boolean _propToggle = false;
  int lSpeed = 0;
  int rSpeed = 0;
  void setThrottle();
  void setOmniDrop(boolean state);
  double maxAccelTime;

};

#endif
