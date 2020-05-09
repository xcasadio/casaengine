#ifndef _ASSET_H_
#define _ASSET_H_

#include <iosfwd>
#include <string>

#include "CA_Export.h"
#include "Macro.h"
#include "Assetable.h"
#include "Parsers\Xml\tinyxml2.h"
#include "Resources\Resource.h"
#include "StringUtils.h"
#include "StringUtils.h"
#include "CA_Assert.h"

namespace CasaEngine
{
	/**
	 * A container which contains the parameters to load the asset
	 */
	class CA_EXPORT Asset : //public IResource
		public AllocatedObject<Asset>
	{
	public:
		Asset(std::string name_, IAssetable* pObject);
		Asset(const tinyxml2::XMLElement& node_);
		Asset(std::ifstream& in);
		~Asset();

		std::string GetName() const;

		template<class T>
		T* GetAsset();

		void Read(const tinyxml2::XMLElement& node_);
		void Read(std::ifstream& in);

//#ifdef EDITOR

		void Write(const tinyxml2::XMLElement* node_);
		void Write(std::ostream& os)const;

// #endif // EDITOR

	private:
		IAssetable* m_pObject;
		std::string m_Name;

		void LoadAsset();

	};

#include "Asset.inl"

}

#endif
