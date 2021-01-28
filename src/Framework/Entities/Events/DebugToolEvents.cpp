#include "DebugToolEvents.h"

namespace CasaEngine
{
	const std::string FPSChangeEvent::FPSChangeEventName("FPSChangeEventName");

	/**
	 *
	 */
	FPSChangeEvent::FPSChangeEvent( const int FPS_ )
	{
		m_iFPS = FPS_;
	}

	/**
	 * 
	 */
	int FPSChangeEvent::getFPS() const
	{
		return m_iFPS;
	}

}
