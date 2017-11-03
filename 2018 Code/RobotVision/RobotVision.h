#ifndef ROBOTVISION_H
#define ROBOTVISION_H

/*

  Header file for robot vision for 2018 Mechabytes MRDC team

  Contributers: Jason Raether

*/

class RobotVision{


public:

  RobotVision(); //Constructor
  ~RobotVision(); //Destructor

private:

  void checkLight(); //Function to detect which button is lit up on Simon Say's board

  void centerBoard(); //Centers camera on Simon Say's board

  void trackMovement(); //Camera follows closest/first moving object

};

#endif
