#ifndef SOCCEROUTPUT_H
#define SOCCEROUTPUT_H

#include "../../StandardLibraries/SinglePiston/SinglePiston.h"

class SoccerOutput
{
public:
    SoccerOutput(int fingerPin, int doorPin);
    void updateSoccerOutput(unsigned char fingerPosition, unsigned char doorPosition);

private:
    int _fingerPin, _doorPin;
    int _fingerPosition, _doorPosition;
    SinglePiston* finger, *door;
};

#endif
