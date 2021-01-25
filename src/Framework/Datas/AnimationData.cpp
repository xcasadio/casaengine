#include "Base.h"
#include "Datas/AnimationData.h"

namespace CasaEngine
{
	AnimationData::AnimationData() :
		m_AnimationType(AnimationType::Once)
	{
	}

	AnimationData::~AnimationData()
	{
	}

	AnimationType AnimationData::GetAnimationType() const
	{
		return m_AnimationType;
	}

	void AnimationData::SetAnimationType(AnimationType type)
	{
		m_AnimationType = type;
	}
}
