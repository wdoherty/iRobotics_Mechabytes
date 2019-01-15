#ifndef BACKPACK_H
#define BACKPACK_H

#include "../../StandardLibraries/Victor/Victor.h"
#include "../../StandardLibraries/Potentiometer/Potentiometer.h"

#define BACKPACK_UP     0       /* position when we are carrying the balls                      */
#define BACKPACK_GROUND 1       /* position when we are picking balls up from the ground        */
#define BACKPACK_PIT    2       /* position when we are reaching down into the pit to get balls */

//TODO: dummy values here, figure out these actual values
#define POT_UP          100     /* position when we are carrying the balls                      */
#define POT_GROUND      400     /* position when we are picking balls up from the ground        */
#define POT_PIT         500     /* position when we are reaching down into the pit to get balls */
#define LINKAGE_UP      1000    /* throttle setting when raising linkage                        */
#define LINKAGE_DOWN    3000    /* throttle setting when lowering linkage                       */
#define LINKAGE_OFF     2185    /* throttle setting when holding linkage in position            */

class Backpack 
{
public:
    Backpack(PCA9685* PWM, int linkagePin, int pitPin, int groundLevelPin, int linkagePotAddr);
    ~Backpack();
    int setBackpackPosition(int position);
    int setGroundIntake(int speed);
    int setPitIntake(int speed);
    void failsafe();

private:
    PCA9685* controller;
    int _linkagePin, _groundLevelPin, _pitPin, _linkagePotAddr;
    int backpackPosition;
    
    Victor* linkage;
    Victor* pitIntake;
    Victor* groundIntake;
    Potentiometer* linkagePot;

    static const int positions[3];
};

#endif