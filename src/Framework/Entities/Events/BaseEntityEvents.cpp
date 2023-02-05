#include "BaseEntityEvents.h"

namespace CasaEngine
{
	//////////////////////////////////////////////////////////////////////////
	/**
	 * 
	 */
	const char * EntityParentChangeEvent::GetEventName()
	{
		return "ParentChangedEvent";
	}

	/**
	 * 
	 */
	EntityParentChangeEvent::EntityParentChangeEvent(BaseEntity *entity, BaseEntity *pParent_)
	{
		m_pEntity = entity;
		m_pParent = pParent_;
	}

	/**
	 * 
	 */
	BaseEntity *EntityParentChangeEvent::getEntity() const
	{
		return m_pEntity;
	}

	/**
	 * 
	 */
	BaseEntity *EntityParentChangeEvent::getParent() const
	{
		return m_pParent;
	}

	//////////////////////////////////////////////////////////////////////////
	const char * WindowResizeEvent::GetEventName()
	{
		return "WindowResizeEvent";
	}

	/**
	 * 
	 */
	WindowResizeEvent::WindowResizeEvent( unsigned int width_, unsigned height_ )
	{
		m_Width = width_;
		m_Height = height_;
	}

	/**
	 * 
	 */
	unsigned int WindowResizeEvent::Height() const
	{
		return m_Height;
	}

	/**
	 * 
	 */
	unsigned int WindowResizeEvent::Width() const
	{
		return m_Width;
	}

	//////////////////////////////////////////////////////////////////////////
	const char * FrameChangeEvent::GetEventName()
	{
		return "FrameChangeEvent";
	}

	/**
	 * 
	 */
	FrameChangeEvent::FrameChangeEvent(const char *Id_ )
	{
		m_ID = Id_;
	}

	/**
	 * 
	 */
	const char *FrameChangeEvent::ID() const
	{
		return m_ID;
	}

	//////////////////////////////////////////////////////////////////////////
	const char * AnimationFinishedEvent::GetEventName()
	{
		return "AnimationFinishedEventName";
	}

	/**
	 * 
	 */
	AnimationFinishedEvent::AnimationFinishedEvent(const char *Id_ )
	{
		m_ID = Id_;
	}

	/**
	 * 
	 */
	const char *AnimationFinishedEvent::ID() const
	{
		return m_ID;
	}

}
