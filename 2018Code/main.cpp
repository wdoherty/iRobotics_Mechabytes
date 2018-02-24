#include "SubsystemManager/SubsystemManager.h"
#include "TestSubsystem/TestSubsystem.h"
#include "../StandardLibraries/wiringPiLib/wiringPi/wiringSerial.h"
#include "../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h"
#include <string.h>

#define baudrate 9600   // the baudrate for comms, has to match the baudrate of the driverstation
#define time_out 500    // the number of milliseconds to wait after recieving signal before calling failsafe

#define DriveL1 2
#define DriveL2 3
#define DriveR1 4
#define DriveR2 5
#define rollers 6
#define lift 7
#define armMotor 8
#define wrist 9

#define omniSolenoid 15
#define doorSolenoid 16

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

unsigned long read_time;

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
	wiringPiSetupGpio();

	int serialId = serialOpen("/dev/ttyS0", baudrate);

	memset(controller,0,sizeof(controller));
    memset(feedback,0,sizeof(feedback));
    connection = true;

	failsafe();
	read_time = millis();
	checkSumRX = 0;
	x = 0;
	packet_index = 0;

	SubsystemManager* Robot = new SubsystemManager();

	Robot->initializeSubsystems();

	while(true)
	{
		//Robot->runRobot();

        connection = false;
        while(packet_index == 0 && serialDataAvail(serialId) >= 22){
            serialGetChar(serialId);
        }

        size1 = serialDataAvail(serialId);
        while(size1 > 0){
            if(packet_index == 0){
                if(serialGetChar(serialId)==255){
                    packet_index++;
                }
            }
            else if(packet_index < 9){
                data[packet_index-1] = serialGetChar(serialId);
                checkSumRX += data[packet_index-1];
                packet_index++;
            }
            else if(packet_index == 9){
                if(serialGetChar(serialId) == checkSumRX){
                    packet_index++;
                }else{
                    packet_index=0;
                }
                checkSumRX = 0;
            }
            else if(packet_index == 10){
                if(serialGetChar(serialId) == 240){
                    for(i=0; i<8; i++){
                        controller[i] = data[i];
                    }
                    connection = true;
                    read_time = millis();
                }
                packet_index=0;
            }
            size1--;
        }
        if(connection && millis() - read_time >= time_out){
            failsafe();
        }

        if(connection){
            // write the code below that you want to run
            // when the robot recieves valid data of the xbox controller
            // basically all the motor control stuff
            // Serial1.write(6);
/*            testMotor.write(180);
            driveThrottle = data[3];
            driveHeading = data[4];
            omniTrigger = (B1 == ((data[0] & B10000) >> 4));
    //        drive.updateDrive(driveThrottle, driveHeading, omniTrigger);

            intakeTrigger = (B1 == ((data[0] & B100000) >> 5));
            doorTrigger = (B1 == ((data[0] & B1000) >> 3));
            scoreTrigger = (B1 == ((data[0] & B10) >> 1));
    //        intake.runIntake(scoreTrigger, intakeTrigger, doorTrigger);

            lTrigger = data[6];
            rTrigger = data[7];
            clawCW = (B1 == ((data[0] & B100) >> 2));
            clawCCW = (B1 == ((data[0] & B1) ));
    //        arm.setArm(lTrigger, rTrigger, clawCW, clawCCW);

            // below is the code for sending feedback to the driver station
*/
            serialPutchar(serialId, 255);
            checkSumTX = 0;
            for(i=0; i<10; i++){
                serialPutchar(serialId, feedback[i]);
                checkSumTX += feedback[i];
            }
            serialPutchar(serialId, checkSumTX);
            serialPutchar(serialId, 240);
        }
	}
}
