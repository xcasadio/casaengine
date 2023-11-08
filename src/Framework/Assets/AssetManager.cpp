#include  "Base.hpp"
#include  "Log/LogManager.hpp"
#include  "AssetManager.hpp"
#include  "Asset.hpp"
#include  "StringUtils.hpp"
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
		m_Assets.insert(std::make_pair(name, new Asset(name, assetable)));
	}

	void AssetManager::AddAsset(Asset* asset)
	{
		CA_ASSERT(m_Assets.find(asset->GetName()) == m_Assets.end(), "AssetManager::AddAsset(): asset '%s' already exist", asset->GetName().c_str());
		m_Assets.insert(std::make_pair(asset->GetName(), asset));
	}

	bool AssetManager::Contains(std::string name)
	{
		return m_Assets.find(name) != m_Assets.end();
	}

	void AssetManager::Rename(const char* oldName, const char* newName)
	{
		const auto it = m_Assets.find(oldName);
		const auto asset = it->second;
		m_Assets.erase(it);

		asset->SetName(newName);
		AddAsset(asset);
	}

	void AssetManager::Clear()
	{
		for (auto it = m_Assets.begin(); it != m_Assets.end(); ++it)
		{
			delete it->second;
		}
	}

#if EDITOR
	void AssetManager::RemoveAsset(std::string name)
	{
		auto it = m_Assets.find(name);
		CA_ASSERT(it == m_Assets.end(), "AssetManager::AddAsset(): asset '%s' doesn't exist", name.c_str());
		m_Assets.erase(it);
	}

	void AssetManager::RemoveAsset(Asset* asset)
	{
		RemoveAsset(asset->GetName());
	}
#endif
}
