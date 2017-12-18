
#include "Timer.h"
#include "Computation.h"


Timer::Timer(int time)
{
	StartTime = Computation::getRunTime();
	TimeEnd = time;
}

Timer::Timer(float time)
{
	StartTime = Computation::getRunTime();
	TimeEnd = time;
}



Timer::~Timer()
{
}
