#pragma once

#include "CA_Export.h"
#include "Assets/Assetable.h"
#include <Animations/AnimationType.h>

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
