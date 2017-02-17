//Drive base code for 2017 Mechabytes MRDC team
//Standard 8wd "Halo" drive control with passive omni drop down for pinpoint turns

#include "Arduino.h"
#include "DriveBase.h"

DriveBase::DriveBase(int leftPWM, int rightPWM, bool omniSolenoid)
{
//subsystem setup, assigns pin number and initializes pin

  lPWM = leftPWM;
  rPWM = rightPWM;
  _omniSolenoid = omniSolenoid;

  pinMode(lPWM, OUTPUT);
  pinMode(rPWM, OUTPUT);
  pinMode(_omniSolenoid, OUTPUT);
}

void DriveBase::setThrottle()
{
//maps decimal 0.00-1.00 to 0-255 for PWM control

  lSpeed = (int)floor((_lStickY - _rStickX)*255);
  rSpeed = (int)floor((_lStickY + _rStickX)*255);

//constrains motor values to within the PWM limits

  if(abs(lSpeed) > 255) lSpeed = 255*(abs(lSpeed)/lSpeed);
  if(abs(rSpeed) > 255) rSpeed = 255*(abs(rSpeed)/rSpeed);

//sends value to speed controller

  analogWrite(lPWM, lSpeed);
  analogWrite(rPWM, rSpeed);
}

void DriveBase::setOmniDrop(boolean state)
{
//sets solenoid state
  digitalWrite(_omniSolenoid, state);
}

void DriveBase::updateDrive(double lStickY, double rStickX, boolean propToggle)
{
//run every cycle to set drive motor value and piston state
//lStickY assigns throttle, rStickX assigns rotation,
//propToggle sets omni wheel position

  _lStickY = lStickY;
  _rStickX = rStickX;

//deadband control to prevent non-significant power output
  if(_lStickY < .1) _lStickY = 0;
  if(_rStickX < .1) _rStickX = 0;

  if(_propToggle != propToggle)
  {
    setOmniDrop(propToggle);
    _propToggle = propToggle;
  }

  setThrottle();
}
