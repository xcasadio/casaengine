
#ifndef _ANIMATIONEVENT_H_
#define _ANIMATIONEVENT_H_

#include <string>
#include "CA_Export.h"
#include <vector>
#include "Parsers\Xml\tinyxml2.h"
#include <iosfwd>
#include "Memory\MemoryAllocation.h"

namespace CasaEngine
{
	class Animation;

	/**
	 * 
	 */
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

		void Read(std::ifstream& /*is*/);
		void Read(tinyxml2::XMLElement *el_);

	private:
		unsigned int m_ID;
		float m_Time;

		//std::vector<IEvent> m_Events;

#if EDITOR
	public:

		void Write(std::ostream& /*os*/) const;
		void Write(tinyxml2::XMLElement *el_) const;

	private:
		static const int m_Version; // load version

#endif
		
	};
}

#endif // _ANIMATIONEVENT_H_
