#include "Controller.h"

Controller::Controller(unsigned char* controller_array_in) :
                       controller_array(controller_array_in) {
    /* NOTHING */
}

unsigned char Controller::start(){
    return (controller_array[0] >> 6) & 1;
}
unsigned char Controller::select(){
    return (controller_array[1] >> 6) & 1;
}

unsigned char Controller::RB(){
    return (controller_array[0] >> 5) & 1;
}
unsigned char Controller::LB(){
    return (controller_array[0] >> 4) & 1;
}

unsigned char Controller::Rstick(){
    return (controller_array[1] >> 5) & 1;
}
unsigned char Controller::Lstick(){
    return (controller_array[1] >> 4) & 1;
}

unsigned char Controller::X(){
    return (controller_array[0] >> 2) & 1;
}
unsigned char Controller::Y(){
    return (controller_array[0] >> 3) & 1;
}
unsigned char Controller::B(){
    return (controller_array[0] >> 1) & 1;
}
unsigned char Controller::A(){
    return (controller_array[0] >> 0) & 1;
}

unsigned char Controller::DPadRight(){
    return (controller_array[1] >> 3) & 1;
}
unsigned char Controller::DPadLeft(){
    return (controller_array[1] >> 2) & 1;
}
unsigned char Controller::DPadUp(){
    return (controller_array[1] >> 0) & 1;
}
unsigned char Controller::DPadDown(){
    return (controller_array[1] >> 1) & 1;
}

    // These are 8-bit quantities
unsigned char Controller::LeftStickX(){
    return controller_array[2];
}
unsigned char Controller::LeftStickY(){
    return controller_array[3];
}

unsigned char Controller::RightStickX(){
    return controller_array[4];
}
unsigned char Controller::RightStickY(){
    return controller_array[5];
}

unsigned char Controller::LTrigger(){
    return controller_array[6];
}
unsigned char Controller::RTrigger(){
    return controller_array[7];
}
