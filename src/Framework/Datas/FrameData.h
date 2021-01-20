#ifndef _FRAMEDATA_H_
#define _FRAMEDATA_H_

#include "CA_Export.h"
#include <string>
#include "Assets/Assetable.h"

#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>

namespace CasaEngine
{
	class CA_EXPORT FrameData :
		public IAssetable
	{
	public:
		FrameData();
		~FrameData();

		float GetDuration();
		void SetDuration(float duration);
		std::string GetSpriteId();
		void SetSpriteId(std::string spriteId);

	private:
		float m_Duration;
		std::string m_SpriteId;
		//flip
		//blending

	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::base_class<IAssetable>(this));
			ar(cereal::make_nvp("duration", m_Duration));
			ar(cereal::make_nvp("sprite_id", m_SpriteId));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::base_class<IAssetable>(this));
			ar(cereal::make_nvp("duration", m_Duration));
			ar(cereal::make_nvp("sprite_id", m_SpriteId));
		}
	};
}

#endif
