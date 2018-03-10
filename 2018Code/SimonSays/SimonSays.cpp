#include "SimonSays.h"

// SimonSays::SimonSays(PCA9685* PWM, int pivotPin, int UL_Pin1, int UL_Pin2, int UR_Pin1, int UR_Pin2,
//                      int LL_Pin1, int LL_Pin2, int LR_Pin1, int LR_Pin2) : controller(PWM)
// {
//     _pivotPin = pivotPin;
//     pivot = new Victor(controller, _pivotPin);
//     UL = new DoublePiston(UL_Pin, 0);
//     UR = new DoublePiston(UR_Pin, 0);
//     LL = new DoublePiston(LL_Pin, 0);
//     LR = new DoublePiston(LR_Pin, 0);
// }


SimonSays::SimonSays(PCA9685* PWM, int pivotPin, int UL_Pin, int UR_Pin, int LL_Pin, int LR_Pin) : controller(PWM)
{
    _pivotPin = pivotPin;
    pivot = new Victor(controller, _pivotPin);
    UL = new SinglePiston(UL_Pin, 0);
    UR = new SinglePiston(UR_Pin, 0);
    LL = new SinglePiston(LL_Pin, 0);
    LR = new SinglePiston(LR_Pin, 0);
}

void SimonSays::failsafe()
{
    pivot->setThrottle(2185);
    UL->setState(0);
    UR->setState(0);
    LL->setState(0);
    LR->setState(0);
}

unsigned char SimonSays::updateSimonSays(unsigned char ArmSpeed, unsigned char UL_State, unsigned char UR_State, unsigned char LL_State, unsigned char LR_State)
{
    value = 0;

    if(UL_State == 1)
    {
        value += 1 * LL->setState(0);
        value += 2 * LR->setState(0);
        value += 4 * UL->setState(1);
        value += 8 * UR->setState(0);
    }
    else if(UR_State == 1)
    {
        // UL->setState(0);
        // UR->setState(1);
        // LL->setState(0);
        // LR->setState(0);
        value += 1 * LL->setState(0);
        value += 2 * LR->setState(0);
        value += 4 * UL->setState(0);
        value += 8 * UR->setState(1);
    }
    else if(LL_State == 1)
    {
        // UL->setState(0);
        // UR->setState(0);
        // LL->setState(1);
        // LR->setState(0);
        value += 1 * LL->setState(1);
        value += 2 * LR->setState(0);
        value += 4 * UL->setState(0);
        value += 8 * UR->setState(0);
    }
    else if(LR_State == 1)
    {
        // UL->setState(0);
        // UR->setState(0);
        // LL->setState(0);
        // LR->setState(1);
        value += 1 * LL->setState(0);
        value += 2 * LR->setState(1);
        value += 4 * UL->setState(0);
        value += 8 * UR->setState(0);
    }
    else
    {
        // UL->setState(0);
        // UR->setState(0);
        // LL->setState(0);
        // LR->setState(0);
        value += 1 * LL->setState(0);
        value += 2 * LR->setState(0);
        value += 4 * UL->setState(0);
        value += 8 * UR->setState(0);
    }

    //controller sends joystick value 0-200, must scale to 0-4095 PWM magnitude
    _armSpeed = (int)(ArmSpeed);
    _armSpeed *= 1650;
    _armSpeed /= 200;



    if(_armSpeed > 410 && _armSpeed < 1230) _armSpeed = 825;
    _armSpeed += 1360;
    pivot->setThrottle(_armSpeed);

    return value;
}
