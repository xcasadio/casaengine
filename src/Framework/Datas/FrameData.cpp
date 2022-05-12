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
		_duration = rsh._duration;
		_spriteId = rsh._spriteId;
		IAssetable::operator=(rsh);

		return *this;
	}

	FrameData::~FrameData()
	{
	}
}
