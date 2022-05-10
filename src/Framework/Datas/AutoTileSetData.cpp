#include "Base.h"

#include "AutoTileSetData.h"


namespace CasaEngine
{
	AutoTileSetData::AutoTileSetData()
	{

	}

	AutoTileSetData::AutoTileSetData(const AutoTileSetData& rsh)
		: IAssetable(rsh)
	{
		*this = rsh;
	}

	AutoTileSetData& AutoTileSetData::operator=(const AutoTileSetData& rsh)
	{
		IAssetable::operator=(rsh);
		for (int i = 0; i < 6; ++i)
		{
			spriteIds[i] = rsh.spriteIds[i];
		}
		return *this;
	}

	AutoTileSetData::~AutoTileSetData()
	{
		
	}
	
	AutoTileSetData* AutoTileSetData::Copy() const
	{
		return new AutoTileSetData(*this);
	}

}
