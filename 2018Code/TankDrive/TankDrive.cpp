#include "TankDrive.h"


TankDrive::TankDrive(PCA9685* PWM, int leftPin1, int leftPin2, int rightPin1, int rightPin2) : controller(PWM)
{
    _leftPin1 = leftPin1;
    _leftPin2 = leftPin2;
    _rightPin1 = rightPin1;
    _rightPin2 = rightPin2;
    left1 = new Victor(controller, _leftPin1);
    left2 = new Victor(controller, _leftPin2);
    right1 = new Victor(controller, _rightPin1);
    right2 = new Victor(controller, _rightPin2);
}

void TankDrive::updateDrive(byte lStickY, byte rStickX)
{
//run every cycle to set drive motor value and piston state
//lStickY assigns throttle, rStickX assigns rotation,

  _lStickY = lStickY;
  _rStickX = rStickX;

//deadband control to prevent non-significant power output
  if(_lStickY > 102 && _lStickY < 152) _lStickY = 127;
  if(_rStickX > 102 && _rStickX < 152) _rStickX = 127;

  setThrottle();
}

void TankDrive::setThrottle()
{
    //maps decimal 0.00-1.00 to 0-255 for PWM control

      lSpeed = ((int) _lStickY + (int) _rStickX)*(4095/255);
      rSpeed = ((int) _lStickY - (int) _rStickX)*(4095/255);

    //constrains motor values to within the PWM limits

      if(abs(lSpeed) > 4095) lSpeed = 4095*(abs(lSpeed)/lSpeed);
      if(abs(rSpeed) > 4095) rSpeed = 4095*(abs(rSpeed)/rSpeed);


    //sends value to speed controller

      left1->setThrottle(lSpeed);
      left2->setThrottle(lSpeed);
      right1->setThrottle(rSpeed);
      right2->setThrottle(rSpeed);
}
