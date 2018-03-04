#include "SoccerOutput.h"

SoccerOutput::SoccerOutput(int fingerPin, int doorPin)
{
    _fingerPin = fingerPin;
    _doorPin = doorPin;
    finger = new SinglePiston(_fingerPin);
    door = new SinglePiston(_doorPin);
}

void SoccerOutput::updateSoccerOutput(unsigned char fingerPosition, unsigned char doorPosition)
{
    _fingerPosition = (int) fingerPosition;
    _doorPosition = (int) doorPosition;

    finger->setState(_fingerPosition);
    door->setState(_doorPosition);
}