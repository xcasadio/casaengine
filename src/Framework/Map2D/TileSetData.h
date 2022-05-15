#pragma once

#include "CA_Export.h"
#include "TileSetData.h"
#include "Maths/Vector2.h"

namespace CasaEngine
{
	class CA_EXPORT TileSetData
	{
	public:
		TileSetData() = default;
		~TileSetData() = default;
		TileSetData(const TileSetData& rsh) = default;
		TileSetData& operator=(const TileSetData& rsh) = default;
		TileSetData(TileSetData&& rsh) = default;
		TileSetData& operator=(TileSetData&& rsh) = default;

		std::string spriteSheetFileName;
		Vector2I tileSize;
	};
}
