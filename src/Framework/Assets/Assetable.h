#ifndef _ASSETABLE_H_
#define _ASSETABLE_H_

#include "CA_Export.h"
#include <string>
#include "Memory/MemoryAllocation.h"

#include <cereal/cereal.hpp>
#include <cereal/details/helpers.hpp>
#include <cereal/types/string.hpp>

namespace CasaEngine
{
	//Each object can be stored inherit from this class
	class CA_EXPORT IAssetable :
		public AllocatedObject<IAssetable>
	{
	public:
		virtual ~IAssetable();
		
		std::string GetName() const;
//#ifdef EDITOR
		void SetName(std::string val); // Only EDITOR
//#endif

	protected:
		IAssetable() = default;
		
	private:
		std::string m_Name;

	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(CEREAL_NVP(m_Name));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(CEREAL_NVP(m_Name));
		}
	};
}

#endif
