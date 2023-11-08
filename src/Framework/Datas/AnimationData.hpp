#pragma once

#include "CA_Export.hpp"
#include  "Assets/Assetable.hpp"
#include <Animations/AnimationType.hpp>

namespace CasaEngine
{
	class CA_EXPORT AnimationData :
		public IAssetable
	{
	public:
		AnimationData();
		~AnimationData() override;

		AnimationType _animationType;

	protected:
		AnimationData(const AnimationData& rsh);
		AnimationData& operator=(const AnimationData& rsh);
	};
}
