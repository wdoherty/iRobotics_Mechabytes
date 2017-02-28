#include <Arduino.h>
#include <Arm.h>
#include <DriveBase.h>
#include <Intake.h>
#define baudrate 9600   // the baudrate for comms, has to match the baudrate of the driverstation
#define time_out 500    // the number of milliseconds to wait after recieving signal before calling failsafe

byte feedback[10];
byte controller[8];
byte data[8];

boolean connection;
byte x;
byte packet_index;
byte i;
byte size;
byte checkSumTX;    // check sum for transmitting data
byte checkSumRX;    // check sum for recieving data

byte driveThrottle;
byte driveHeading;
bool omniTrigger

unsigned long read_time;

#define DriveL1 2
#define DriveL2 3
#define DriveR1 4
#define DriveR2 5
#define rollers 6
#define lift 7
#define arm 8
#define wrist 9

#define omniSolenoid 15
#define doorSolenoid 16

void failsafe(){
    // write the code below that you want to run
    // when the robot loses a signal here
    arm.armFailsafe();
    intake.StopAllMotors();
    drive.driveBaseFailsafe();
    connection = false;
}

void setup(){
    //declare the serial port for comms
    //the paramater of the begin function is the baudrate
    Serial1.begin(9600);
    //initialize subsystems
    Arm arm = Arm(arm, wrist);
    DriveBase drive = DriveBase(DriveL1, DriveL2, DriveR1, DriveR2, omniSolenoid);
    Intake intake = Intake(rollers, doorSolenoid);
    // initialize the variables to 0
    memset(controller,0,sizeof(controller));
    memset(feedback,0,sizeof(feedback));
    connection = true;
    failsafe();
    read_time = millis();
    checkSumRX = 0;
    x = 0;
    packet_index = 0;
}

void loop(){
    // this while block of code might not need the "packet_index == 0" condition
    // it causes the robot to be more tolerant of old data which can be bad
    // you might want to deleting that condition
    while(packet_index == 0 && Serial1.available() >= 22){
        Serial1.read();
    }

    size = Serial1.available();

    while(size > 0){
        if(packet_index == 0){
            if(Serial1.read()==255){
                packet_index++;
            }
        }
        else if(packet_index < 9){
            data[packet_index-1] = Serial1.read();
            checkSumRX += data[packet_index-1];
            packet_index++;
        }
        else if(packet_index == 9){
            if(Serial1.read() == checkSumRX){
                packet_index++;
            }else{
                packet_index=0;
            }
            checkSumRX = 0;
        }
        else if(packet_index == 10){
            if(Serial1.read() == 240){
                for(i=0; i<8; i++){
                    controller[i] = data[i];
                }
                connection = true;
            }
            packet_index=0;
        }
        size--;
    }
    if(connection && millis() - read_time >= time_out){
        failsafe();
    }

    if(connection){
        // write the code below that you want to run
        // when the robot recieves valid data of the xbox controller
        // basically all the motor control stuff
        driveThrottle = data[3];
        driveHeading = data[4];
        omniTrigger = (1B == ((data[0] & 10000) >> 4));
        drive.updateDrive(driveThrottle, driveHeading, omniTrigger);



        // below is the code for sending feedback to the driver station

        Serial1.write(255);
        checkSumTX = 0;
        for(i=0; i<10; i++){
            Serial1.write(feedback[i]);
            checkSumTX += feedback[i];
        }
        Serial1.write(checkSumTX);
        Serial1.write(240);

        read_time = millis();
    }
}
