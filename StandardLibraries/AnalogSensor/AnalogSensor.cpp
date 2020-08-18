#include "AnalogSensor.h"

void init(int ADSBase, int pin)
{
  _pin = pin;
  _ADSBase = ADSBase;
}

int read()
{
  return analogRead(_ADSBase + pin);
}
