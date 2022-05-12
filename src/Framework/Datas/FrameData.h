#pragma once

#include "CA_Export.h"
#include <string>
#include "Assets/Assetable.h"

namespace CasaEngine
{
	class CA_EXPORT FrameData :
		public IAssetable
	{
	public:
		FrameData();
		FrameData(const FrameData& rsh);
		FrameData& operator=(const FrameData& rsh);
		~FrameData() override;

		float _duration;
		std::string _spriteId;
		//flip
		//blending
	};
}
