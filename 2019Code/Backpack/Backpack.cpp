#include "Backpack.h"

const int Backpack::positions[3] = {POT_UP, POT_GROUND, POT_PIT};

Backpack::Backpack(PCA9685* PWM, int linkagePin, int pitPin, int groundLevelPin, int linkagePotAddr) 
{
    controller = PWM;
    _linkagePin = linkagePin;
    _groundLevelPin = groundLevelPin;
    _pitPin = pitPin;
    _linkagePotAddr = linkagePotAddr;

    pitIntake = new Victor(controller, _pitPin);
    groundIntake = new Victor(controller, _groundLevelPin);
    linkage = new Victor(controller, _linkagePin);

    linkagePot = new Potentiometer(linkagePotAddr);  // THIS COULD CHANGE
}

Backpack::~Backpack()
{
    delete pitIntake;
    delete groundIntake;
    delete linkage;
    delete linkagePot;    
}


void Backpack::failsafe()
{
        // foamIntake->setThrottle(2185); //stop foam intake
        // soccerIntake->setThrottle(2185); //stop soccer intake
}

/*
 * setBackpackPosition
 *   DESCRIPTION: adjusts the height of the backpack mechanism.
 *
 *   INPUTS: position -- desired height of backpack
 *   OUTPUTS: none
 *   RETURN VALUE: 0 on success, -1 on failure
 *   SIDE EFFECTS: operates Victors.
 */
int Backpack::setBackpackPosition(int position){
    if (position < BACKPACK_UP || position > BACKPACK_PIT) {
        return -1;
    }

    /* turn on motor until at desired position */
    if (backpackPosition < position) {
        linkage->setThrottle(LINKAGE_DOWN);
        while (linkagePot->readState() < positions[position]) {
            /* do nothing */
        }
    } else if (backpackPosition > position) {
        linkage->setThrottle(LINKAGE_UP);
        while (linkagePot->readState() > positions[position]) {
            /* do nothing */
        }
    }
    linkage->setThrottle(LINKAGE_OFF);
    
    backpackPosition = position;
    return 0;
}

int Backpack::setGroundIntake(int speed) {
    if (speed < 0 || speed > 4095) {
        return -1;
    }
    groundIntake->setThrottle(speed);
    return 0;
}

int Backpack::setPitIntake(int speed){
    if (speed < 0 || speed > 4095) {
        return -1;
    }
    pitIntake->setThrottle(speed);
    return 0;
}