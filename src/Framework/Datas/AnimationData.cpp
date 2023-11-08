#include  "Datas/AnimationData.hpp"

namespace CasaEngine
{
	AnimationData::AnimationData() :
		_animationType(AnimationType::Once)
	{
	}


	AnimationData::AnimationData(const AnimationData& rsh)
	{
		*this = rsh;
	}

	AnimationData& AnimationData::operator=(const AnimationData& rsh)
		= default;

	AnimationData::~AnimationData()
		= default;
}
