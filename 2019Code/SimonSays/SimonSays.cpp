#include "SimonSays.h"

SimonSays::SimonSays(int UL_Pin, int UR_Pin, int LL_Pin, int LR_Pin)
{
    UL = new SinglePiston(UL_Pin, 0);
    UR = new SinglePiston(UR_Pin, 0);
    LL = new SinglePiston(LL_Pin, 0);
    LR = new SinglePiston(LR_Pin, 0);
}

void SimonSays::failsafe()
{
    UL->setState(0);
    UR->setState(0);
    LL->setState(0);
    LR->setState(0);
}

unsigned char SimonSays::updateSimonSays(unsigned char UL_State, unsigned char UR_State, unsigned char LL_State, unsigned char LR_State)
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
        value += 1 * LL->setState(0);
        value += 2 * LR->setState(0);
        value += 4 * UL->setState(0);
        value += 8 * UR->setState(1);
    }
    else if(LL_State == 1)
    {
        value += 1 * LL->setState(1);
        value += 2 * LR->setState(0);
        value += 4 * UL->setState(0);
        value += 8 * UR->setState(0);
    }
    else if(LR_State == 1)
    {
        value += 1 * LL->setState(0);
        value += 2 * LR->setState(1);
        value += 4 * UL->setState(0);
        value += 8 * UR->setState(0);
    }
    else
    {
        value += 1 * LL->setState(0);
        value += 2 * LR->setState(0);
        value += 4 * UL->setState(0);
        value += 8 * UR->setState(0);
    }
    return value;
}
