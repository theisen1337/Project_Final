#pragma once
#ifndef Computation_H
#define Computation_H
#include <chrono>



class Computation
{
public:
	Computation();
	void Instruction();
	static float getRunTime();
	static float getGameTime();
	static float getTicksPerSecond();
	static float getFrameRate();

private:
	
	void UpdateStatistics();
	void setRunTime(std::chrono::time_point<std::chrono::steady_clock> currenttime);
	void setGameTime(std::chrono::time_point<std::chrono::steady_clock> currenttime);
	void setPauseTime(std::chrono::time_point<std::chrono::steady_clock> currenttime);
	void setTicksPerSecond();

	//float RunTime;
	//float ticksPerSecond;
	int ticksThisSecond;
	int FrameRateThisSecond;

	float alotted_1SEC_Timer;
	float PauseTime;
	float TotalPauseTime;
	std::chrono::time_point<std::chrono::steady_clock> SincePaused;
	

};
#endif