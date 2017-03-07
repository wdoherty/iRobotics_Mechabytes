//#include <Arduino.h>
//#include <Arm.h>
//#include <DriveBase.h>
#include <Intake.h>
#include <Servo.h>
#define baudrate 9600   // the baudrate for comms, has to match the baudrate of the driverstation
#define time_out 500    // the number of milliseconds to wait after recieving signal before calling failsafe

byte feedback[10];
byte controller[8];
byte data[8];

boolean connection;
boolean badPacket;
byte x;
byte packet_index;
byte i;
byte size1;
byte checkSumTX;    // check sum for transmitting data
byte checkSumRX;    // check sum for recieving data

byte driveThrottle; //drive variables
byte driveHeading;
bool omniTrigger;

int _lStickY;
int _rStickX;

bool doorTrigger;   //intake variables
bool intakeTrigger;
bool scoreTrigger;
bool prevState = false;
bool piston_out = false;

int _PISTON;

byte lTrigger;      //arm variables
byte rTrigger;
bool clawCW;
bool clawCCW;

unsigned long read_time;

#define DriveML1 2
#define DriveML2 3
#define DriveMR1 4
#define DriveMR2 5
#define rollers 6
#define lift 7
#define armMotor 8
#define wrist 9

#define doorSolenoid 16
//#define compressorPin 30

  Servo DriveL1;
  Servo DriveL2;
  Servo DriveR1;
  Servo DriveR2;

  Servo intake1;

  Servo ArmMotor;
  Servo WristMotor;

//Arm arm(armMotor, wrist);
//Intake intake(rollers, doorSolenoid);
//DriveBase drive(DriveL1, DriveL2, DriveR1, DriveR2, omniSolenoid);
//DriveBase drive(7, DriveL2, DriveR1, DriveR2, omniSolenoid);
//Servo testMotor;

void failsafe(){
    // write the code below that you want to run
    // when the robot loses a signal here
    driveBaseFailsafe();
    IntakeFailsafe();
    armFailsafe();
//    digitalWrite(compressorPin, LOW);
    connection = false;
}

