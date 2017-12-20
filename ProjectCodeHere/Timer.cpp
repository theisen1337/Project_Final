
#include "Timer.h"
#include "Computation.h"


Timer::Timer(int time)
{
	StartTime = Computation::getGameTime();
	TimeEnd = time + StartTime;
}

Timer::Timer(float time)
{
	StartTime = Computation::getGameTime();
	TimeEnd = time + StartTime;
}

bool Timer::RanOut()
{
	return (Computation::getGameTime() - TimeEnd) <= 0;
}

float Timer::TimeLeft()
{
	return Computation::getGameTime() - TimeEnd;
}


Timer::~Timer()
{
}
