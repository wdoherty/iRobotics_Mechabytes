#include "DigitalSensor.h"

DigitalSensor::DigitalSensor(int address){
    pin = address;
    pinMode(pin, INPUT);
}

int DigitalSensor::readState(){
    return digitalRead(pin);
}
