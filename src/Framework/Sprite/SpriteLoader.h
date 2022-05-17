#pragma once

#include <string>
#include <vector>
#include "CA_Export.h"
#include "Datas/SpriteData.h"

namespace CasaEngine
{
	class CA_EXPORT SpriteLoader
	{
	public:
		static std::vector<SpriteData> LoadFromFile(const std::string& fileName);
	};
}
