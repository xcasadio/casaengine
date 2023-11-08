#pragma once

#include "CA_Export.hpp"
#include <vector>
#include  "AnimationEvent.hpp"
#include  "EventHandler/EventSet.hpp"
#include <Datas/AnimationData.hpp>

namespace CasaEngine
{
	class CA_EXPORT Animation :
		public EventSet
	{
	public:
		~Animation() override;

		virtual void Initialize();
		void Update(float elapsedTime);

		void AddEvent(AnimationEvent* event);
		float TotalTime() const;
		float CurrentTime() const;
		virtual void Reset();

		AnimationData* GetAnimationData();

	protected:
		Animation(AnimationData& animationData);

		std::vector<AnimationEvent*> m_Events;

	private:
		float m_CurrentTime;
		bool m_AnimationEnded;
		bool m_bIsInitialized;
		AnimationData* m_pAnimationData;

#if EDITOR
	public:
		float* CurrentTimePtr();
		void CurrentTime(float val);
		void RemoveEvent(AnimationEvent* event);
		void SortEventList();
#endif

	};
}
