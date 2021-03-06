//Drive base code for 2017 Mechabytes MRDC team
//Standard 8wd "Halo" drive control with passive omni drop down for pinpoint turns
//Drivin' and Derivin' Wheely Wheely TooT TooT: Aditya Chitnis
#include "Arduino.h"
#include <Servo.h>
#include "DriveBase.h"

DriveBase::DriveBase(int leftPWM1, int leftPWM2, int rightPWM1, int rightPWM2, int omniSolenoid)
{
//subsystem setup, assigns pin number and initializes pin

  lPWM1 = leftPWM1;
  lPWM2 = leftPWM2;
  rPWM1 = rightPWM1;
  rPWM2 = rightPWM2;
  _omniSolenoid = omniSolenoid;

  // pinMode(lPWM1, OUTPUT);
  // pinMode(rPWM1, OUTPUT);
  // pinMode(lPWM2, OUTPUT);
  // pinMode(rPWM2, OUTPUT);
  DriveL1.attach(lPWM1);
  DriveL2.attach(lPWM2);
  DriveR1.attach(rPWM1);
  DriveR2.attach(rPWM2);
  pinMode(_omniSolenoid, OUTPUT);
}

void DriveBase::driveBaseFailsafe()
{
  // analogWrite(lPWM1, 0);
  // analogWrite(lPWM2, 0);
  // analogWrite(rPWM1, 0);
  // analogWrite(rPWM2, 0);
  DriveL1.write(90);
  DriveL2.write(90);
  DriveR1.write(90);
  DriveR2.write(90);
}

void DriveBase::setThrottle()
{
//maps decimal 0.00-1.00 to 0-255 for PWM control

  lSpeed = ((int) _lStickY + (int) _rStickX)*(180/255);
  rSpeed = ((int) _lStickY - (int) _rStickX)*(180/255);

//constrains motor values to within the PWM limits

  if(abs(lSpeed) > 180) lSpeed = 180*(abs(lSpeed)/lSpeed);
  if(abs(rSpeed) > 180) rSpeed = 180*(abs(rSpeed)/rSpeed);


//sends value to speed controller

  // analogWrite(lPWM1, lSpeed);
  // analogWrite(lPWM2, lSpeed);
  // analogWrite(rPWM1, rSpeed);
  // analogWrite(rPWM2, rSpeed);
  DriveL1.write(lSpeed);
  DriveL2.write(lSpeed);
  DriveR1.write(rSpeed);
  DriveR2.write(rSpeed);

}

void DriveBase::setOmniDrop(boolean state)
{
//sets solenoid state
  digitalWrite(_omniSolenoid, state);
}

void DriveBase::updateDrive(byte lStickY, byte rStickX, bool propToggle)
{
//run every cycle to set drive motor value and piston state
//lStickY assigns throttle, rStickX assigns rotation,
//propToggle sets omni wheel position

  _lStickY = lStickY;
  _rStickX = rStickX;

//deadband control to prevent non-significant power output
  if(_lStickY > 102 && _lStickY < 152) _lStickY = 127;
  if(_rStickX > 102 && _rStickX < 152) _rStickX = 127;

  if(_propToggle != propToggle)
  {
    setOmniDrop(propToggle);
    _propToggle = propToggle;
  }

  setThrottle();
}
