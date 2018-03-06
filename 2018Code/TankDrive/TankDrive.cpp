#include "TankDrive.h"
#include <stdlib.h>
#include <math.h>
#include <iostream>


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
    headingMod = 1.6;
}

void TankDrive::failsafe()
{
    left1->setThrottle(2048);
    left2->setThrottle(2048);
    right1->setThrottle(2048);
    right2->setThrottle(2048);
}

void TankDrive::updateDrive(unsigned char throttle, unsigned char reverse, unsigned char rStickX)
{
//scales input signa from
_throttle = (throttle >> 1);
_throttle *= 4095;
_throttle /= 100;

_reverse = (reverse >> 1);
_reverse *= 4095;
_reverse /= 100;

int throttleMag = _throttle - _reverse;
throttleMag += (4095/2);

_rStickX = rStickX;

_rStickX *= 4095;
_rStickX /= 200;

if(throttleMag > 1930 && throttleMag < 2160) throttleMag = 2048;
if(_rStickX > 1930 && _rStickX < 2160) _rStickX = 2048;
setThrottle(throttleMag, _rStickX);

  // setThrottle();
}

void TankDrive::setThrottle(int lStickY, int rStickX)
{
       double throttle = abs(lStickY-2048) * (lStickY < 2048 ? -1 : 1);    //// = magnitude & direction of throttle
       double heading = abs(rStickX-2048) * (rStickX < 2048 ? -1 : 1);    //// = magnitude and direction of heading

       double angularPower = fabs(throttle/2048)*(heading)*(headingMod); //scales rotation by throttle value when not in quick turn

       setQuickTurn(throttle, heading);

   if(quickTurn)
   {
   lSpeed = throttle + heading + 2048;
   rSpeed = throttle - heading + 2048;
   }
   else
   {
   lSpeed = throttle + angularPower + 2048;
   rSpeed = throttle - angularPower + 2048;
   }

   //constrains motor values to within the PWM limits
if(lSpeed > 4095) lSpeed = 4095;
if(rSpeed > 4095) rSpeed = 4095;
if(lSpeed < 0) lSpeed = 0;
if(rSpeed < 0) rSpeed = 0;

//adjusts speed of one side of drive to compensate for uneven steering
// lSpeedMag = abs(90 - lSpeed);
// lSpeedMag *= 13;
// lSpeedMag /= 20;
// if(lSpeed > 90) lSpeed = 90 + lSpeedMag;
// else lSpeed = 90 - lSpeedMag;

//sends drive speeds back to DS
// feedback[0] = lSpeed;
// feedback[1] = rSpeed;

//optionally invert drive direction if electrical swap is difficult
// lSpeed = 4095 - lSpeed;
// rSpeed = 4095 - rSpeed;

    //sends value to speed controller
	  std::cout << lSpeed << std::endl;

      left1->setThrottle(lSpeed);
      left2->setThrottle(lSpeed);
      right1->setThrottle(rSpeed);
      right2->setThrottle(rSpeed);
}

void TankDrive::setQuickTurn(double throttle, double heading)
{
    if((fabs(throttle) < 5) && (fabs(heading) > 5)) quickTurn = true;
    else quickTurn = false;
}
