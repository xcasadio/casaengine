#include  "Animations/AnimationEvent.hpp"

namespace CasaEngine
{
	AnimationEvent::AnimationEvent() :
		m_ID(0xffffffff),
		m_Time(0)
	{

	}

	AnimationEvent::AnimationEvent(const AnimationEvent& rsh)
	{
		*this = rsh;
	}

	AnimationEvent& AnimationEvent::operator = (const AnimationEvent& rsh)
		= default;

	AnimationEvent::~AnimationEvent()
		= default;

	unsigned int AnimationEvent::ID() const
	{
		return m_ID;
	}

	float AnimationEvent::Time() const
	{
		return m_Time;
	}

	void AnimationEvent::Time(float val)
	{
		m_Time = val;
	}
}
