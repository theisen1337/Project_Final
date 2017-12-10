#include "Initialization.h"
#include <iostream>
#include "Timer.h"

//using namespace Initialization;

static bool GAME = true;
Timer Compute(1);

void MainLoop()
{
	std::cout << "\ttime: " << Initialization::computation.getRunTime() << "\tTPS: " << Initialization::computation.getTicksPerSecond() << std::endl;
	Initialization::computation.Instruction();
	if (Compute.RanOut())
	{
		std::cout << "time: " << Initialization::computation.getRunTime() << "\tTPS: " << Initialization::computation.getTicksPerSecond() << std::endl;
		Compute.setTimer(1);
	}
	
}

void render() {
}

int main()
{
	while (GAME)
	{
		MainLoop();
	}
	return 0;
}

