#include "SoccerOutput.h"

SoccerOutput::SoccerOutput(int fingerPin, int doorPin)
{
    _fingerPin = fingerPin;
    _doorPin = doorPin;
    finger = new SinglePiston(_fingerPin);
    door = new SinglePiston(_doorPin);
}

unsigned char SoccerOutput::updateSoccerOutput(unsigned char fingerPosition, unsigned char doorPosition)
{
    value = 0;

    _fingerPosition = (int) fingerPosition;
    _doorPosition = (int) doorPosition;

    value += 4 * finger->setState(_fingerPosition);
    value += 8 * door->setState(_doorPosition);

    return value;
}
