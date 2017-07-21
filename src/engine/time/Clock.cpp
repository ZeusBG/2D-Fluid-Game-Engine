#pragma once
#include "Clock.h"

Clock::Clock()
{
	m_Delta = 0;
	m_TimeSpeed = 1.0f;
}

void Clock::Start()
{
	m_TimeStarted = std::chrono::steady_clock::now();
	m_LastMeasured = m_TimeStarted;
}

float Clock::MeasureTime()
{
	TimePoint now = std::chrono::steady_clock::now();
	m_Delta = (std::chrono::duration_cast<std::chrono::microseconds>(now - m_LastMeasured).count() / 1000.0f) * m_TimeSpeed;
	return m_Delta;
}

float Clock::GetLastDelta()
{
	return m_Delta;
}

float Clock::GetTimeSinceStart()
{
	return (std::chrono::duration_cast<std::chrono::microseconds>(m_TimeStarted - m_LastMeasured).count() / 1000.0f);
}
