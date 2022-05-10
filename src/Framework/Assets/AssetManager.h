#pragma once

#include "CA_Assert.h"
#include "Log\LogManager.h"
#include "CA_Export.h"
#include "Asset.h"
#include "StringUtils.h"

#include <string>
#include <map>

namespace CasaEngine
{
	class CA_EXPORT AssetManager
	{
	public:
		~AssetManager();

		template<class T>
		T* GetAsset(std::string name_);

		template<class T>
		std::vector<T*> GetAssets();

		void AddAsset(std::string name, IAssetable *assetable);
		void AddAsset(Asset* asset_);
		bool Contains(std::string name);
		void Rename(const char* old_name, const char* new_name);
		void Clear();
		
	private:
		std::map<std::string, Asset*> m_Assets;

#if EDITOR
		void RemoveAsset(std::string name);
		void RemoveAsset(Asset* asset_);
#endif
	};

	template<class T>
	T* AssetManager::GetAsset(std::string name_)
	{
		auto asset = m_Assets.find(name_);
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
