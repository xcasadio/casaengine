#ifndef _ANIMATIONENDEVENT_H_
#define _ANIMATIONENDEVENT_H_

#include <string>

#include "CA_Export.h"
#include <vector>
#include "AnimationEvent.h"
#include "Parsers\Xml\tinyxml2.h"

namespace CasaEngine
{
	class CA_EXPORT AnimationEndEvent : 
		public AnimationEvent
	{
	public:
		AnimationEndEvent();
		AnimationEndEvent(const AnimationEndEvent& rsh);
		const AnimationEndEvent& operator = (const AnimationEndEvent& rsh);
		~AnimationEndEvent();
		
		AnimationEvent* Copy() override;

		void Activate(Animation *pAnim_) override;

		void Read(std::ifstream& /*is*/);
		void Read(tinyxml2::XMLElement *el_);
		
#if EDITOR
	public:
		void Write(std::ostream& /*os*/) const;
		void Write(tinyxml2::XMLElement *el_) const;

	private:
		static const int m_Version; // load version
#endif
		
	};
}

#endif // _ANIMATIONENDEVENT_H_
