#include "Datas/AnimationData.h"

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
	{
		_animationType = rsh._animationType;
		IAssetable::operator=(rsh);
		return *this;
	}

	AnimationData::~AnimationData()
	{
	}
}
