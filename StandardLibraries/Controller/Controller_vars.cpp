#include "Controller_vars.h"

Controller_vars::Controller_vars(unsigned char* controller_array_in) :
                                 controller_array(controller_array_in) {
    /* NOTHING */
}

void Controller_vars::UpdateController(){
    start = (controller_array[0] >> 6) & 1;
    select = (controller_array[1] >> 6) & 1;

    RB = (controller_array[0] >> 5) & 1;
    LB = (controller_array[0] >> 4) & 1;

    Rstick = (controller_array[1] >> 5) & 1;
    Lstick = (controller_array[1] >> 4) & 1;

    X = (controller_array[0] >> 2) & 1;
    Y = (controller_array[0] >> 3) & 1;
    B = (controller_array[0] >> 1) & 1;
    A = (controller_array[0] >> 0) & 1;

    DPadRight = (controller_array[1] >> 3) & 1;
    DPadLeft = (controller_array[1] >> 2) & 1;
    DPadUp = (controller_array[1] >> 0) & 1;
    DPadDown = (controller_array[1] >> 1) & 1;

    LeftStickX = controller_array[2];
    LeftStickY = controller_array[3];

    RightStickX = controller_array[4];
    RightStickY = controller_array[5];

    LTrigger = controller_array[6];
    RTrigger = controller_array[7];
}
