
#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_

#include "CA_Assert.h"
#include "Log\LogManager.h"
#include "CA_Export.h"
#include "Asset.h"
#include "StringUtils.h"
#include "Singleton.h"
#include "Parsers/Xml/tinyxml2.h"
#include "Macro.h"

#include <string>
#include <map>
#include <iosfwd>


namespace CasaEngine
{
	/*
	 *	
	 */
	class CA_EXPORT AssetManager :
		public CSingleton<AssetManager>
	{
		MAKE_SINGLETON(AssetManager)

	public:
		template<class T>
		T* GetAsset(std::string name_);

		void AddAsset(Asset *asset_);

		/**
		 * Delete all asset
		 */
		void Clear();

		void Load(const tinyxml2::XMLElement* node_);
		void Load(std::ifstream& in);

//#ifdef EDITOR

		void Write(const tinyxml2::XMLElement* node_);
		void Write(std::ostream& os)const;

// #endif // EDITOR

	private:
		//ID
		std::map<std::string, Asset *> m_Assets;
		
	}; // class AssetManager

	#include "AssetManager.inl"

} // namespace CasaEngine

#endif // _ASSETMANAGER_H_
