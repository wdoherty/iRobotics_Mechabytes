#ifndef SOCCEROUTPUT_H
#define SOCCEROUTPUT_H

#include "../../StandardLibraries/SinglePiston/SinglePiston.h"

class SoccerOutput
{
public:
    SoccerOutput(int fingerPin, int doorPin);
    unsigned char updateSoccerOutput(unsigned char fingerPosition, unsigned char doorPosition);

private:
    int _fingerPin, _doorPin;
    int _fingerPosition, _doorPosition;
    unsigned char value;
    SinglePiston* finger, *door;
};

#endif
