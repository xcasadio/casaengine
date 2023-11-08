#include  "Base.hpp"
#include  "Animations/SetFrameEvent.hpp"
#include <string>
#include  "Animation.hpp"
#include  "Animation2D.hpp"
#include  "Log/LogManager.hpp"

#include <ostream>
#include <fstream>

#include  "CA_Assert.hpp"

namespace CasaEngine
{
	SetFrameEvent::SetFrameEvent()
		= default;

	SetFrameEvent::SetFrameEvent(const SetFrameEvent& rsh)
	{
		*this = rsh;
	}

	SetFrameEvent& SetFrameEvent::operator = (const SetFrameEvent& rsh)
		= default;

	SetFrameEvent::~SetFrameEvent()
		= default;

	AnimationEvent* SetFrameEvent::Copy()
	{
		return new SetFrameEvent(*this);
	}

	const char* SetFrameEvent::FrameID() const
	{
		return m_FrameID.c_str();
	}

	void SetFrameEvent::Activate(Animation* pAnim_)
	{
		CA_ASSERT(pAnim_ != nullptr, "SetFrameEvent::Activate() : Animation is nullptr");

		auto* pAnim2D = static_cast<Animation2D*>(pAnim_);

		if (pAnim2D != nullptr)
		{
			pAnim2D->CurrentFrame(m_FrameID.c_str());
		}
		else
		{
			CA_ERROR("SetFrameEvent.Activate() : Animation(%s) is not a Animation2D\n", pAnim_->GetAnimationData()->GetName().c_str());
		}
	}

	void SetFrameEvent::FrameID(const char* val)
	{
		m_FrameID = val;
	}
}
