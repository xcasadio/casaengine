#include "Base.h"

#include "Animations/AnimationEndEvent.h"
#include <string>
#include "Animation.h"
#include "Animation2D.h"
#include "Log/LogManager.h"
#include "Parsers/Xml/tinyxml2.h"
#include <ostream>
#include <sstream>
#include <fstream>
#include "Macro.h"
#include "CA_Assert.h"

namespace CasaEngine
{
	/**
	 *
	 */
	AnimationEndEvent::AnimationEndEvent()
	{

	}

	/**
	 * 
	 */
	AnimationEndEvent::AnimationEndEvent(const AnimationEndEvent& rsh)
	{
		*this = rsh;
	}

	/**
	 * 
	 */
	const AnimationEndEvent& AnimationEndEvent::operator = (const AnimationEndEvent& rsh)
	{
		AnimationEvent::operator=(rsh);
		return *this;
	}

	/**
	 * 
	 */
	AnimationEndEvent::~AnimationEndEvent()
	{

	}

	AnimationEvent* AnimationEndEvent::Copy()
	{
		return NEW_AO AnimationEndEvent(*this);
	}

	/**
	 * 
	 */
	void AnimationEndEvent::Activate(Animation *pAnim_)
	{
		
	}

	/**
	 * 
	 */
	void AnimationEndEvent::Read (std::ifstream& /*is*/)
	{

	}

	/**
	 * 
	 */
	void AnimationEndEvent::Read(tinyxml2::XMLElement *el_)
	{
		AnimationEvent::Read(el_);
	}
	
#if EDITOR
	/**
	 * 
	 */
	void AnimationEndEvent::Write(std::ostream& /*os*/) const
	{

	}

	/**
	 * 
	 */
	void AnimationEndEvent::Write(tinyxml2::XMLElement *el_) const
	{

	}

#endif // EDITOR


}
