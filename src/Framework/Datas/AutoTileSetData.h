#pragma once

#include "CA_Export.h"
#include "Assets/Assetable.h"

namespace CasaEngine
{
	class CA_EXPORT AutoTileSetData :
		public IAssetable
	{
	public:
		AutoTileSetData();
		AutoTileSetData(const AutoTileSetData& rsh);
		AutoTileSetData& operator=(const AutoTileSetData& rsh);
		~AutoTileSetData() override;

		AutoTileSetData* Copy() const;

		std::string spriteIds[6];

	//private:
	//	friend class cereal::access;
	//
	//	template <class Archive>
	//	void save(Archive& ar) const
	//	{
	//		ar(cereal::make_nvp("sprite_ids", spriteIds));
	//	}
	//
	//	template <class Archive>
	//	void load(Archive& ar)
	//	{
	//		ar(cereal::make_nvp("sprite_ids", spriteIds));
	//	}
	};
}
