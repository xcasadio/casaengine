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
	/**
	 *
	 */
	Animation::Animation() :
		m_ID(0xffffffff),
		//m_Name(""),
		m_TotalTime(0),
		m_CurrentTime(0),
		m_AnimationEnded(0),
		m_bIsInitialized(false),
		m_Loop(true)
	{
		addEvent(AnimationFinishedEvent::GetEventName());
	}

	/**
	 * 
	 */
	Animation::Animation(const Animation& rsh)
	{
		addEvent(AnimationFinishedEvent::GetEventName());
		*this = rsh;
	}

	/**
	 * 
	 */
	const Animation& Animation::operator = (const Animation& rsh)
	{
		//m_Name = rsh.m_Name;
		m_ID = rsh.m_ID;
		m_TotalTime = rsh.m_TotalTime;
		m_CurrentTime = rsh.m_CurrentTime;
		m_AnimationEnded = rsh.m_AnimationEnded;
		m_bIsInitialized = rsh.m_bIsInitialized;
		m_Loop = rsh.m_Loop;

		for (auto* event : rsh.m_Events)
		{
			m_Events.push_back(event->Copy());
		}

		return *this;
	}

	/**
	 * 
	 */
	Animation::~Animation()
	{
		std::vector<AnimationEvent *>::iterator it;

		for (it = m_Events.begin(); it != m_Events.end(); it++)
		{
			DELETE_AO (*it);
		}
	}

	/**
	 * 
	 */
	void Animation::Initialize()
	{
		if (m_Events.size() > 0)
		{
			m_TotalTime = m_Events.back()->Time();
		}

		m_bIsInitialized = true;
	}

	/**
	 * 
	 */
	unsigned int Animation::ID() const 
	{ 
		return m_ID; 
	}

	/**
	 * 
	 */
	float Animation::TotalTime() const 
	{ 
		return m_TotalTime; 
	}

	/**
	 *
	 */
	float Animation::CurrentTime() const 
	{ 
		return m_CurrentTime; 
	}

	/**
	 *
	 */
	bool Animation::GetLoop() const 
	{ 
		return m_Loop; 
	}

	/**
	 * 
	 */
	void Animation::Update(float elapsedTime_)
	{
		CA_ASSERT(m_bIsInitialized == true, "Animation::Update() : call Initialize before Update()");

		if (m_TotalTime == 0.0f) // no event do nothing
		{
			return;
		}

		bool isFinished = false;
		float lastTime = m_CurrentTime;
		m_CurrentTime += elapsedTime_;

		if (m_Loop == true)
		{
			//always between 0 <= current time <= TotalTime
			while(m_CurrentTime > m_TotalTime)
			{
				m_CurrentTime -= m_TotalTime;
				isFinished = true;
			}
		}
		else if (m_CurrentTime > m_TotalTime)
		{
			m_CurrentTime = m_TotalTime;
			isFinished = true;
		}

		if (isFinished == true)
		{
			fireEvent(AnimationFinishedEvent::GetEventName(), AnimationFinishedEvent(GetName().c_str()));//AnimationFinishedEvent(ID()));
		}
		
		// m_Events must be sorted by time
		for (auto event : m_Events)
		{
			// we activate only event between the last time
			// and the current time
			if (lastTime >= event->Time()
				&& event->Time() < m_CurrentTime)
			{
				event->Activate(this);
				//activeEvents.push_back(it);
			}
		}
	}

	/**
	 * 
	 */
	void Animation::AddEvent(AnimationEvent *event_) 
	{ 
		m_Events.push_back(event_); 
	}

#if EDITOR

	/**
	 * 
	 */
	void Animation::CurrentTime(float val) 
	{ 
		m_CurrentTime = val; 
	}

	/**
	 * 
	 */
	void Animation::RemoveEvent(AnimationEvent *event_) 
	{ 
		std::vector<AnimationEvent *>::iterator it;

		for (it = m_Events.begin();
			it != m_Events.end();
			it++)
		{
			if ((*it) == event_)
			{
				break;
			}
		}

		if (it != m_Events.end())
		{
			m_Events.erase(it); 
		}
	}

	/**
	 * 
	 */
	void Animation::SortEventList() 
	{ 
		//m_Events.sort(); 
	}
	
#endif

}
