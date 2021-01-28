#ifndef _ANIMATIONEVENT_H_
#define _ANIMATIONEVENT_H_

#include "CA_Export.h"
#include <cereal/access.hpp>
#include <cereal/cereal.hpp>


#include "Memory\MemoryAllocation.h"

namespace CasaEngine
{
	class Animation;

	class CA_EXPORT AnimationEvent :
		public AllocatedObject<AnimationEvent>
	{
	public:
		AnimationEvent();
		AnimationEvent(const AnimationEvent& rsh);
		const AnimationEvent& operator = (const AnimationEvent& rsh);
		~AnimationEvent();

		virtual AnimationEvent* Copy() = 0;
		
		//EventHandler<AnimationFrameChangedEventArgs> OnFrameChanged;
		//EventHandler OnEndAnimationReached;

		unsigned int ID() const;
		float Time() const;
		void Time(float val);

		virtual void Activate(Animation *pAnim_) = 0;

	private:
		unsigned int m_ID; // TODO : usefull ?
		float m_Time;

	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::make_nvp("time", m_Time));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::make_nvp("time", m_Time));
		}

#if EDITOR
	private:
		static const int m_Version; // load version
#endif
	};
}

#endif
