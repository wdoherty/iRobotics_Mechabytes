#ifndef ROBOTVISION_H
#define ROBOTVISION_H

/*

  Header file for robot vision for 2018 Mechabytes MRDC team

  Contributers: Jason Raether, Marco Palella

*/

class RobotVision{


public:

  RobotVision(); //Constructor

  ~RobotVision(); //Destructor

private:

  void streamVideo(); //Sends video stream from Raspberry Pi to laptop

  void checkLight(); //Detects which button is lit up on Simon Say's board

  void centerBoard(); //Centers camera on Simon Say's board

  void trackMovement(); //Camera follows closest/first moving object

};

#endif