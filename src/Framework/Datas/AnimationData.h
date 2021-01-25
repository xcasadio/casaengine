#ifndef _AnimationData_H_
#define _AnimationData_H_

#include "CA_Export.h"
#include <string>
#include "Assets/Assetable.h"
#include <Animations/AnimationType.h>

#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

namespace CasaEngine
{
	class CA_EXPORT AnimationData :
		public IAssetable
	{
	public:
		AnimationData();
		~AnimationData();
		
		AnimationType GetAnimationType() const;
		void SetAnimationType(AnimationType type);

	private:
		AnimationType m_AnimationType;

	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IAssetable>(this));
			ar(cereal::make_nvp("animation_type", m_AnimationType));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IAssetable>(this));
			ar(cereal::make_nvp("animation_type", m_AnimationType));
		}
	};
}

#endif
