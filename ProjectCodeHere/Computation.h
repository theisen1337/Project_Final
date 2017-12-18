#pragma once
#ifndef Computation_H
#define Computation_H




class Computation
{
public:
	Computation();
	void Instruction();
	static float getRunTime();
	float getTicksPerSecond();

private:
	
	void UpdateStatistics();
	void setRunTime();
	void setTicksPerSecond();

	//float RunTime;
	float ticksPerSecond;
	int ticksThisSecond;

	float alotted_1SEC_Timer;

};
#endif