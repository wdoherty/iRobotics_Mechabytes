//Drive base code for 2017 Mechabytes MRDC team
//Standard 8wd "Halo" drive control with passive omni drop down for pinpoint turns

#ifndef DriveBase_h
#define DriveBase_h

#include "Arduino.h"

class DriveBase
{
public:

  DriveBase(int leftPWM1, int leftPWM2, int rightPWM1, int rightPWM2, int omniSolenoid);
  void updateDrive(double lStickY, double rStickX, bool propToggle);
  void driveBaseFailsafe();

private:

  int lPWM1;
  int lPWM2;
  int rPWM1;
  int rPWM2;
  int _omniSolenoid;
  double _lStickY = 0.0;
  double _rStickX = 0.0;
  bool _propToggle = false;
  int lSpeed = 0;
  int rSpeed = 0;
  void setThrottle();
  void setOmniDrop(boolean state);
  double maxAccelTime;

};

#endif
