#include "Assetable.h"

namespace CasaEngine
{
	std::string IAssetable::GetName() const
	{
		return m_Name;
	}


	IAssetable& IAssetable::operator = (const IAssetable& rsh)
	{
		m_Name = rsh.m_Name;
		return *this;
	}

//#if EDITOR

	void IAssetable::SetName(std::string val)
	{
		m_Name = val;
	}

//#endif
}
