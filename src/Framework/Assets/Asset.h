#pragma once

#include <string>

#include "CA_Export.h"

#include "Assetable.h"
#include "CA_Assert.h"

namespace CasaEngine
{
	//A container which contains the parameters to load the asset 
	class CA_EXPORT Asset
	{
	public:
		Asset(std::string name, IAssetable* pObject);
		~Asset();

		std::string GetName() const;
		void SetName(std::string);

		template<class T>
		T* GetAsset();

		template<class T>
		bool IsTypeOf();

	private:
		IAssetable* m_pObject;
		std::string m_Name;

		void LoadAsset();
	};

	template<class T>
	T* Asset::GetAsset()
	{
		if (m_pObject == nullptr)
		{
			LoadAsset();
		}

		CA_ASSERT(m_pObject != nullptr, "Asset::GetAsset() : can't load the asset %s", GetName().c_str());
		T* val = dynamic_cast<T*>(m_pObject);
		CA_ASSERT(val != nullptr, "Asset::GetAsset() : the asset '%s' is not type of ", GetName().c_str(), typeid(T).name());
		return val;
	}

	template<class T>
	bool Asset::IsTypeOf()
	{
		if (m_pObject == nullptr)
		{
			LoadAsset();
		}

		CA_ASSERT(m_pObject != nullptr, "Asset::GetAsset() : can't load the asset %s", GetName().c_str());
		T* val = dynamic_cast<T*>(m_pObject);
		return val != nullptr;
	}
}
