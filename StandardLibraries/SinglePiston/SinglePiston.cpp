#include "SinglePiston.h"

SinglePiston::SinglePiston(int address){
    pin = address;
    // pinMode(pin, OUTPUT);
    state = true;
    setPiston();
}
SinglePiston::SinglePiston(int address, bool initState){
    pin = address;
    // pinMode(pin, OUTPUT);
    state = initState;
    setPiston();
}

void SinglePiston::setPiston(){
    //digitalWrite(pin, state);
}


bool SinglePiston::switchState(){
    state = !state;
    setPiston();
    return state;
}

bool SinglePiston::setState(bool newState){
    if(state != newState){
        state = newState;
        setPiston();
    }
    return state;
}
