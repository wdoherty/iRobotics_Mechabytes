#ifndef SIMONSAYS_H
#define SIMONSAYS_H

#include "../../StandardLibraries/Victor/Victor.h"
#include "../../StandardLibraries/SinglePiston/SinglePiston.h"
// #include "../../StandardLibraries/DoublePiston/DoublePiston.h"

class SimonSays
{
public:
    // SimonSays(PCA9685* PWM, int pivotPin, int UL_Pin1, int UL_Pin2, int UR_Pin1, int UR_Pin2,
    //                      int LL_Pin1, int LL_Pin2, int LR_Pin1, int LR_Pin2);
    SimonSays(int UL_Pin, int UR_Pin, int LL_Pin, int LR_Pin);
    unsigned char updateSimonSays(unsigned char UL_State, unsigned char UR_State, unsigned char LL_State, unsigned char LR_State);
    void failsafe();
private:
    SinglePiston* UL, *UR, *LL, *LR;
    unsigned char value;
};

#endif
