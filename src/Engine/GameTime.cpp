#include "Base.h"
#include "GameTime.h"

#if defined(CA_PLATFORM_WINDOWS)

#include <windows.h>

TimeVal getPerfTime()
{
	__int64 count;
	QueryPerformanceCounter((LARGE_INTEGER*)&count);
	return count;
}

int getPerfDeltaTimeUsec(const TimeVal start, const TimeVal end)
{
	static __int64 freq = 0;
	if (freq == 0)
		QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	__int64 elapsed = end - start;
	return static_cast<int>(elapsed * 1000000 / freq);
}

#else // Linux, BSD, OSX

#include <sys/time.h>

TimeVal getPerfTime()
{
	timeval now;
	gettimeofday(&now, 0);
	return (TimeVal)now.tv_sec*1000000L + (TimeVal)now.tv_usec;
}

int getPerfDeltaTimeUsec(const TimeVal start, const TimeVal end)
{
	return (int)(end - start);
}

#endif // defined(CA_PLATFORM_WINDOWS)

namespace CasaEngine
{

GameTime::GameTime()
{
	m_ElapsedTime = 0;
	m_TotalElapsedTime = 0;
	m_StartTime = 0;
	//m_FirstStartTime = 0;
}

/**
 * 
 */
GameTime::~GameTime()
{
}

/**
 * 
 */
float GameTime::FrameTime() const
{
	return m_ElapsedTime;
}

/**
 * 
 */
float GameTime::TotalTime() const
{
	return m_TotalElapsedTime;
}

/**
 * 
 */
void GameTime::Start()
{
	m_StartTime = getPerfTime();
}

/**
 * 
 */
void GameTime::End()
{
	TimeVal endTime = getPerfTime();
	float v = static_cast<float>(getPerfDeltaTimeUsec(m_StartTime, endTime)) / 100000.0f;

	m_ElapsedTime = v;
	m_TotalElapsedTime += m_ElapsedTime;

#ifdef CA_DEBUGGING

	//If we are in a breakpoint the time of the frame
	//can be very high and create some bug
	if (m_ElapsedTime > 0.05f) // 1/20 FPS
	{
		m_ElapsedTime = 1.0f / 60.0f;
	}

#endif // CA_DEBUGGING
}

}
