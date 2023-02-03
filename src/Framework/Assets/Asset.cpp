#include "Base.h"
#include "Log/LogManager.h"
#include "Asset.h"
#include <string>
#include "Assetable.h"
#include "Exceptions.h"
#include "CA_Assert.h"


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
