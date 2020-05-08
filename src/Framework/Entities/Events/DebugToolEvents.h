#ifndef DEBUGTOOLEVENTS_H
#define DEBUGTOOLEVENTS_H


#include "CA_Export.h"
#include "EventHandler\EventArgs.h"

#include <string>

namespace CasaEngine
{
	/**
	 *	
	 */
	class CA_EXPORT FPSChangeEvent : public EventArgs
	{
	public:
		static const std::string FPSChangeEventName;

		FPSChangeEvent(const int FPS_);

		int getFPS() const;

	private:
		int m_iFPS;
	};

}

#endif // DEBUGTOOLEVENTS_H
