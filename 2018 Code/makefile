EXENAME = main
OBJS = wiringPiI2C.o PCA9685.o Victor.o TestSubsystem.o SubsystemManager.o main.o

CXX = g++
CXXFLAGS = -Wall -c -lwiringPi
LD = g++
LDFLAGS = -Wall -lwiringPi

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp SubsystemManager/SubsystemManager.h
	$(CXX) $(CXXFLAGS) main.cpp

SubsystemManager.o : SubsystemManager/SubsystemManager.cpp SubsystemManager/SubsystemManager.h TestSubsystem/TestSubsystem.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/Victor/Victor.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) SubsystemManager/SubsystemManager.cpp

TestSubsystem.o : TestSubsystem/TestSubsystem.cpp TestSubsystem/TestSubsystem.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/Victor/Victor.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) TestSubsystem/TestSubsystem.cpp

Victor.o : ../StandardLibraries/Victor/Victor.cpp ../StandardLibraries/Victor/Victor.h ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) ../StandardLibraries/Victor/Victor.cpp

PCA9685.o : ../StandardLibraries/PCA9685/PCA9685.cpp ../StandardLibraries/PCA9685/PCA9685.h ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) ../StandardLibraries/PCA9685/PCA9685.cpp

wiringPiI2C.o : ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.c ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.h
	$(CXX) $(CXXFLAGS) ../StandardLibraries/wiringPiLib/wiringPi/wiringPiI2C.c

clean :
	-rm -f *.o $(EXENAME)
