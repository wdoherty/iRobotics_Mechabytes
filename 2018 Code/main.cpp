#include "SubsystemManager/SubsystemManager.h"

int main()
{
	SubsystemManager* Robot = new SubsystemManager();
	Robot->initializeSubsystems();
	
	while(true)
	{
		Robot->runRobot();
	}
}
