#include  "Base.hpp"
#include  "Log/LogManager.hpp"
#include  "Asset.hpp"
#include <string>
#include  "Assetable.hpp"
#include  "Exceptions.hpp"
#include  "CA_Assert.hpp"


namespace CasaEngine
{
	Asset::Asset(std::string name, IAssetable* pObject)
	{
		CA_ASSERT(pObject != nullptr, "Asset() : IAssetable is nullptr");

		m_pObject = pObject;
		m_Name = name;
		//Game::Instance().GetResourceManager().Add(name_, this);
	}

	Asset::~Asset()
	{
		delete m_pObject;
	}

	std::string Asset::GetName() const
	{
		return m_Name;
	}

	void Asset::SetName(std::string name)
	{
		m_Name = name;
		m_pObject->SetName(name);
	}

	void Asset::LoadAsset()
	{
		throw new NotImplementedException("Asset::LoadAsset()");
	}
}
