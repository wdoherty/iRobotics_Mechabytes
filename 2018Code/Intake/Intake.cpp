#include "Intake.h"

Intake::Intake(PCA9685* PWM, int foamPin, int soccerPin, int hoodPin) : controller(PWM)
{
    _foamPin = foamPin;
    _soccerPin = soccerPin;
    _hoodPin = hoodPin;
    foamIntake = new Victor(controller, _foamPin);
    soccerIntake = new Victor(controller, _soccerPin);
    hood = new SinglePiston(hoodPin, 0);
    //hood2 = new SinglePiston(19, 1);
    hoodHold = true;
}

void Intake::failsafe()
{
        foamIntake->setThrottle(2185); //stop foam intake
        soccerIntake->setThrottle(2185); //stop soccer intake
}

unsigned char Intake::updateIntake(unsigned char foamTrigger, unsigned char soccerTrigger, unsigned char doorReset)
{
    //Driver must hold button down to use Intake
    //Soccer gets priority, always

    value = 0;  // default: neither trigger operational

    if((int)soccerTrigger == 1)
    {
        foamIntake->setThrottle(1785); //run the foam ball intake in reverse: soccer balls are in contact with it
        soccerIntake->setThrottle(2585); //run main soccer intake in
        value = 2;  // binary 10, soccer bit high
        hoodHold = false;
    }
    else if((int)foamTrigger == 1)
    {
        foamIntake->setThrottle(2585); //run the foam ball intake in
        soccerIntake->setThrottle(1785); //reverse soccer intake
        value = 1;  // binary 01, foam bit high
        hoodHold = false;
    }
    else
    {
        foamIntake->setThrottle(2185); //stop foam intake
        soccerIntake->setThrottle(2185); //stop soccer intake
    }
    if((int)doorReset == 1) hoodHold = true;

    if(!hoodHold) hood->setState(1);
    else hood->setState(0);
    return value;
}
