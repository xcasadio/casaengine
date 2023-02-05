#pragma once

#include <string>

#include "CA_Export.h"
#include "AnimationEvent.h"

namespace CasaEngine
{
	class CA_EXPORT SetFrameEvent :
		public AnimationEvent
	{
	public:
		SetFrameEvent();
		SetFrameEvent(const SetFrameEvent& rsh);
		SetFrameEvent& operator = (const SetFrameEvent& rsh);
		~SetFrameEvent() override;

		AnimationEvent* Copy() override;

		void Activate(Animation* pAnim_) override;

		const char* FrameID() const;
		void FrameID(const char* val);

	private:
		std::string m_FrameID;

		//private:
		//	friend class cereal::access;
		//
		//	template <class Archive>
		//	void load(Archive& ar)
		//	{
		//		ar(cereal::base_class<AnimationEvent>(this));
		//		ar(cereal::make_nvp("sprite_name", m_FrameID));
		//	}
		//
		//	template <class Archive>
		//	void save(Archive& ar) const
		//	{
		//		ar(cereal::base_class<AnimationEvent>(this));
		//		ar(cereal::make_nvp("sprite_name", m_FrameID));
		//	}

#if EDITOR
	private:
		static const int m_Version; // load version
#endif
	};
}
