
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
	/////////////////////////////////////////////////////////////
	/// Sprite
	/////////////////////////////////////////////////////////////
	class CA_EXPORT Animation :
		public IAssetable,
		public EventSet
	{
	public:
		virtual ~Animation();

		//EventHandler OnEndAnimationReached;

		void Initialize();

		unsigned int ID() const;
		float TotalTime() const;
		float CurrentTime() const;
		bool GetLoop() const;

		void Update(float elapsedTime_);

		void Read (std::ifstream& is);
		void Read (const tinyxml2::XMLElement& el_);

	protected:
		Animation();
		Animation(const Animation& rsh);
		const Animation& operator = (const Animation& rsh);

		std::vector<AnimationEvent *> m_Events;

#if EDITOR
	public:
#endif
		void AddEvent(AnimationEvent *event_);

	private:
		unsigned int m_ID;
		
		float m_TotalTime; // total time of the animation
		float m_CurrentTime;
		bool m_AnimationEnded;
		bool m_Loop;
		bool m_bIsInitialized;

#if EDITOR

	public:
		void CurrentTime(float val);
		void RemoveEvent(AnimationEvent *event_);
		void SortEventList();

		void Write(tinyxml2::XMLElement *el_);
		void Write(std::ostream& os);

	private:
		static const int m_Version; // load version

#endif
		
	};
} // namespace CasaEngine

#endif // _ANIMATION_H_
