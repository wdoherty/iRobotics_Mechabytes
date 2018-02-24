#include "SimonSays.h"

SimonSays::SimonSays(PCA9685* PWM, int pivotPin) : controller(PWM)
{
    _pivotPin = pivotPin;
    pivot = new Victor(controller, _pivotPin);
}

void SimonSays::updateSimonSays(int runUp, int runDown)
{
    if(runUp == 1 && runDown == 0)
    {
        pivot->setThrottle(0); //runs arm down
    }
    else if(runUp == 0 && runDown == 1)
    {
        pivot->setThrottle(4095); //runs arm up
    }
    else
    {
        pivot->setThrottle(4095/2); //stops arm
    }
}
