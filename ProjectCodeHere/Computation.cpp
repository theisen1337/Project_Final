#include "Computation.h"
#include <chrono>



static auto startTime = std::chrono::high_resolution_clock::now();

///Computation
Computation::Computation()
{
	ticksPerSecond = 0;
	ticksThisSecond = 0;
	RunTime = 0;
	alotted_1SEC_Timer = 1.0f;
}

void Computation::Instruction()
{
	UpdateStatistics(); // update private statistics of the Computation. i.e. ticksPerSecond.

	//SpriteContainer.Compute() // witch will hold the compute() all sprites
	//Renderer.draw()
}

void Computation::UpdateStatistics()
{
	//Set the Runtime from the initalization of this class. must be updated pirior to every other Instruction.
	setRunTime();
	setTicksPerSecond();
}

//return the ticks p/s of the last second.
float Computation::getTicksPerSecond()
{
	return ticksPerSecond;
}

//Calculate the amount of ticks p/s.
void Computation::setTicksPerSecond()
{
	ticksThisSecond++;

	if (alotted_1SEC_Timer < getRunTime())
	{
		alotted_1SEC_Timer += 1.0f;
		ticksPerSecond = ticksThisSecond;
		ticksThisSecond = 0;
	}
}

//grabs chrono "now" time, and compare it to the beginning of this class implementation. 
void Computation::setRunTime()
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	Computation::RunTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
}


//Return RunTime
float Computation::getRunTime()
{
	return Computation::RunTime;
}

