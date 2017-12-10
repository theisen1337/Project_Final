
#include "Timer.h"
#include "Initialization.h"
#include <chrono>

#include <iostream>

//using namespace Initialization;

Timer::Timer(int time)
{
	Timer::setStartTime();
	Timer::setTimer(time);
}

Timer::Timer(float time)
{
	Timer::setStartTime();
	Timer::setTimer(time);
}

void Timer::setTimer(int time)
{
	Timer::TimeEnd = time * 1.0f + Initialization::computation.getRunTime();
}

void Timer::setTimer(float time)
{
	Timer::TimeEnd = time + Initialization::computation.getRunTime();
}

float Timer::TimeLeft()
{
	float why = Initialization::computation.getRunTime();
	std::cout << why << std::endl;
	return TimeEnd - why;
}

bool Timer::RanOut()
{
	return (TimeLeft() <= 0);
}

void Timer::setStartTime()
{
	Timer::StartTime = Initialization::computation.getRunTime();
}

Timer::~Timer()
{
}
