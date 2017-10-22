#include "DoublePiston.h"
// #include <wiringPi.h>

DoublePiston(int address1, int address2)
{
  pin1 = address1;
  pin2 = address2;
  // pinMode(pin1, OUTPUT);
  // pinMode(pin2, OUTPUT);
  state = true;
  setPistons();
}

DoublePiston(int address1, int address2, bool initState)
{
  pin1 = address1;
  pin2 = address2;
  // pinMode(pin1, OUTPUT);
  // pinMode(pin2, OUTPUT);
  state = initState;
  setPistons();
}

void DoublePiston::setPistons()
{
  // digitalWrite(pin1, state);
  // digitalWrite(pin2, !state);
}

bool DoublePiston::switchState()
{
  state = !state;
  setPistons();
  return state;
}

bool DoublePiston::setState(bool newState)
{
  if(state != newState)
  {
    state = newState;
    setPistons();
  }
  return state;
}
