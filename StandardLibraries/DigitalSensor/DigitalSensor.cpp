#include "DigitalSensor.h"

DigitalSensor::DigitalSensor(int address){
    pin = address;
    pinMode(pin, INPUT);
    // gpioSetMode(pin, PI_INPUT);
}

int DigitalSensor::readState(){
    return digitalRead(pin);
    // return gpioRead(pin);
}
