EXENAME = main
OBJS = wiringPiI2C.o wiringPi.o wiringSerial.o PCA9685.o Controller.o Controller_vars.o Victor.o SinglePiston.o DoublePiston.o BowlingBallIntake.o BasketballShooter.o BasketballIntake.o Backpack.o SimonSays.o TankDrive.o SubsystemManager.o main.o vision.o


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
	$(CXX) $(OPENCVFLAGS) main.cpp

SubsystemManager.o : SubsystemManager/SubsystemManager.cpp SubsystemManager/SubsystemManager.h TankDrive/TankDrive.h  SimonSays/SimonSays.h BowlingBallIntake/BowlingBallIntake.h BasketballShooter/BasketballShooter.h BasketballIntake/BasketballIntake.h Backpack/Backpack.h ../StandardLibraries/DoublePiston/DoublePiston.h ../StandardLibraries/SinglePiston/SinglePiston.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/Victor/Victor.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) SubsystemManager/SubsystemManager.cpp

TankDrive.o : TankDrive/TankDrive.cpp TankDrive/TankDrive.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/Victor/Victor.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) TankDrive/TankDrive.cpp

SimonSays.o : SimonSays/SimonSays.cpp SimonSays/SimonSays.h ../StandardLibraries/SinglePiston/SinglePiston.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h
	$(CXX) $(CXXFLAGS) SimonSays/SimonSays.cpp

BowlingBallIntake.o : BowlingBallIntake/BowlingBallIntake.cpp BowlingBallIntake/BowlingBallIntake.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/Victor/Victor.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) BowlingBallIntake/BowlingBallIntake.cpp

BasketballShooter.o : BasketballShooter/BasketballShooter.cpp BasketballShooter/BasketballShooter.h ../StandardLibraries/SinglePiston/SinglePiston.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/Victor/Victor.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) BasketballShooter/BasketballShooter.cpp

BasketballIntake.o : BasketballIntake/BasketballIntake.cpp BasketballIntake/BasketballIntake.h ../StandardLibraries/SinglePiston/SinglePiston.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/Victor/Victor.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) BasketballIntake/BasketballIntake.cpp

Backpack.o : Backpack/Backpack.cpp Backpack/Backpack.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/Victor/Victor.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) Backpack/Backpack.cpp

DoublePiston.o : ../StandardLibraries/DoublePiston/DoublePiston.cpp ../StandardLibraries/DoublePiston/DoublePiston.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h
	$(CXX) $(CXXFLAGS) ../StandardLibraries/DoublePiston/DoublePiston.cpp

SinglePiston.o : ../StandardLibraries/SinglePiston/SinglePiston.cpp ../StandardLibraries/SinglePiston/SinglePiston.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPi.h
	$(CXX) $(CXXFLAGS) ../StandardLibraries/SinglePiston/SinglePiston.cpp

Victor.o : ../StandardLibraries/Victor/Victor.cpp ../StandardLibraries/Victor/Victor.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) ../StandardLibraries/Victor/Victor.cpp

Controller_vars.o : ../StandardLibraries/Controller/Controller_vars.cpp ../StandardLibraries/Controller/Controller_vars.h
	$(CXX) $(CXXFLAGS) ../StandardLibraries/Controller/Controller_vars.cpp

Controller.o : ../StandardLibraries/Controller/Controller.cpp ../StandardLibraries/Controller/Controller.h
	$(CXX) $(CXXFLAGS) ../StandardLibraries/Controller/Controller.cpp

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
