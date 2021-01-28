#include <time.h>
#include <stdio.h>

#include "Base.h"
#include "DateTime.h"

namespace CasaEngine
{
	static DateTime m_sNow;

	/**
	 *
	 */
	DateTime::DateTime()
	{
		Update();
	}

	/**
	 *
	 */
	DateTime::~DateTime()
	{
	}

	/**
	 *
	 */
	DateTime::DateTime(const DateTime& rsh)
	{
		*this = rsh;
	}

	/**
	 *
	 */
	const DateTime& DateTime::operator = (const DateTime& rsh)
	{
		m_CurrentTime = rsh.m_CurrentTime;
		m_pTm = rsh.m_pTm;
		return *this;
	}

	/**
	 *
	 */
	const DateTime& DateTime::Now()
	{
		m_sNow.Update();
		return m_sNow;
	}

	/**
	 *
	 */
	std::string DateTime::GetCurrentDate() const
	{
		// Récupération et formatage de la date
		char sTime[24];
		strftime(sTime, sizeof(sTime), "%d/%m/%Y", m_pTm);

		return sTime;
	}

	/**
	 *
	 */
	std::string DateTime::GetCurrentTime() const
	{
		// Récupération et formatage de la date
		char sTime[24];
		strftime(sTime, sizeof(sTime), "%H:%M:%S", m_pTm);
		return sTime;
	}

	/**
	 *
	 */
	void DateTime::Update()
	{
		m_CurrentTime = time(nullptr);
		m_pTm = localtime(&m_CurrentTime);
	}
}