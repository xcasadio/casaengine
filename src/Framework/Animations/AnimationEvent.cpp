#include "Animations/AnimationEvent.h"

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
	{
		this->m_ID = rsh.m_ID;
		this->m_Time = rsh.m_Time;
		return *this;
	}

	AnimationEvent::~AnimationEvent()
	{

	}

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
