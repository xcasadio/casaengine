#pragma once

#include <string>

#include "CA_Export.hpp"

namespace CasaEngine
{
	class CA_EXPORT DateTime
	{
	public:
		DateTime();
		DateTime(const DateTime& rsh);
		DateTime& operator = (const DateTime& rsh);
		~DateTime();

		static const DateTime& Now();

		// Current Date convert to string : 21/04/2013
		std::string GetCurrentDate() const;
		// Current time convert to string : 16:40:38
		std::string GetCurrentTime() const;

	private:

		static DateTime m_Now;
		time_t m_CurrentTime{};
		tm* m_pTm{};

		void Update();
	};
}
