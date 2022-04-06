#ifndef _ASSETABLE_H_
#define _ASSETABLE_H_

#include "CA_Export.h"
#include <string>

#include <cereal/cereal.hpp>
#include <cereal/types/polymorphic.hpp>

namespace CasaEngine
{
	class CA_EXPORT IAssetable
	{
	public:
		virtual ~IAssetable();
		
		std::string GetName() const;
//#ifdef EDITOR
		void SetName(std::string val); // Only EDITOR
//#endif

	protected:
		IAssetable() = default;
		const IAssetable& operator = (const IAssetable& rsh);
		
	private:
		std::string m_Name;

	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::make_nvp("asset_name", m_Name));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::make_nvp("asset_name", m_Name));
		}
	};
}

//CEREAL_REGISTER_TYPE_WITH_NAME(CasaEngine::IAssetable, "asset");

#endif
