#include "SubsystemManager/SubsystemManager.h"
#include "TestSubsystem/TestSubsystem.h"
#include "../StandardLibraries/wiringPiLib/wiringPi/wiringSerial.h"
#include "../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h"
#include "RobotVision/vision.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include "../StandardLibraries/AnalogSensor/AnalogSensor.h"
#include "../StandardLibraries/DigitalSensor/DigitalSensor.h"

// #define baudrate 9600   // the baudrate for comms, has to match the baudrate of the driverstation
#define time_out 500    // the number of milliseconds to wait after recieving signal before calling failsafe

using namespace std;

//function for halting all motor output in case of comms loss
void failsafe(SubsystemManager* subsystems){
    // write the code below that you want to run
    // when the robot loses a signal here
    subsystems->failsafe();
    connection = false;
}

int main()
{
  //initializes digital IO
	wiringPiSetupGpio();

    // creates the subsystems for the robot and sets initial states
    SubsystemManager* Robot = new SubsystemManager();
    Robot->initializeSubsystems();

	cout << "init complete" << endl;

}
