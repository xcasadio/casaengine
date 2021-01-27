#include "Base.h"
#include "Datas/Animation2DData.h"


namespace CasaEngine
{
	Animation2DData::Animation2DData()
	{
	}

	Animation2DData::Animation2DData(const Animation2DData& rsh)
	{
		*this = rsh;
	}


	Animation2DData& Animation2DData::operator=(const Animation2DData& rsh)
	{
		for (auto& frame: rsh.m_Frames)
		{ 
			m_Frames.push_back(frame);
		}
		
		AnimationData::operator=(rsh);
		return *this;
	}

	Animation2DData::~Animation2DData()
	{
	}

	std::vector<FrameData>& Animation2DData::GetFrames()
	{
		return m_Frames;
	}

	void Animation2DData::AddFrame(FrameData& frame)
	{
		return m_Frames.push_back(frame);
	}

	Animation2DData* Animation2DData::Copy() const
	{
		return NEW_AO Animation2DData(*this);
	}
}
