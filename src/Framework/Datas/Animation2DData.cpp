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
		for (auto& frame: rsh._frames)
		{ 
			_frames.push_back(frame);
		}
		
		AnimationData::operator=(rsh);
		return *this;
	}

	Animation2DData::~Animation2DData()
	{
	}

	Animation2DData* Animation2DData::Copy() const
	{
		return new Animation2DData(*this);
	}
}
