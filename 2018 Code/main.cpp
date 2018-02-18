#include "SubsystemManager/SubsystemManager.h"
#include "TestSubsystem/TestSubsystem.h"

int main()
{
	SubsystemManager* Robot = new SubsystemManager();
	
	Robot->initializeSubsystems();
	while(true)
	{
		Robot->runRobot();
	}
}
