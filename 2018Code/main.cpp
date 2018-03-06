#include "SubsystemManager/SubsystemManager.h"
#include "TestSubsystem/TestSubsystem.h"
#include "../StandardLibraries/wiringPiLib/wiringPi/wiringSerial.h"
#include "../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h"
#include "RobotVision/vision.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#define baudrate 9600   // the baudrate for comms, has to match the baudrate of the driverstation
#define time_out 500    // the number of milliseconds to wait after recieving signal before calling failsafe

using namespace std;

// #define DriveL1 2
// #define DriveL2 3
// #define DriveR1 4
// #define DriveR2 5
// #define rollers 6
// #define lift 7
// #define armMotor 8
// #define wrist 9
//
// #define omniSolenoid 15
// #define doorSolenoid 16

unsigned char feedback[10];
unsigned char controller[8];
unsigned char data[8];

bool connection;
bool badPacket;
unsigned char x;
unsigned char packet_index;
unsigned char i;
unsigned char size1;
unsigned char checkSumTX;    // check sum for transmitting data
unsigned char checkSumRX;    // check sum for recieving data

unsigned long read_time;

void failsafe(SubsystemManager* subsystems){
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
	wiringPiSetup();

	int serialId = serialOpen("/dev/ttyS0", 9600);
    cout << serialId << endl;

	memset(controller,0,sizeof(controller));
    memset(feedback,0,sizeof(feedback));
    connection = true;

    SubsystemManager* Robot = new SubsystemManager();
    Robot->initializeSubsystems();
    //Vision *v = new Vision();

	failsafe(Robot);
	read_time = millis();
	checkSumRX = 0;
	x = 0;
	packet_index = 0;

	cout << "init complete" << endl;
	while(true)
	{
		//Robot->runRobot();
		/*if(v->checkBoard()){
			std::cout << "Found board." << std::endl;
			cout << v->analyzeBoard() << endl;
			usleep(3000000); //3 seconds
		}*/
		// cout << "loop start" << endl;
        connection = false;
        while(packet_index == 0 && serialDataAvail(serialId) >= 22){
            serialGetchar(serialId);
            //cout << "dump extra" << endl;
        }

        size1 = serialDataAvail(serialId);
        while(size1 > 0){
            //cout << "Inside size1 loop" << endl;
            if(packet_index == 0){
                //cout << "0" << endl;
                if(serialGetchar(serialId)==255){
                    packet_index++;
                    //cout << "valid lead bit" << endl;
                }
            }
            else if(packet_index < 9){
                data[packet_index-1] = serialGetchar(serialId);
                checkSumRX += data[packet_index-1];
                //cout << packet_index << endl;
                packet_index++;
            }
            else if(packet_index == 9){
                if(serialGetchar(serialId) == checkSumRX){
                    packet_index++;
                }else{
                    packet_index=0;
                }
                checkSumRX = 0;
            }
            else if(packet_index == 10){
                //cout << "10" << endl;
                if(serialGetchar(serialId) == 240){
                    //cout << "valid end bit" << endl;
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
            failsafe(Robot);
        }

        if(connection){
            // write the code below that you want to run
            // when the robot recieves valid data of the xbox controller
            // basically all the motor control stuff
            //after getting valid input, execute main code
            //cout << "Run Robot" << endl;
            Robot->runRobot(controller);

// below is the code for sending feedback to the driver station
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
