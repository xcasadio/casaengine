#include "Base.h"
#include "Log/LogManager.h"
#include "Asset.h"
#include "Parsers/Xml/tinyxml2.h"
#include "Parsers/Xml/XMLHelper.h"
#include <string>
#include "Assetable.h"
#include "Exceptions.h"
#include "CA_Assert.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	Asset::Asset(std::string name_, IAssetable* pObject)
	{
		CA_ASSERT(pObject != nullptr, "Asset() : IAssetable is nullptr");

		m_pObject = pObject;
		m_Name = name_;
		//Game::Instance().GetResourceManager().Add(name_, this);
	}

	Asset::~Asset()
	{
		DELETE_AO m_pObject;
	}

	std::string Asset::GetName() const
	{
		return m_Name;
	}

	void Asset::LoadAsset()
	{
		throw NEW_AO CNotImplementedException("Asset::LoadAsset()");
	}
}
