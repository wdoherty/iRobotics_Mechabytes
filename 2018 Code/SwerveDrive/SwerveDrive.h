#ifndef SWERVEDRIVE_H
#define SWERVEDRIVE_H

#include <cstdint>

class SwerveDrive
{
public:
  SwerveDrive(int FLDrivePWM, int FRDrivePWM, int BLDrivePWM, int BRDrivePWM,
              int FLRotatePWM, int FRRotatePWM, int BLRotatePWM, int BRRotatePWM,
              int FLQuad, int FRQuad, int BLQuad, int BRQuad,
              int FLAbs, int FRAbs, int BLAbs, int BRAbs);
  updateDrive(uint8_t lStickX, uint8_t lStickY, uint8_t rStickX);

private:

};


#endif
