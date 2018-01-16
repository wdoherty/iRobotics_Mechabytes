#ifndef SINGLEPISTON_H
#define SINGLEPISTON_H

class SinglePiston
{
public:
    SinglePiston(int address);
    SinglePiston(int address, bool initState);
    bool switchState();
    bool setState(bool newState);

private:
    void setPiston();
    int pin;
    bool state;
};

#endif
