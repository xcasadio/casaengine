#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_

#include "CA_Assert.h"
#include "Log\LogManager.h"
#include "CA_Export.h"
#include "Asset.h"
#include "StringUtils.h"

#include "Parsers/Xml/tinyxml2.h"
#include "Macro.h"

#include <string>
#include <map>
#include <iosfwd>

namespace CasaEngine
{
	class CA_EXPORT AssetManager
	{
	public:
		~AssetManager();

		template<class T>
		T* GetAsset(std::string name_);

		void AddAsset(Asset* asset_);
		bool Contains(std::string name);
		void Clear();

		void Load(const tinyxml2::XMLElement* node_);
		void Load(std::ifstream& in);

		//#ifdef EDITOR

		void Write(const tinyxml2::XMLElement* node_);
		void Write(std::ostream& os)const;

		// #endif

	private:
		std::map<std::string, Asset*> m_Assets;
	};

#include "AssetManager.inl"

}

#endif
