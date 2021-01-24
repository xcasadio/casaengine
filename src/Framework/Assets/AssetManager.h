#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_

#include "CA_Assert.h"
#include "Log\LogManager.h"
#include "CA_Export.h"
#include "Asset.h"
#include "StringUtils.h"

#include "Parsers/Xml/tinyxml2.h"


#include <string>
#include <map>
#include <iosfwd>

namespace CasaEngine
{
	class CA_EXPORT AssetManager :
		public AllocatedObject<AssetManager>
	{
	public:
		~AssetManager();

		template<class T>
		T* GetAsset(std::string name_);

		void AddAsset(Asset* asset_);
		bool Contains(std::string name);
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
		std::map<std::string, Asset*>::const_iterator asset = m_Assets.find(name_);
		CA_ASSERT(asset != m_Assets.end(),
			(CStringBuilder("AssetManager::GetAsset(): can't find the asset '")(name_)("'")).c_str());
		return asset->second->GetAsset<T>();
	}
	/*
	template<class T>
	std::vector<T*> AssetManager::GetAssets()
	{
		std::vector<T*> assets;

		for (auto pair : m_Assets)
		{
			pair.
		}
		
		return assets;
	}
	*/
}

#endif