void setup(){
    //declare the Serial1 port for comms
    //the paramater of the begin function is the baudrate
//    Serial.begin(9600);
    Serial1.begin(9600);
    // initialize the variables to 0
    memset(controller,0,sizeof(controller));
    memset(feedback,0,sizeof(feedback));
    connection = true;

    //subsystem initialization
    DriveBaseInit(DriveML1, DriveML2, DriveMR1, DriveMR2);
    IntakeInit(rollers, doorSolenoid);
    ArmInit(armMotor, wrist);
//    pinMode(compressorPin, OUTPUT);
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
    connection = false;
    badPacket = false;
    while(packet_index == 0 && Serial1.available() >= 22){
        Serial1.read();
    }

    size1 = Serial1.available();
    while(size1 > 0){
//      Serial1.write(0);
        if(packet_index == 0){
            if(Serial1.read()==255){
//              Serial1.write(1);
                packet_index++;
            }
            else badPacket = true; // may have to take out later
        }
        else if(packet_index < 9){
//           Serial1.write(2);
            data[packet_index-1] = Serial1.read();
            checkSumRX += data[packet_index-1];
            packet_index++;
        }
        else if(packet_index == 9){
//           Serial1.write(3);
           Serial1.write(checkSumRX);
            if(Serial1.read() == checkSumRX){
//              Serial1.write(4);
                packet_index++;
            }else{
                packet_index=0;
            }
            checkSumRX = 0;
        }
        else if(packet_index == 10){
            if(Serial1.read() == 240){
//              Serial1.write(5);
                for(i=0; i<8; i++){
                    controller[i] = data[i];
                }
                connection = true;
                 read_time = millis();
            }
            else badPacket = true; //may have to take out later
            packet_index=0;
        }
        size1--;
    }
    if((connection && millis() - read_time >= time_out) || badPacket){
//        Serial1.write(7);
        failsafe();
    }

    if(connection){
        // write the code below that you want to run
        // when the robot recieves valid data of the xbox controller
        // basically all the motor control stuff
//        Serial1.write(6);
//        testMotor.write(180);
        driveThrottle = data[3];
        driveHeading = data[4];
        omniTrigger = (B1 == ((data[0] & B10000) >> 4));
//        Serial1.write(driveThrottle);
        updateDrive(driveThrottle, driveHeading);
        
//        if(driveThrottle == B11111111) testMotor.write(180);
//        
//        else if(driveThrottle == B00001111) testMotor.write(0);
//        else testMotor.write(90);

        intakeTrigger = (B1 == ((data[0] & B100000) >> 5));
        doorTrigger = (B1 == ((data[0] & B1000) >> 3));
        scoreTrigger = (B1 == ((data[0] & B10) >> 1));
        runIntake(scoreTrigger, intakeTrigger, doorTrigger);
        
//        digitalWrite(doorSolenoid, doorTrigger?HIGH:LOW);
        
        lTrigger = data[6];
        rTrigger = data[7];
        clawCW = (B1 == ((data[0] & B100) >> 2));
        clawCCW = (B1 == ((data[0] & B1) ));
        setArm(lTrigger, rTrigger, clawCW, clawCCW);

        // below is the code for sending feedback to the driver station
        feedback[4] = 0;
        feedback[5] = 0;
        feedback[6] = 0;
        feedback[7] = 0;
        feedback[8] = 0;
        feedback[9] = 0;

        Serial1.write(255);
        checkSumTX = 0;
        for(i=0; i<10; i++){
            Serial1.write(feedback[i]);
            checkSumTX += feedback[i];
        }
        Serial1.write(checkSumTX);
        Serial1.write(240);
    }
}

//DriveBase subsystem
void DriveBaseInit(int leftPWM1, int leftPWM2, int rightPWM1, int rightPWM2)
{
//subsystem setup, assigns pin number and initializes pin
  DriveL1.attach(leftPWM1);
  DriveL2.attach(leftPWM2);
  DriveR1.attach(rightPWM1);
  DriveR2.attach(rightPWM2);
}

void driveBaseFailsafe()
{
  DriveL1.write(90);
  DriveL2.write(90);
  DriveR1.write(90);
  DriveR2.write(90);
}

void setThrottle(int _lStickY, int _rStickX)
{

   int throttle = abs(_lStickY-90) * (_lStickY < 90 ? -1 : 1);    //// = magnitude & direction of throttle
   int heading = abs(_rStickX-90) * (_rStickX < 90 ? -1 : 1);    //// = magnitude and direction of heading

//   Serial.println(_lStickY);
//   Serial1.write(throttle);
//   Serial1.write(heading);
//   Serial.println(throttle);
//   Serial.println(heading);
   
   int lSpeed = (throttle + heading) + 90;
   int rSpeed = throttle - heading + 90;
 

// int lSpeed = ( _lStickY +  _rStickX);
// int rSpeed = ( _lStickY -  _rStickX);

// if(abs(lSpeed - 90) < 5) lSpeed = 90;
// if(abs(rSpeed - 90) < 5) rSpeed = 90;

//constrains motor values to within the PWM limits

// if(lSpeed > 180) lSpeed = 180;
// if(lSpeed < 0) lSpeed = 0;
// if(rSpeed > 180) rSpeed = 180;
// if(rSpeed < 0) rSpeed = 0;

//sends value to speed controller
//  Serial1.write(lSpeed);
//  Serial1.write(rSpeed);
//  Serial.println(lSpeed);
//  Serial.println(rSpeed);

feedback[0] = (byte)lSpeed;
feedback[1] = (byte)rSpeed;
  
  DriveL1.write(lSpeed);
  DriveL2.write(lSpeed);
  DriveR1.write(rSpeed);
  DriveR2.write(rSpeed);
}

