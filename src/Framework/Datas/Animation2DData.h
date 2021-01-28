#ifndef _ANIMATION2DDATA_H_
#define _ANIMATION2DDATA_H_

#include "CA_Export.h"
#include "Datas/FrameData.h"
#include "Datas/AnimationData.h"

#include <cereal/access.hpp>

namespace CasaEngine
{
	class CA_EXPORT Animation2DData :
		public AnimationData
	{
	public:
		Animation2DData();
		Animation2DData(const Animation2DData& rsh);
		Animation2DData& operator=(const Animation2DData& rsh);
		~Animation2DData();

		std::vector<FrameData>& GetFrames();
		void AddFrame(FrameData& frame);

		Animation2DData* Copy() const;

	private:

		std::vector<FrameData> m_Frames;

	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::make_nvp("anim", cereal::base_class<AnimationData>(this)));
			ar(cereal::make_nvp("frames", m_Frames));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::make_nvp("anim", cereal::base_class<AnimationData>(this)));
			ar(cereal::make_nvp("frames", m_Frames));
		}
	};
}

#endif
