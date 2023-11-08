#pragma once

#include "CA_Export.hpp"
#include <string>
#include  "Assets/Assetable.hpp"

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
