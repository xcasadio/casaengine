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
#include <Animations/AnimationType.h>
#include <Datas/AnimationData.h>

namespace CasaEngine
{
	class CA_EXPORT Animation :
		public EventSet
	{
	public:
		virtual ~Animation();

		virtual void Initialize();

		void AddEvent(AnimationEvent* event_);
		float TotalTime() const;
		float CurrentTime() const;

		void Update(float elapsedTime_);

		AnimationData* GetAnimationData();
		
	protected:
		Animation(AnimationData& animationData);

		std::vector<AnimationEvent *> m_Events;

	private:
		float m_CurrentTime;
		bool m_AnimationEnded;
		bool m_bIsInitialized;
		AnimationData* m_pAnimationData;

#if EDITOR
	public:
		void CurrentTime(float val);
		void RemoveEvent(AnimationEvent *event_);
		void SortEventList();
#endif
		
	};
}

#endif
