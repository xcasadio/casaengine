#include "Base.h"
#include "Log/LogManager.h"
#include "AssetManager.h"
#include "Asset.h"
#include "Parsers/Xml/tinyxml2.h"
#include "Parsers/Xml/XMLHelper.h"
#include "StringUtils.h"
#include <string>
#include <map>
#include <string>

namespace CasaEngine
{
	AssetManager::~AssetManager()
	{
		Clear();
	}

	void AssetManager::AddAsset(std::string name, IAssetable* assetable)
	{
		CA_ASSERT(m_Assets.find(name) == m_Assets.end(), "AssetManager::AddAsset(): asset '%s' already exist", name.c_str());
		m_Assets.insert(std::make_pair(name, NEW_AO Asset(name, assetable)));
	}
	
	void AssetManager::AddAsset(Asset* asset_)
	{
		CA_ASSERT(m_Assets.find(asset_->GetName()) == m_Assets.end(), "AssetManager::AddAsset(): asset '%s' already exist", asset_->GetName().c_str());
		m_Assets.insert(std::make_pair(asset_->GetName(), asset_));
	}

	bool AssetManager::Contains(std::string name)
	{
		return m_Assets.find(name) != m_Assets.end();
	}

	void AssetManager::Rename(const char* old_name, const char* new_name)
	{
		const auto it = m_Assets.find(old_name);
		const auto asset = it->second;
		m_Assets.erase(it);
		
		asset->SetName(new_name);
		AddAsset(asset);
	}
	
	void AssetManager::Clear()
	{
		for (auto it = m_Assets.begin(); it != m_Assets.end(); ++it)
		{
			DELETE_AO it->second;
		}
	}

#if EDITOR
	void AssetManager::RemoveAsset(std::string name)
	{
		auto it = m_Assets.find(name);
		CA_ASSERT(it == m_Assets.end(), "AssetManager::AddAsset(): asset '%s' doesn't exist", name.c_str());
		m_Assets.erase(it);
	}
	
	void AssetManager::RemoveAsset(Asset* asset_)
	{
		RemoveAsset(asset_->GetName());
	}
#endif
}
