#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller
{
public:
        // head of 8-element controller array received from XBox controller
    Controller(unsigned char* controller_array_in);

        // These are boolean values, may be changed to boolean type
    unsigned char start();
    unsigned char select();

    unsigned char RB();
    unsigned char LB();

    unsigned char Rstick();
    unsigned char Lstick();

    unsigned char X();
    unsigned char Y();
    unsigned char B();
    unsigned char A();

    unsigned char DPadRight();
    unsigned char DPadLeft();
    unsigned char DPadUp();
    unsigned char DPadDown();

        // These are 8-bit quantities
    unsigned char LeftStickX();
    unsigned char LeftStickY();

    unsigned char RightStickX();
    unsigned char RightStickY();

    unsigned char LTrigger();
    unsigned char RTrigger();

private:
    unsigned char* controller_array;
};

#endif
