#include "Arm.h"

Arm::Arm(PCA9685* PWM, int armPin) : controller(PWM)
{
    _armPin = armPin;
    armPivot = new Victor(controller, _armPin);
}

void Arm::updateArm(int armUp, int armDown)
{
    if(armUp == 1 && armDown == 0)
    {
        armPivot->setThrottle(0); //runs arm down
    }
    else if(armUp == 0 && armDown == 1)
    {
        armPivot->setThrottle(4095); //runs arm up
    }
    else
    {
        armPivot->setThrottle(4095/2); //stops arm
    }
}
