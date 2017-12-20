#include <chrono>
#include <iomanip>

#include "Computation.h"
#include "SpokkEngine.h"
#include "Initialization.h"

static auto startTime = std::chrono::high_resolution_clock::now();
static float RunTime;
static float GameTime;
static float ticksPerSecond;
static float FPS;

auto SincePaused = std::chrono::high_resolution_clock::now();

VulkanRender renderc = *(SpokkEngine::getRender());

///Computation
Computation::Computation()
{
	ticksPerSecond = 0;
	ticksThisSecond = 0;
	RunTime = 0;
	GameTime = 0;
	PauseTime = 0;
	TotalPauseTime = 0;
	alotted_1SEC_Timer = 1.0f;
}

void Computation::Instruction()
{
	UpdateStatistics(); // update private statistics of the Computation. i.e. ticksPerSecond.

	

	
	//#################################################################


	renderc.updateUniformBuffer();
	renderc.drawFrame();
	glfwPollEvents();


	//#################################################################
}

void Computation::UpdateStatistics()
{
	//Set the Runtime from the initalization of this class. must be updated pirior to every other Instruction.
	auto currentTime = std::chrono::high_resolution_clock::now();

	setRunTime(currentTime);
	if (!*Initialization::getBool('p'))
	{
		setGameTime(currentTime);
		SincePaused = currentTime;
	}
	else
	{
		setPauseTime(currentTime);
	}
	setTicksPerSecond();
}

//return the ticks p/s of the last second.
float Computation::getTicksPerSecond()
{
	return ticksPerSecond;
}

float Computation::getFrameRate()
{
	return FPS;
}


//Calculate the amount of ticks p/s.
void Computation::setTicksPerSecond()
{
	ticksThisSecond++;
	FrameRateThisSecond++;

	if (alotted_1SEC_Timer < getRunTime())
	{
		alotted_1SEC_Timer += 1.0f;

		FPS = FrameRateThisSecond;
		FrameRateThisSecond = 0;

		ticksPerSecond = ticksThisSecond;
		ticksThisSecond = 0;

		std::cout << "RunTime " << std::setw(6) << RunTime
			<< "\tGameTime " << std::setw(6) << GameTime
			<< "\tPauseTime " << std::setw(6) << PauseTime
			<< "\tTotalPauseTime " << std::setw(6) << TotalPauseTime
			<< "\tTicks " << std::setw(6) << ticksPerSecond << std::endl;
			//<< "\tFPS "<< FPS <<std::endl;
	}
}

//grabs chrono "now" time, and compare it to the beginning of this class implementation. 
void Computation::setRunTime(std::chrono::time_point<std::chrono::steady_clock> currenttime)
{
	RunTime = std::chrono::duration<float, std::chrono::seconds::period>(currenttime - startTime).count();
}

//grabs chrono "now" time, and compare it to the beginning of this class implementation. 
void Computation::setGameTime(std::chrono::time_point<std::chrono::steady_clock> currenttime)
{
	if (PauseTime > 0)
	{
		TotalPauseTime += PauseTime;
		PauseTime = 0;
	}
	GameTime = (std::chrono::duration<float, std::chrono::seconds::period>(currenttime - startTime).count() - TotalPauseTime);
}

//grabs chrono "now" time, and compare it to the beginning of this class implementation. 
void Computation::setPauseTime(std::chrono::time_point<std::chrono::steady_clock> currenttime)
{

	PauseTime = std::chrono::duration<float, std::chrono::seconds::period>(currenttime - SincePaused).count();
}

//Return RunTime
float Computation::getRunTime()
{
	return RunTime;
}

float Computation::getGameTime()
{
	return GameTime;
}

