#include <ctime>
#include <cstdio>

#include "Base.h"
#include "DateTime.h"

namespace CasaEngine
{
	static DateTime m_sNow;

	DateTime::DateTime()
	{
		Update();
	}

	DateTime::~DateTime() = default;

	DateTime::DateTime(const DateTime& rsh)
	{
		*this = rsh;
	}

	DateTime& DateTime::operator = (const DateTime& rsh) = default;

	const DateTime& DateTime::Now()
	{
		m_sNow.Update();
		return m_sNow;
	}

	std::string DateTime::GetCurrentDate() const
	{
		char sTime[24];
		strftime(sTime, sizeof(sTime), "%d/%m/%Y", m_pTm);

		return sTime;
	}

	std::string DateTime::GetCurrentTime() const
	{
		char sTime[24];
		strftime(sTime, sizeof(sTime), "%H:%M:%S", m_pTm);
		return sTime;
	}

	void DateTime::Update()
	{
		m_CurrentTime = time(nullptr);
		m_pTm = localtime(&m_CurrentTime);
	}
}