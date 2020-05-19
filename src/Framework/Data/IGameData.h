#ifndef IGAMEDATA_H_
#define IGAMEDATA_H_

#include "CA_Export.h"
#include "Assets/Assetable.h"

namespace CasaEngine
{
	typedef unsigned int GameDataClassID;

	class CA_EXPORT IGameData :
		public IAssetable
	{
	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IAssetable>(this));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IAssetable>(this));
		}
	};
}

#endif
