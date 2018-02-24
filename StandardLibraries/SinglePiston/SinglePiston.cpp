#include "SinglePiston.h"

SinglePiston::SinglePiston(int address){
    pin = address;
    // pinMode(pin, OUTPUT);
    state = 1;
    setPiston();
}
SinglePiston::SinglePiston(int address, int initState){
    pin = address;
    // pinMode(pin, OUTPUT);
    state = initState;
    setPiston();
}

void SinglePiston::setPiston(){
    digitalWrite(pin, state);
}


int SinglePiston::switchState(){
    if(state == 0)
        state = 1;
    else
        state = 0;

    setPiston();
    return state;
}

int SinglePiston::setState(int newState){
    if(state != newState){
        state = newState;
        setPiston();
    }
    return state;
}
