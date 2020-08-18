#include "DigitalSensor.h"

DigitalSensor::DigitalSensor(int address){
    pin = address;
    /* wiringpi lib */
    pinMode(pin, INPUT);
    /* pigpio lib */
    // gpioSetMode(pin, PI_INPUT);
}

int DigitalSensor::readState(){
    /* wiringpi lib */
    return digitalRead(pin);
    /* pigpio lib */
    // return gpioRead(pin);
}
