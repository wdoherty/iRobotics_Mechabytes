#include "SubsystemManager/SubsystemManager.h"
#include "TestSubsystem/TestSubsystem.h"
#include "../StandardLibraries/wiringPiLib/wiringPi/wiringSerial.h"
#include <string.h>

#define baudrate 9600   // the baudrate for comms, has to match the baudrate of the driverstation
#define time_out 500    // the number of milliseconds to wait after recieving signal before calling failsafe

char feedback[10];
char controller[8];
char data[8];

bool connection;
char x;
char packet_index;
char i;
char size1;
char checkSumTX;    // check sum for transmitting data
char checkSumRX;    // check sum for recieving data

void failsafe(){
    // write the code below that you want to run
    // when the robot loses a signal here
//    arm.armFailsafe();
//    intake.StopAllMotors();
//    drive.driveBaseFailsafe();
//testMotor.write(180);
    connection = false;
}

int main()
{
//Serial init
	int serialId = serialOpen("/dev/ttyS0", baudrate);

	memset(controller,0,sizeof(controller));
    memset(feedback,0,sizeof(feedback));
    connection = true;

	SubsystemManager* Robot = new SubsystemManager();

	Robot->initializeSubsystems();
	while(true)
	{
		Robot->runRobot();
	}
}
