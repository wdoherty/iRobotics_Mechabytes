# 1 "c:\\users\\billy\\appdata\\local\\temp\\tmpejegv9"
#include <Arduino.h>
# 1 "C:/Users/Billy/Desktop/Mechabytes/RobotCode/src/main.ino"
#include <Arduino.h>
#include <Arm.h>
#include <DriveBase.h>
#include <Intake.h>
#define baudrate 9600
#define time_out 500

byte feedback[10];
byte controller[8];
byte data[8];

boolean connection;
byte x;
byte packet_index;
byte i;
byte size;
byte checkSumTX;
byte checkSumRX;

byte driveThrottle;
byte driveHeading;
bool omniTrigger;

bool doorTrigger;
bool intakeTrigger;
bool scoreTrigger;

byte lTrigger;
byte rTrigger;
bool clawCW;
bool clawCCW;

unsigned long read_time;

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

Arm arm(armMotor, wrist);
Intake intake(rollers, doorSolenoid);
DriveBase drive(DriveL1, DriveL2, DriveR1, DriveR2, omniSolenoid);
void failsafe();
void setup();
void loop();
#line 51 "C:/Users/Billy/Desktop/Mechabytes/RobotCode/src/main.ino"
void failsafe(){


    arm.armFailsafe();
    intake.StopAllMotors();
    drive.driveBaseFailsafe();
    connection = false;
}

void setup(){


    Serial1.begin(9600);





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



        driveThrottle = data[3];
        driveHeading = data[4];
        omniTrigger = (B1 == ((data[0] & B10000) >> 4));
        drive.updateDrive(driveThrottle, driveHeading, omniTrigger);

        intakeTrigger = (B1 == ((data[0] & B100000) >> 5));
        doorTrigger = (B1 == ((data[0] & B1000) >> 3));
        scoreTrigger = (B1 == ((data[0] & B10) >> 1));
        intake.runIntake(scoreTrigger, intakeTrigger, doorTrigger);

        lTrigger = data[6];
        rTrigger = data[7];
        clawCW = (B1 == ((data[0] & B100) >> 2));
        clawCCW = (B1 == ((data[0] & B1) ));
        arm.setArm(lTrigger, rTrigger, clawCW, clawCCW);



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