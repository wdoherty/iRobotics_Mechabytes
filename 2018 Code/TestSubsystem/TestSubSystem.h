#ifndef TEST_SUBSYSTEM
#define TEST_SUBSYSTEM

#include "Victor.h"

#include "PCA9685.h"

class TestSubSystem
{
public:
    TestSubSystem(PCA9685& output);
private:
    PCA9685& device;
};

#endif
