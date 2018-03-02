#include "SimonSays.h"

SimonSays::SimonSays(PCA9685* PWM, int pivotPin, int UL_Pin1, int UL_Pin2, int UR_Pin1, int UR_Pin2,
                     int LL_Pin1, int LL_Pin2, int LR_Pin1, int LR_Pin2) : controller(PWM)
{
    _pivotPin = pivotPin;
    pivot = new Victor(controller, _pivotPin);
    UL = new DoublePiston(UL_Pin1, UL_Pin2, false);
    UR = new DoublePiston(UR_Pin1, UR_Pin2, false);
    LL = new DoublePiston(LL_Pin1, LL_Pin2, false);
    LR = new DoublePiston(LR_Pin1, LR_Pin2, false);
}

void SimonSays::failsafe()
{
    pivot->setThrottle(2048);
    UL->setState(0);
    UR->setState(0);
    LL->setState(0);
    LR->setState(0);
}

void SimonSays::updateSimonSays(unsigned char ArmSpeed, unsigned char UL_State, unsigned char UR_State, unsigned char LL_State, unsigned char LR_State)
{
    if(UL_State == 1)
    {
        UL->setState(1);
        UR->setState(0);
        LL->setState(0);
        LR->setState(0);
    }
    else if(UR_State == 1)
    {
        UL->setState(0);
        UR->setState(1);
        LL->setState(0);
        LR->setState(0);
    }
    else if(LL_State == 1)
    {
        UL->setState(0);
        UR->setState(0);
        LL->setState(1);
        LR->setState(0);
    }
    else if(LR_State == 1)
    {
        UL->setState(0);
        UR->setState(0);
        LL->setState(0);
        LR->setState(1);
    }
    else
    {
        UL->setState(0);
        UR->setState(0);
        LL->setState(0);
        LR->setState(0);
    }

    //controller sends joystick value 0-200, must scale to 0-4095 PWM magnitude
    _armSpeed = (int)(ArmSpeed);
    _armSpeed *= 4095;
    _armSpeed /= 200;

    if(_armSpeed > 1023 && _armSpeed < 3072) _armSpeed = 2048;
    pivot->setThrottle(_armSpeed);
}
