#include "Intake.h"

Intake::Intake(PCA9685* PWM, int foamPin, int soccerPin) : controller(PWM)
{
    _foamPin = foamPin;
    _soccerPin = soccerPin;
    foamIntake = new Victor(controller, _foamPin);
    soccerIntake = new Victor(controller, _soccerPin);
}

void Intake::failsafe()
{
        foamIntake->setThrottle(2185); //stop foam intake
        soccerIntake->setThrottle(2185); //stop soccer intake
}

unsigned char Intake::updateIntake(unsigned char foamTrigger, unsigned char soccerTrigger)
{
    //Driver must hold button down to use Intake
    //Soccer gets priority, always

    value = 0;

    if((int)soccerTrigger == 1)
    {
        foamIntake->setThrottle(1785); //run the foam ball intake in reverse: soccer balls are in contact with it
        soccerIntake->setThrottle(2585); //run main soccer intake in
        value = 2;  // binary 0
    }
    else if((int)foamTrigger == 1)
    {
        foamIntake->setThrottle(2585); //run the foam ball intake in
        soccerIntake->setThrottle(2185); //stop soccer intake
        value = 1;
    }
    else
    {
        foamIntake->setThrottle(2185); //stop foam intake
        soccerIntake->setThrottle(2185); //stop soccer intake
    }
    return value;
}
