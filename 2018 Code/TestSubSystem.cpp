#include "TestSubSystem.h"

TestSubSystem::TestSubSystem(PCA9685& output): device(output){
    Victor throttle(output, 0);
    throttle.setThrottle(255);
}
