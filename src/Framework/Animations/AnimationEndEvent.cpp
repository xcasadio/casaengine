#include  "Base.hpp"

#include  "Animations/AnimationEndEvent.hpp"
#include  "Animation.hpp"
#include  "Animation2D.hpp"
#include  "Log/LogManager.hpp"

#include <ostream>
#include <fstream>

namespace CasaEngine
{
	AnimationEndEvent::AnimationEndEvent() = default;

	AnimationEndEvent::AnimationEndEvent(const AnimationEndEvent& rsh)
	{
		*this = rsh;
	}

	AnimationEndEvent& AnimationEndEvent::operator = (const AnimationEndEvent& rsh) = default;

	AnimationEndEvent::~AnimationEndEvent() = default;

	AnimationEvent* AnimationEndEvent::Copy()
	{
		return new AnimationEndEvent(*this);
	}

	void AnimationEndEvent::Activate(Animation* pAnim_)
	{

	}
}
