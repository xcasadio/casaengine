#include "Base.h"
#include "Log/LogManager.h"
#include "Animations/Animation.h"
#include <string>
#include "AnimationEvent.h"
#include "Assets/Assetable.h"

#include "CA_Assert.h"
#include "Entities/Events/BaseEntityEvents.h"


namespace CasaEngine
{
	Animation::Animation(AnimationData& animationData) :
		m_CurrentTime(0),
		m_AnimationEnded(0),
		m_bIsInitialized(false),
		m_pAnimationData(&animationData)
	{
		addEvent(AnimationFinishedEvent::GetEventName());
	}

	Animation::~Animation()
	{
		for (auto it = m_Events.begin(); it != m_Events.end(); ++it)
		{
			delete* it;
		}
	}

	void Animation::Initialize()
	{
		m_bIsInitialized = true;
	}

	float Animation::TotalTime() const
	{
		if (!m_Events.empty())
		{
			return m_Events.back()->Time();
		}

		return 0.0f;
	}

	float Animation::CurrentTime() const
	{
		return m_CurrentTime;
	}

	void Animation::Reset()
	{
		m_CurrentTime = 0.0f;
	}

	AnimationData* Animation::GetAnimationData()
	{
		return m_pAnimationData;
	}

	void Animation::Update(float elapsedTime)
	{
		CA_ASSERT(m_bIsInitialized == true, "Animation::Update() : call Initialize before Update()");

		const auto totalTime = TotalTime();
		if (totalTime == 0.0f)
		{
			return;
		}

		bool isFinished = false;
		const float lastTime = m_CurrentTime;
		m_CurrentTime += elapsedTime;
		float currentTime = m_CurrentTime;

		if (m_pAnimationData->_animationType == AnimationType::Loop)
		{
			while (m_CurrentTime > totalTime)
			{
				m_CurrentTime -= totalTime;
				//isFinished = true;
			}
			currentTime = m_CurrentTime;
		}
		else if (m_pAnimationData->_animationType == AnimationType::Once)
		{
			if (m_CurrentTime > totalTime)
			{
				m_CurrentTime = totalTime;
				currentTime = m_CurrentTime;
				isFinished = true;
			}
		}
		else if (m_pAnimationData->_animationType == AnimationType::PingPong)
		{
			int pingPongState = 0;

			while (currentTime > totalTime)
			{
				currentTime -= totalTime;
				pingPongState = 1 - pingPongState;
			}

			if (pingPongState == 1)
			{
				currentTime = totalTime - currentTime;
			}
		}
		else
		{
			throw std::exception("animation type is not supported");
		}

		if (isFinished == true)
		{
			fireEvent(AnimationFinishedEvent::GetEventName(), AnimationFinishedEvent(m_pAnimationData->GetName().c_str()));
		}

		// m_Events must be sorted by time
		for (auto* event : m_Events)
		{
			if (lastTime >= event->Time()
				&& event->Time() < currentTime)
			{
				event->Activate(this);
			}
		}
	}

	void Animation::AddEvent(AnimationEvent* event)
	{
		m_Events.push_back(event);
	}

#if EDITOR

	float* Animation::CurrentTimePtr()
	{
		return &m_CurrentTime;
	}

	void Animation::CurrentTime(float val)
	{
		m_CurrentTime = val;
	}

	void Animation::RemoveEvent(AnimationEvent* event)
	{
		std::vector<AnimationEvent*>::iterator it;

		for (it = m_Events.begin();
			it != m_Events.end();
			++it)
		{
			if (*it == event)
			{
				break;
			}
		}

		if (it != m_Events.end())
		{
			m_Events.erase(it);
		}
	}

	void Animation::SortEventList()
	{
		//m_Events.sort(); 
	}

#endif

}
