#pragma once

#include "CA_Export.h"
#include <string>

namespace CasaEngine
{
	class CA_EXPORT IAssetable
	{
	public:
		virtual ~IAssetable() = default;
		IAssetable& operator = (const IAssetable & rsh);
		
		std::string GetName() const;
//#ifdef EDITOR
		void SetName(std::string val); // Only EDITOR
//#endif

	protected:
		IAssetable() = default;
		
	private:
		std::string m_Name;
	};
}
