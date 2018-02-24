#include "DigitalSensor.h"

DigitalSensor::DigitalSensor(int address){
    pin = address;
}

int DigitalSensor::readState(){
    return digitalRead(pin);
}
