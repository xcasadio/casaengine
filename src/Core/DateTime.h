#ifndef DATETIME_H
#define DATETIME_H

#include <sys\types.h>
#include <string>

#include "CA_Export.h"
#include "Memory\MemoryAllocation.h"

namespace CasaEngine
{
	class CA_EXPORT DateTime :
		public AllocatedObject<DateTime>
	{
	public:
		DateTime();
		DateTime(const DateTime &rsh);
		const DateTime& operator = (const DateTime& rsh);
		~DateTime();

		static const DateTime& Now();

		//----------------------------------------------------------
		// Current Date convert to string : 21/04/2013
		//----------------------------------------------------------
		std::string GetCurrentDate() const;

		//----------------------------------------------------------
		// Current time convert to string : 16:40:38
		//----------------------------------------------------------
		std::string GetCurrentTime() const;

	private:

		static DateTime m_Now;
		time_t m_CurrentTime;
		tm *m_pTm;

		void Update();
	};
}

#endif // DATETIME_H
