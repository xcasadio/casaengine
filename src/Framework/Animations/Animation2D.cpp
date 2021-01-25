#include "Base.h"

#include "Animations/Animation2D.h"
#include <string>
#include "SetFrameEvent.h"
#include "Memory/MemoryAllocation.h"
#include "Entities/EntityManager.h"
#include "Entities/Events/BaseEntityEvents.h"
#include "Animations/AnimationEndEvent.h"

namespace CasaEngine
{
	Animation2D::Animation2D(Animation2DData& data) :
		Animation(data),
		m_CurrentFrame(nullptr)
	{
		addEvent(FrameChangeEvent::GetEventName());
		m_pAnimation2DData = &data;
		float timeEventFired = 0.0f;
		for (auto frame : data.GetFrames())
		{
			SetFrameEvent* pFrameEvent = new SetFrameEvent();
			pFrameEvent->FrameID(frame->GetSpriteId().c_str());
			pFrameEvent->Time(timeEventFired);
			timeEventFired += frame->GetDuration();
			AddEvent(pFrameEvent);
		}

		if (data.GetFrames().size() > 0)
		{
			AnimationEndEvent* pEndEvent = NEW_AO AnimationEndEvent();
			pEndEvent->Time(timeEventFired);
			AddEvent(pEndEvent);
		}
	}

	Animation2D::~Animation2D()
	{

	}

	void Animation2D::Initialize()
	{
		Animation::Initialize();
		Reset();
	}

	void Animation2D::Reset()
	{
		for (unsigned int i=0; i<m_Events.size(); i++)
		{
			SetFrameEvent *pFrameEvent = dynamic_cast<SetFrameEvent *>(m_Events[i]);
			if (pFrameEvent != nullptr)
			{
				CurrentFrame(pFrameEvent->FrameID());
				break;
			}
		}
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
}
