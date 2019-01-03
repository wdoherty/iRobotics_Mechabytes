#include "Potentiometer.h"

Potentiometer::Potentiometer(int address) {
    pin = address;
}

int Potentiometer::readState() {
    return state;
}
