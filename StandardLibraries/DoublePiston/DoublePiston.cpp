#include "DoublePiston.h"

DoublePiston::DoublePiston(int address1, int address2)
{
  pin1 = address1;
  pin2 = address2;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  // gpioSetMode(pin1, PI_OUTPUT);
  // gpioSetMode(pin2, PI_OUTPUT);
  state = 1;
  setPistons();
}

DoublePiston::DoublePiston(int address1, int address2, int initState)
{
  pin1 = address1;
  pin2 = address2;
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  // gpioSetMode(pin1, PI_OUTPUT);
  // gpioSetMode(pin2, PI_OUTPUT);
  state = initState;
  setPistons();
}

void DoublePiston::setPistons()
{
  digitalWrite(pin1, state);
  // gpioWrite(pin1, state);

   if(state == 0)
        digitalWrite(pin2, 1);
        // gpioWrite(pin2, 1);
    else
        digitalWrite(pin2, 0);
        // gpioWrite(pin2, 0);
}

int DoublePiston::switchState()
{
    if(state == 0)
        state = 1;
    else
        state = 0;

  setPistons();
  return state;
}

int DoublePiston::setState(int newState)
{
  if(state != newState)
  {
    state = newState;
    setPistons();
  }
  return state;
}
