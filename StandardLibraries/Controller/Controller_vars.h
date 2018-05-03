#ifndef CONTROLLER_VARS_H
#define CONTROLLER_VARS_H

class Controller_vars
{
public:
        // head of 8-element controller array received from XBox controller
    Controller_vars(unsigned char* controller_array_in);

    void UpdateController();

        // These are boolean values, may be changed to boolean type
    unsigned char start;
    unsigned char select;

    unsigned char RB;
    unsigned char LB;

    unsigned char Rstick;
    unsigned char Lstick;

    unsigned char X;
    unsigned char Y;
    unsigned char B;
    unsigned char A;

    unsigned char DPadRight;
    unsigned char DPadLeft;
    unsigned char DPadUp;
    unsigned char DPadDown;

        // These are 8-bit quantities
    unsigned char LeftStickX;
    unsigned char LeftStickY;

    unsigned char RightStickX;
    unsigned char RightStickY;

    unsigned char LTrigger;
    unsigned char RTrigger;

private:
    unsigned char* controller_array;
};

#endif
