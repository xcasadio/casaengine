#include "Base.h"

#include "Animations/SetFrameEvent.h"
#include <string>
#include "Animation.h"
#include "Animation2D.h"
#include "Log/LogManager.h"
#include "Parsers/Xml/tinyxml2.h"
#include <ostream>
#include <fstream>

#include "CA_Assert.h"

namespace CasaEngine
{
	/**
	 *
	 */
	SetFrameEvent::SetFrameEvent()
	{

	}

	/**
	 *
	 */
	SetFrameEvent::SetFrameEvent(const SetFrameEvent& rsh)
	{
		*this = rsh;
	}

	/**
	 *
	 */
	const SetFrameEvent& SetFrameEvent::operator = (const SetFrameEvent& rsh)
	{
		AnimationEvent::operator=(rsh);
		m_FrameID = rsh.m_FrameID;
		return *this;
	}

	/**
	 *
	 */
	SetFrameEvent::~SetFrameEvent()
	{

	}

	AnimationEvent* SetFrameEvent::Copy()
	{
		return NEW_AO SetFrameEvent(*this);
	}

	/**
	 *
	 */
	const char* SetFrameEvent::FrameID() const
	{
		return m_FrameID.c_str();
	}

	/**
	 *
	 */
	void SetFrameEvent::Activate(Animation* pAnim_)
	{
		CA_ASSERT(pAnim_ != nullptr, "SetFrameEvent::Activate() : Animation is nullptr");

		Animation2D* pAnim2D = static_cast<Animation2D*>(pAnim_);

		if (pAnim2D != nullptr)
		{
			pAnim2D->CurrentFrame(m_FrameID.c_str());
		}
		else
		{
			CA_ERROR("SetFrameEvent.Activate() : Animation(%s) is not a Animation2D\n", pAnim_->GetAnimationData()->GetName().c_str());
		}
	}

	/**
	 *
	 */
	void SetFrameEvent::FrameID(const char* val)
	{
		m_FrameID = val;
	}
}
