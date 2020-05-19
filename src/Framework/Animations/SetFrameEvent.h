#ifndef _CHANGEFRAMEEVENT_H_
#define _CHANGEFRAMEEVENT_H_

#include <string>

#include "CA_Export.h"
#include <vector>
#include "AnimationEvent.h"
#include "Parsers\Xml\tinyxml2.h"

namespace CasaEngine
{
	class CA_EXPORT SetFrameEvent :
		public AnimationEvent
	{
	public:
		SetFrameEvent();
		SetFrameEvent(const SetFrameEvent& rsh);
		const SetFrameEvent& operator = (const SetFrameEvent& rsh);
		~SetFrameEvent();

		AnimationEvent* Copy() override;

		void Activate(Animation* pAnim_);

		const char* FrameID() const;
		void FrameID(const char* val);

		void Read(std::ifstream& /*is*/);
		void Read(tinyxml2::XMLElement* el_);

	private:
		std::string m_FrameID;

	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<AnimationEvent>(this));
			ar(cereal::make_nvp("sprite_name", m_FrameID));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<AnimationEvent>(this));
			ar(cereal::make_nvp("sprite_name", m_FrameID));
		}

#if EDITOR
	private:
		static const int m_Version; // load version
#endif
	};
}

#endif
