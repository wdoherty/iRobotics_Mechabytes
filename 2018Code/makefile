EXENAME = main
OBJS = wiringPiI2C.o wiringPi.o wiringSerial.o PCA9685.o Victor.o SinglePiston.o DoublePiston.o Arm.o Intake.o SimonSays.o SoccerOutput.o TankDrive.o TestSubsystem.o SubsystemManager.o main.o vision.o


CXX = clang++
CXXFLAGS = -Wall -c
OPENCVFLAGS = -Wall -c -std=c++11
LD = clang++

LDFLAGS = -Wall -lwiringPi -lpthread
OPENCV = $(shell pkg-config --libs --static opencv)

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OPENCV) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp SubsystemManager/SubsystemManager.h ../StandardLibraries/wiringPiLib/wiringPi/wiringSerial.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h
	$(CXX) $(CXXFLAGS) main.cpp

SubsystemManager.o : SubsystemManager/SubsystemManager.cpp SubsystemManager/SubsystemManager.h TestSubsystem/TestSubsystem.h TankDrive/TankDrive.h SoccerOutput/SoccerOutput.h SimonSays/SimonSays.h Intake/Intake.h Arm/Arm.h ../StandardLibraries/DoublePiston/DoublePiston.h ../StandardLibraries/SinglePiston/SinglePiston.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/Victor/Victor.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) SubsystemManager/SubsystemManager.cpp

TestSubsystem.o : TestSubsystem/TestSubsystem.cpp TestSubsystem/TestSubsystem.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/Victor/Victor.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) TestSubsystem/TestSubsystem.cpp

TankDrive.o : TankDrive/TankDrive.cpp TankDrive/TankDrive.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/Victor/Victor.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) TankDrive/TankDrive.cpp

SoccerOutput.o : SoccerOutput/SoccerOutput.cpp SoccerOutput/SoccerOutput.h ../StandardLibraries/SinglePiston/SinglePiston.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h
	$(CXX) $(CXXFLAGS) SoccerOutput/SoccerOutput.cpp

SimonSays.o : SimonSays/SimonSays.cpp SimonSays/SimonSays.h ../StandardLibraries/DoublePiston/DoublePiston.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/Victor/Victor.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) SimonSays/SimonSays.cpp

Intake.o : Intake/Intake.cpp Intake/Intake.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/Victor/Victor.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) Intake/Intake.cpp

Arm.o : Arm/Arm.cpp Arm/Arm.h ../StandardLibraries/SinglePiston/SinglePiston.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/Victor/Victor.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) Arm/Arm.cpp

DoublePiston.o : ../StandardLibraries/DoublePiston/DoublePiston.cpp ../StandardLibraries/DoublePiston/DoublePiston.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h
	$(CXX) $(CXXFLAGS) ../StandardLibraries/DoublePiston/DoublePiston.cpp

SinglePiston.o : ../StandardLibraries/SinglePiston/SinglePiston.cpp ../StandardLibraries/SinglePiston/SinglePiston.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h
	$(CXX) $(CXXFLAGS) ../StandardLibraries/SinglePiston/SinglePiston.cpp

Victor.o : ../StandardLibraries/Victor/Victor.cpp ../StandardLibraries/Victor/Victor.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) ../StandardLibraries/Victor/Victor.cpp

PCA9685.o : ../StandardLibraries/PCA9685/PCA9685.cpp ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) ../StandardLibraries/PCA9685/PCA9685.cpp

wiringSerial.o : ../StandardLibraries/wiringPiLib/wiringPi/wiringSerial.c ../StandardLibraries/wiringPiLib/wiringPi/wiringSerial.h
	$(CXX) $(CXXFLAGS) ../StandardLibraries/wiringPiLib/wiringPi/wiringSerial.c

wiringPi.o : ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.c ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h
	$(CXX) $(CXXFLAGS) ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.c

wiringPiI2C.o : ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.c ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.c

vision.o : RobotVision/vision.cpp RobotVision/vision.h
	$(CXX) $(OPENCVFLAGS) RobotVision/vision.cpp

clean :
	-rm -f *.o $(EXENAME)
