#pragma once

#include "CA_Export.hpp"
#include  "Datas/FrameData.hpp"
#include  "Datas/AnimationData.hpp"

#include <vector>

namespace CasaEngine
{
	class CA_EXPORT Animation2DData :
		public AnimationData
	{
	public:
		Animation2DData();
		Animation2DData(const Animation2DData& rsh);
		Animation2DData& operator=(const Animation2DData& rsh);
		~Animation2DData() override;

		std::vector<FrameData> _frames;

		Animation2DData* Copy() const;
	};
}
