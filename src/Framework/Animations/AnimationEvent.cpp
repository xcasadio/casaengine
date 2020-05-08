//==========================================================
// En-têtes
//==========================================================
#include "Base.h"

#include "Animations/AnimationEvent.h"
#include <string>
#include "Parsers/Xml/tinyxml2.h"
#include <iosfwd>


namespace CasaEngine
{
	/**
	 *
	 */
	AnimationEvent::AnimationEvent() :
		m_ID(0xffffffff),
		m_Time(0)
	{

	}

	/**
	 * 
	 */
	AnimationEvent::AnimationEvent(const AnimationEvent& rsh)
	{
		*this = rsh;
	}

	/**
	 * 
	 */
	const AnimationEvent& AnimationEvent::operator = (const AnimationEvent& rsh)
	{
		this->m_ID = rsh.m_ID;
		this->m_Time = rsh.m_Time;
		return *this;
	}

	/**
	 * 
	 */
	AnimationEvent::~AnimationEvent()
	{

	}

	/**
	 * 
	 */
	unsigned int AnimationEvent::ID() const 
	{ 
		return m_ID; 
	}

	/**
	 *
	 */
	float AnimationEvent::Time() const 
	{ 
		return m_Time; 
	}

	/**
	 *
	 */
	void AnimationEvent::Time(float val)
	{
		m_Time = val;
	}
	
	/**
	 * 
	 */
	void AnimationEvent::Read (std::ifstream& /*is*/)
	{

	}

	/**
	 * 
	 */
	void AnimationEvent::Read(tinyxml2::XMLElement* el_)
	{
		el_->QueryFloatAttribute("time", &m_Time);
	}

#if EDITOR

	/**
	 * 
	 */
	void AnimationEvent::Write(std::ostream& /*os*/) const
	{

	}

	/**
	 * 
	 */
	void AnimationEvent::Write(tinyxml2::XMLElement *el_) const
	{

	}
	
#endif

}
