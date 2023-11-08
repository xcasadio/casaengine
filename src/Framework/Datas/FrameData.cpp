#include  "Datas/FrameData.hpp"

namespace CasaEngine
{
	FrameData::FrameData()
		= default;

	FrameData::FrameData(const FrameData& rsh)
	{
		*this = rsh;
	}

	FrameData& FrameData::operator=(const FrameData& rsh)
		= default;

	FrameData::~FrameData()
		= default;
}
