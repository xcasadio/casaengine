#include "Tools/DebugSystem.h"
#include "GameTime.h"
#include "Maths/Math.h"

namespace CasaEngine
{
	DebugSystem::DebugSystem() :
		m_offset(0), m_min(0), m_max(0), m_avg(0), m_lastGameTimes{}
	{
		for (int i = 0; i < numSamples; i++)
		{
			m_lastGameTimes[i] = -1.0f;
		}
	}

	void DebugSystem::Update(const GameTime& gameTime_)
	{
		m_lastGameTimes[m_offset] = gameTime_.FrameTime();
		m_offset = ++m_offset % numSamples;

		float avg = 0.0f;
		float min = Math::MaxFloat;
		float max = -Math::MaxFloat;
		int count = 0;

		for (float val : m_lastGameTimes)
		{
			if (val < 0.0f)
			{
				continue;
			}

			min = Math::MinOf(min, val);
			max = Math::MaxOf(max, val);
			avg += val;
			count++;
		}

		m_min = min;
		m_max = max;
		m_avg = avg / static_cast<float>(count);
	}

	float DebugSystem::GetFPS() const
	{
		return 1.0f / m_avg;
	}

	float DebugSystem::GetMinFPS() const
	{
		return m_min;
	}

	float DebugSystem::GetMaxFPS() const
	{
		return m_max;
	}

	float DebugSystem::GetAverageFPS() const
	{
		return m_avg;
	}
}
