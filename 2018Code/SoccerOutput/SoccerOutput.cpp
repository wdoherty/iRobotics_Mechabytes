#include "SoccerOutput.h"

SoccerOutput::SoccerOutput(int fingerPin, int doorPin)
{
    finger = new SinglePiston(fingerPin);
    door = new SinglePiston(doorPin);
}

void SoccerOutput::updateSoccerOutput(unsigned char fingerPosition, unsigned char doorPosition)
{
    _fingerPosition = (int) fingerPosition;
    _doorPosition = (int) doorPosition;

    finger->setState(_fingerPosition);
    door->setState(_doorPosition);
}
