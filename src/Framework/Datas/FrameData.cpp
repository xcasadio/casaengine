#include "Base.h"

#include "Datas/FrameData.h"


namespace CasaEngine
{
	FrameData::FrameData()
	{
	}

	FrameData::FrameData(const FrameData& rsh)
	{
		*this = rsh;
	}

	FrameData& FrameData::operator=(const FrameData& rsh)
	{
		m_Duration = rsh.m_Duration;
		m_SpriteId = rsh.m_SpriteId;
		IAssetable::operator=(rsh);

		return *this;
	}


	FrameData::~FrameData()
	{
	}



	float FrameData::GetDuration()
	{
		return m_Duration;
	}

	void FrameData::SetDuration(float duration)
	{
		m_Duration = duration;
	}

	std::string FrameData::GetSpriteId()
	{
		return m_SpriteId;
	}

	void FrameData::SetSpriteId(std::string spriteId)
	{
		m_SpriteId = spriteId;
	}
}
