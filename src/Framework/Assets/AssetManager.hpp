#pragma once

#include  "CA_Assert.hpp"
#include  "Log/LogManager.hpp"
#include "CA_Export.hpp"
#include  "Asset.hpp"
#include  "StringUtils.hpp"

#include <string>
#include <map>

namespace CasaEngine
{
	class CA_EXPORT AssetManager
	{
	public:
		~AssetManager();

		template<class T>
		T* GetAsset(std::string name);

		template<class T>
		std::vector<T*> GetAssets();

		void AddAsset(std::string name, IAssetable* assetable);
		void AddAsset(Asset* asset);
		bool Contains(std::string name);
		void Rename(const char* oldName, const char* newName);
		void Clear();

	private:
		std::map<std::string, Asset*> m_Assets;

#if EDITOR
		void RemoveAsset(std::string name);
		void RemoveAsset(Asset* asset);
#endif
	};

	template<class T>
	T* AssetManager::GetAsset(const std::string name)
	{
		auto asset = m_Assets.find(name);
		CA_ASSERT(asset != m_Assets.end(), (CStringBuilder("AssetManager::GetAsset(): can't find the asset '")(name_)("'")).str().c_str());
		return asset->second->GetAsset<T>();
	}

	template<class T>
	std::vector<T*> AssetManager::GetAssets()
	{
		std::vector<T*> assets;

		for (auto pair : m_Assets)
		{
			if (pair.second->IsTypeOf<T>())
			{
				assets.push_back(pair.second->GetAsset<T>());
			}
		}

		return assets;
	}
}
