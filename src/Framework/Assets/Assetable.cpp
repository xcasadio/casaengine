#include "Assetable.h"

namespace CasaEngine
{
	IAssetable::~IAssetable()
	{
	}

	std::string IAssetable::GetName() const
	{
		return m_Name;
	}

//#if EDITOR

	void IAssetable::SetName(std::string val)
	{
		m_Name = val;
	}

//#endif
}
