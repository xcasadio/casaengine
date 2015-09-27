#ifndef BASEENTITYEVENTS_H
#define BASEENTITYEVENTS_H

#include "CA_Export.h"
#include "EventHandler/EventArgs.h"

namespace CasaEngine
{
	class BaseEntity;

	/**
	 *	
	 */
	class CA_EXPORT EntityParentChangeEvent : public CasaEngine::EventArgs
	{
	private:
		BaseEntity *m_pEntity;
		BaseEntity *m_pParent;

	public:
		static const char * GetEventName();

		EntityParentChangeEvent(BaseEntity *pEntity_, BaseEntity *pParent_);

		BaseEntity *getEntity() const;
		BaseEntity *getParent() const;
	};

	/**
	 *	
	 */
	class CA_EXPORT WindowResizeEvent : public EventArgs
	{
	private:
		unsigned int m_Width;
		unsigned int m_Height;

	public:
		static const char *GetEventName();

		WindowResizeEvent(unsigned int width_, unsigned height_);

		unsigned int Height() const;
		unsigned int Width() const;
	};

	/**
	 *	Animation 2D event when the current frame change
	 */
	class CA_EXPORT FrameChangeEvent : public EventArgs
	{
	private:
		const char *m_ID;

	public:
		static const char *GetEventName();

		FrameChangeEvent(const char *ID_);

		const char *ID() const;
	};

	/**
	 *	Animation 2D event when the animation finished (last event triggered)
	 */
	class CA_EXPORT AnimationFinishedEvent : public EventArgs
	{
	private:
		const char *m_ID;

	public:
		static const char *GetEventName();

		AnimationFinishedEvent(const char *ID_);

		const char *ID() const;
	};

} // namespace CasaEngine

#endif // BASEENTITYEVENTS_H
