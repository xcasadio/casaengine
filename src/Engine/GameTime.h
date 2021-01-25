#ifndef GAMETIME_H
#define GAMETIME_H

#include "CA_Export.h"
#include "Memory/MemoryAllocation.h"

#if defined(CA_PLATFORM_WINDOWS)

typedef __int64 TimeVal;

#else // Linux, BSD, OSX

#include <stdint.h>
typedef int64_t TimeVal;

#endif // defined(CA_PLATFORM_WINDOWS)

namespace CasaEngine
{
	///
	class CA_EXPORT GameTime :
		public AllocatedObject<GameTime>
	{
	public:
		GameTime();
		~GameTime();

		/// Start the timer
		void Start();

		///
		///  @note call Start before use End()
		/// @return the elapsed time
		void End();

		///
		/// @return the total elapsed time
		float FrameTime() const;

		///
		/// @return the total elapsed time
		float TotalTime() const;

	private:
		TimeVal m_StartTime; ///< the start time

		float m_ElapsedTime; ///< last frame elapsed time
		float m_TotalElapsedTime; ///< last frame elapsed time
	};
}

#endif //GAMETIME_H
