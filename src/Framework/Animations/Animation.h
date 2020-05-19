#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <string>
#include "CA_Export.h"
#include <vector>
#include "AnimationEvent.h"
#include "Parsers\Xml\tinyxml2.h"
#include <sstream>
#include "Memory\MemoryAllocation.h"
#include "Assets\Assetable.h"
#include "IAnimationEventListener.h"
#include "EventHandler\EventSet.h"

namespace CasaEngine
{
	class CA_EXPORT Animation :
		public IAssetable,
		public EventSet
	{
	public:
		virtual ~Animation();

		//EventHandler OnEndAnimationReached;

		virtual void Initialize();

		void AddEvent(AnimationEvent* event_);
		unsigned int ID() const;
		float TotalTime() const;
		float CurrentTime() const;
		bool GetLoop() const;

		void Update(float elapsedTime_);
		
	protected:
		Animation();
		Animation(const Animation& rsh);
		const Animation& operator = (const Animation& rsh);

		std::vector<AnimationEvent *> m_Events;

	private:
		unsigned int m_ID;// TODO : usefull ?
		
		float m_TotalTime; // total time of the animation
		float m_CurrentTime;
		bool m_AnimationEnded;
		bool m_Loop;
		bool m_bIsInitialized;

	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IAssetable>(this));
			ar(cereal::make_nvp("loop", m_Loop));
			ar(cereal::make_nvp("animation_event", m_Events));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IAssetable>(this));
			ar(cereal::make_nvp("loop", m_Loop));
			ar(cereal::make_nvp("animation_event", m_Events));
		}

#if EDITOR
	public:
		void CurrentTime(float val);
		void RemoveEvent(AnimationEvent *event_);
		void SortEventList();

	private:
		static const int m_Version; // load version
#endif
		
	};
}

#endif
