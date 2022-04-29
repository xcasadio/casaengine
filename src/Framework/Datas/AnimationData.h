#pragma once

#include "CA_Export.h"
#include "Assets/Assetable.h"
#include <Animations/AnimationType.h>

#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>

namespace CasaEngine
{
	class CA_EXPORT AnimationData :
		public IAssetable
	{
	public:
		AnimationData();
		~AnimationData() override;
		
		AnimationType GetAnimationType() const;
		void SetAnimationType(AnimationType type);

	protected:
		AnimationData(const AnimationData& rsh);
		AnimationData& operator=(const AnimationData& rsh);

	private:
		AnimationType m_AnimationType;

	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::make_nvp("asset", cereal::base_class<IAssetable>(this)));
			ar(cereal::make_nvp("animation_type", m_AnimationType));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::make_nvp("asset", cereal::base_class<IAssetable>(this)));
			ar(cereal::make_nvp("animation_type", m_AnimationType));
		}
	};
}
