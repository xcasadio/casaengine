#include "Base.h"

#include "Animations/AnimationEndEvent.h"
#include "Animation.h"
#include "Animation2D.h"
#include "Log/LogManager.h"

#include <ostream>
#include <fstream>

namespace CasaEngine
{
	/**
	 *
	 */
	AnimationEndEvent::AnimationEndEvent()
		= default;

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
		= default;

	/**
	 *
	 */
	AnimationEndEvent::~AnimationEndEvent()
		= default;

	AnimationEvent* AnimationEndEvent::Copy()
	{
		return new AnimationEndEvent(*this);
	}

	/**
	 *
	 */
	void AnimationEndEvent::Activate(Animation* pAnim_)
	{

	}
}
