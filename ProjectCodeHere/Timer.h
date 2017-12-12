#pragma once
class Timer
{
public:
	Timer(float time);
	Timer(int time);

	~Timer();

	void setTimer(float time);
	void setTimer(int time);

	bool RanOut();
	float TimeLeft();
	

private:
	float StartTime;
	float TimeEnd;
	float span;

};

