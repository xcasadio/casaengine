#pragma once

#include "CA_Export.hpp"

#include <string>
#include <vector>

#include  "Datas/Animation2DData.hpp"

namespace CasaEngine
{
	class CA_EXPORT Animation2dLoader 
	{
	public:
		static std::vector<Animation2DData> LoadFromFile(const std::string& fileName);
	};
}
