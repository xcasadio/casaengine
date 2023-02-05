#pragma once

#include "CA_Export.h"
#include "AnimationEvent.h"

namespace CasaEngine
{
	class CA_EXPORT AnimationEndEvent :
		public AnimationEvent
	{
	public:
		AnimationEndEvent();
		AnimationEndEvent(const AnimationEndEvent& rsh);
		AnimationEndEvent& operator = (const AnimationEndEvent& rsh);
		~AnimationEndEvent() override;

		AnimationEvent* Copy() override;

		void Activate(Animation* pAnim_) override;

		//private:
		//	friend class cereal::access;
		//
		//	template <class Archive>
		//	void load(Archive& ar)
		//	{
		//		ar(cereal::base_class<AnimationEvent>(this));
		//	}
		//
		//	template <class Archive>
		//	void save(Archive& ar) const
		//	{
		//		ar(cereal::base_class<AnimationEvent>(this));
		//		ar(cereal::make_nvp("type", "AnimationEndEvent"));
		//	}

#if EDITOR
	private:
		static const int m_Version; // load version
#endif
	};
}
