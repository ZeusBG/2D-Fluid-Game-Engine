#pragma once
#include <chrono>
typedef std::chrono::steady_clock::time_point TimePoint;
class Clock
{
public:
	Clock();
	void Start();
	float MeasureTime();
	float GetLastDelta();
	float GetTimeSinceStart();
private:
	TimePoint m_TimeStarted;
	TimePoint m_LastMeasured;
	float m_Delta;
	float m_TimeSpeed;
};

