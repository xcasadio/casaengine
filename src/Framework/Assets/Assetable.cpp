#include  "Assetable.hpp"

namespace CasaEngine
{
	std::string IAssetable::GetName() const
	{
		return m_Name;
	}


	IAssetable& IAssetable::operator = (const IAssetable& rsh)
		= default;

	//#if EDITOR

	void IAssetable::SetName(std::string val)
	{
		m_Name = val;
	}

	//#endif
}
