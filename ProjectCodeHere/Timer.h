#pragma once
class Timer
{
public:
	Timer(float time);
	Timer(int time);

	~Timer();


	bool RanOut();
	float TimeLeft();
	

private:
	float StartTime;
	float TimeEnd;
	float span;

};

