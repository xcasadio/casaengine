#pragma once

#include "CA_Export.h"

#include <string>
#include <vector>

#include "Datas/Animation2DData.h"

namespace CasaEngine
{
	class CA_EXPORT Animation2dLoader 
	{
	public:
		static std::vector<Animation2DData> LoadFromFile(const std::string& fileName);
	};
}
