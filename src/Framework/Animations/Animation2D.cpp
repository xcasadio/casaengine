#include "Base.h"

#include "Animations/Animation2D.h"
#include <string>
#include "SetFrameEvent.h"

#include "Entities/EntityManager.h"
#include "Entities/Events/BaseEntityEvents.h"
#include "Animations/AnimationEndEvent.h"

namespace CasaEngine
{
	Animation2D::Animation2D(Animation2DData& data) :
		Animation(data),
		m_CurrentFrame(nullptr),
		m_pAnimation2DData(&data)
	{
		addEvent(FrameChangeEvent::GetEventName());

		float timeEventFired = 0.0f;
		for (const auto& frame : data.GetFrames())
		{
			auto *pFrameEvent = new SetFrameEvent();
			pFrameEvent->FrameID(frame.GetSpriteId().c_str());
			pFrameEvent->Time(timeEventFired);
			timeEventFired += frame.GetDuration();
			AddEvent(pFrameEvent);
		}

		if (!data.GetFrames().empty())
		{
			auto *pEndEvent = new AnimationEndEvent();
			pEndEvent->Time(timeEventFired);
			AddEvent(pEndEvent);
		}
	}

	void Animation2D::Initialize()
	{
		Animation::Initialize();
		Reset();
	}

	void Animation2D::Reset()
	{
		for (const auto& m_Event : m_Events)
		{
			auto *pFrameEvent = dynamic_cast<SetFrameEvent *>(m_Event);
			if (pFrameEvent != nullptr)
			{
				CurrentFrame(pFrameEvent->FrameID());
				break;
			}
		}

		Animation::Reset();
	}

	const char* Animation2D::CurrentFrame() const 
	{ 
		return m_CurrentFrame; 
	}

	void Animation2D::CurrentFrame(const char* val) 
	{ 
		m_CurrentFrame = val;

		fireEvent(FrameChangeEvent::GetEventName(), FrameChangeEvent(m_CurrentFrame));
	}

	Animation2DData* Animation2D::GetAnimation2DData()
	{
		return m_pAnimation2DData;
	}
	
}
