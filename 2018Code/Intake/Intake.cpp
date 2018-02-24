#include "intake.h"

Intake::Intake(PCA9685* PWM, int foamPin, int soccerPin) : controller(PWM)
{
    _foamPin = foamPin;
    _soccerPin = soccerPin;
    foamIntake = new Victor(controller, 4);
    soccerIntake = new Victor(controller, 5);
}

void Intake::runIntake(int foamTrigger, int soccerTrigger)
{
    //Driver must hold button down to use Intake
    //Soccer gets priority, always
    if(soccerTrigger == 1)
    {
        foamIntake->setThrottle(0); //run the foam ball intake in reverse: soccer balls are in contact with it
        soccerIntake->setThrottle(4095); //run main soccer intake in
    }
    else if(foamTrigger == 1)
    {
        foamIntake->setThrottle(4095); //run the foam ball intake in
        soccerIntake->setThrottle(4095/2); //stop soccer intake
    }
    else
    {
        foamIntake->setThrottle(4095/2); //stop foam intake
        soccerIntake->setThrottle(4095/2); //stop soccer intake
    }
}
