#include "BasketballShooter.h"
#include <stdlib.h>
#include <math.h>

BasketballShooter::BasketballShooter(PCA9685* PWM, int stopperPin, int shooterPin, int turretPin, int stagingPin1, int stagingPin2) : controller(PWM)
{
  _stopperPin = stopperPin;
  _shooterPin = shooterPin;
  _turretPin = turretPin;
  _stagingPin1 = stagingPin1;
  _stagingPin2 = stagingPin2;

  stopper = new SinglePiston(stopperPin, 0);
  shooter = new Victor(controller, _shooterPin);
  turret = new Victor(controller, _turretPin);
  staging1 = new Victor(controller, _stagingPin1);
  staging2 = new Victor(controller, _stagingPin2);

  shooterToggle = 0;
  prevShooterState = shooterToggle;
}

unsigned char BasketballShooter::updateBasketballShooter(unsigned char stage, unsigned char feed, unsigned char runShooter, int turretOfffset)
{
  int turretDirection = 0;
  int turretMagnitude = 0;

  if(runShooter > 0 && runShooter != prevShooterState)
  {
    if(shooterToggle == 0) shooterToggle = 1;
    else shooterToggle = 0;

    if(shooterToggle > 0) shooter->setThrottle(2785);
    else shooter->setThrottle(2185);
  }
  prevShooterState = runShooter;

  //moves balls towards shooter, but keeps output closed
  if(stage > 0)
  {
    stopper->setState(0);
    staging1->setThrottle(2585);
    staging2->setThrottle(2585);
  }

  else if(feed > 0)
  {
    stopper->setState(1);
    staging1->setThrottle(2585);
    staging2->setThrottle(2585);
  }

  else
  {
    staging1->setThrottle(2185);
    staging2->setThrottle(2185);
  }

  //20 is arbitrary pixel offset, will tune later
  if(abs(turretOfffset > 20))
  {
    turretDirection = abs(turretOfffset)/turretOfffset;
    turretMagnitude = (400 * turretDirection) + 2185;
    turret->setThrottle(turretMagnitude);
  }
  else
  {
    turret->setThrottle(2185);
  }

  return 1;
}

void BasketballShooter::failsafe()
{
  shooter->setThrottle(2185);
  turret->setThrottle(2185);
  staging1->setThrottle(2185);
  staging2->setThrottle(2185);
}
