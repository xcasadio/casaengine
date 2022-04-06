#pragma once

#include "CA_Export.h"

#ifdef CA_PLATFORM_WINDOWS
typedef __int64 TimeVal;
#else // Linux, BSD, OSX
#include <stdint.h>
typedef int64_t TimeVal;
#endif

namespace CasaEngine
{
	class CA_EXPORT GameTime
	{
	public:
		GameTime();
		~GameTime();

		void Start();
		void End();

		float FrameTime() const;
		float TotalTime() const;

	private:
		TimeVal m_StartTime; ///< the start time
		float m_ElapsedTime; ///< last frame elapsed time
		float m_TotalElapsedTime; ///< last frame elapsed time
	};
}
