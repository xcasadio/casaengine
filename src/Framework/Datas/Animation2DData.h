#ifndef _ANIMATION2DDATA_H_
#define _ANIMATION2DDATA_H_

#include "CA_Export.h"
#include <string>
#include "Assets/Assetable.h"
#include "Datas/FrameData.h"

#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

namespace CasaEngine
{
	class CA_EXPORT Animation2DData :
		public IAssetable
	{
	public:
		Animation2DData();
		~Animation2DData();

		std::vector<FrameData *> GetFrames();
		void AddFrame(FrameData* frame);

	private:
		std::vector<FrameData*> m_Frames;

	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IAssetable>(this));
			ar(cereal::make_nvp("frames", m_Frames));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IAssetable>(this));
			ar(cereal::make_nvp("frames", m_Frames));
		}
	};
}

#endif
