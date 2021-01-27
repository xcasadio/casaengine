#include "Base.h"
#include "Datas/AnimationData.h"

namespace CasaEngine
{
	AnimationData::AnimationData() :
		m_AnimationType(AnimationType::Once)
	{
	}


	AnimationData::AnimationData(const AnimationData& rsh)
	{
		*this = rsh;
	}

	AnimationData& AnimationData::operator=(const AnimationData& rsh)
	{
		m_AnimationType = rsh.m_AnimationType;
		IAssetable::operator=(rsh);
		return *this;
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
