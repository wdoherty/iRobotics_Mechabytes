#ifndef DRIVEWHEEL_H_
#define DRIVEWHEEL_H_

class DriveWheel {
  public:
    DriveWheel(Victor drive1, Victor Drive2, Victor swerve,
               QuadEnc driveEncoder, AbsEnc swerveEncoder);

    // maps motor speed from input of [-1,1]
    // to output of full reverse to full forward
    int setSpeed(float speed);

    // sets the swerve angle, in radians, relative to
    // the front of the robot and increasing CCW
    int setAngle(float angle);

  private:
    Victor _drive1, _drive2, _swerve;
    QuadEnc _driveEncoder;
    AbsEnc _swerveEncoder;

};

#endif
