#pragma once

#include <string>
#include "CA_Export.h"

namespace CasaEngine
{
	class CA_EXPORT SpriteLoader
	{
	public:
		static void LoadFromFile(const std::string& fileName);
	};
}
