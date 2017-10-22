#ifndef DOUBLEPISTON_H
#define DOUBLEPISTON_H

class DoublePiston
{
public:
  DoublePiston(int address1, int address2);
  DoublePiston(int address1, int address2, bool initState);
  bool switchState();
  bool setState(bool newState);
  bool setPistons();

private:
  int pin1, pin2;
  bool state;
};

#endif
