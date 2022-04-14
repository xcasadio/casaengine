#pragma once

#include "CA_Export.h"
#include "GameTime.h"

namespace CasaEngine
{
    class CA_EXPORT DebugSystem
    {
	public :
		DebugSystem();

		void Update(const GameTime& gameTime_);
		float GetFPS() const;
		float GetMinFPS() const;
		float GetMaxFPS() const;
		float GetAverageFPS() const;
		
	private:
		unsigned int m_offset;
		float m_min;
		float m_max;
		float m_avg;
		static constexpr unsigned int numSamples = 100;
		float m_lastGameTimes[numSamples];
	};

}