void updateDrive(byte lStickY, byte rStickX)
{
//run every cycle to set drive motor value and piston state
//lStickY assigns throttle, rStickX assigns rotation,
//propToggle sets omni wheel position

feedback[2] = lStickY;
feedback[3] = rStickX;

  _lStickY = ((lStickY)*180/200) & B11111111;
  _rStickX = ((rStickX)*180/200) & B11111111;

//  Serial.println(lStickY);
//  Serial.println(_lStickY);

//deadband control to prevent non-significant power output
  if(_lStickY > 80 && _lStickY < 100) _lStickY = 90;
  if(_rStickX > 80 && _rStickX < 100) _rStickX = 90;
//  Serial1.write(_lStickY);
//  Serial1.write(_rStickX);
  setThrottle(_lStickY, _rStickX);
}

//intake subsystem
void IntakeInit(int PWM, int pistonIO)
{
//subsystem setup, assigns pin number and initializes pin
  
  int _PWM = PWM;
  _PISTON = pistonIO;
  pinMode(_PISTON, OUTPUT);//pin for piston control
  // pinMode(_PWM, OUTPUT);
  intake1.attach(_PWM);
}

void setIntakeSpeed(int state)
{
//for input -1, 0, 1, sets speed to full forward, full reverse, or off

  int IntakeSpeed = (90 * state) + 90;

//sends value to speed controller
  intake1.write(IntakeSpeed);
  // analogWrite(_PWM, speed);
}

void runPiston(bool piston)//accepts piston as state of button
{
    digitalWrite(_PISTON, piston?HIGH:LOW);//send 'pressed' to _PISTON
}

void IntakeFailsafe()
{
  // analogWrite(_PWM, 0);
  intake1.write(90);
}

void runIntake(bool lTrigger, bool rTrigger, bool piston)
{
//if left trigger held, run intake out
//if right trigger held, run intake in
//right trigger takes priority
if(rTrigger)
{
  setIntakeSpeed(1);//run intake in
}
else if(lTrigger)
{
  setIntakeSpeed(-1);//run intake out
}
else setIntakeSpeed(0);//do nothing

if(piston && piston != prevState)
{
  runPiston(!piston_out);
  piston_out = !piston_out;
  prevState = piston;
}
else if(!piston)
{
  prevState = piston;
}
}

//arm subsystem
void ArmInit(int armPWM, int wristPWM)
{
//subsystem setup, assigns pin number and initializes pin

  int _PWM1 = armPWM;
  int _PWM2 = wristPWM;

  ArmMotor.attach(_PWM1);
  WristMotor.attach(_PWM2);
}

void setArmSpeed(byte _lTrigger, byte _rTrigger)
{
//for input -1, 0, 1, sets speed to half forward, half reverse, or off
  int armSpeed = (127 + (int) _rTrigger - (int) _lTrigger)*(180/255);
  if(abs(90 - armSpeed) < 10) armSpeed = 90;

//sends value to speed controller
  ArmMotor.write(armSpeed);
}

void setWristSpeed(int state)
{
//for input -1, 0, 1, sets speed to half forward, half reverse, or off
  int wristSpeed = (50 * state) + 90;

  //sends value to speed controller
  WristMotor.write(wristSpeed);
}

void armFailsafe()
{
  ArmMotor.write(90);
  WristMotor.write(90);
}

void setArm(byte lTrigger, byte rTrigger, bool rButton, bool lButton)
{
//if left trigger held, run intake out
//if right trigger held, run intake in
//right trigger takes priority

// if(rTrigger) setArmSpeed();
// else if(lTrigger) setArmSpeed(-1);
// else setArmSpeed(0);
setArmSpeed((lTrigger >> 1), (rTrigger >> 1));

if(rButton) setWristSpeed(1);
else if(lButton) setWristSpeed(-1);
else setWristSpeed(0);
}
