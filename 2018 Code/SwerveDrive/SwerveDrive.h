#ifndef SWERVEDRIVE_H_
#define SWERVEDRIVE_H_

class SwerveDrive {
  public:
    SwerveDrive(DriveWheel frontLeft, DriveWheel frontRight, DriveWheel backLeft, DriveWheel backRight);

    // Overloaded methods to
    // Option 1: set wheel speeds and angles based on linear and angular velocity vectors (i.e. autonomous)
    // Option 2: set wheel speeds and angles based on controller input (i.e. driver control)
    //              leftStickX  --> Left/Right          (strafe)
    //              leftStickY  --> Forward/Backward    (drive)
    //              rightStickX --> Rotation            (turn)
    setDrive(float[2] velocity, float omega);
    setDrive(float leftStickX, float leftStickY, float rightStickX);

  private:
    DriveWheel _frontLeft, _frontRight, _BackLeft, _BackRight;
    float[2] _velocity;
    float _omega;
};

#endif
