#include "Base.h"
#include "Datas/Animation2DData.h"


namespace CasaEngine
{
	Animation2DData::Animation2DData()
	{
	}

	Animation2DData::~Animation2DData()
	{
	}

	std::vector<FrameData*>& Animation2DData::GetFrames()
	{
		return m_Frames;
	}

	void Animation2DData::AddFrame(FrameData * frame)
	{
		return m_Frames.push_back(frame);
	}
}
