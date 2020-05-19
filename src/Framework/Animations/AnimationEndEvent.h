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
		
	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<AnimationEvent>(this));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<AnimationEvent>(this));
			ar(cereal::make_nvp("type", "AnimationEndEvent"));
		}
		
#if EDITOR
	private:
		static const int m_Version; // load version
#endif
	};
}

#endif
