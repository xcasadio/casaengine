
#include "Base.h"
#include "Log/LogManager.h"
#include "Asset.h"
#include "Parsers/Xml/tinyxml2.h"
#include "Parsers/Xml/XMLHelper.h"
#include <string>
#include "Assetable.h"
#include <iosfwd>
#include "Resources/ResourceManager.h"
#include "Exceptions.h"
#include "CA_Assert.h"
#include "Memory/MemoryAllocation.h"

using namespace tinyxml2;

namespace CasaEngine
{


Asset::Asset(std::string name_, IAssetable *pObject)
{
	CA_ASSERT(pObject != nullptr, "Asset() : IAssetable is nullptr");

	m_pObject = pObject;
	m_Name = name_;
	//ResourceManager::Instance().Add(name_, this);
}

Asset::Asset(const tinyxml2::XMLElement& node_) :
	m_pObject(nullptr)
{
	Read(node_);
}

Asset::Asset(std::ifstream& in) :
	m_pObject(nullptr)
{
	Read(in);
}

Asset::~Asset()
{
	if (nullptr != m_pObject) DELETE_AO m_pObject;
}


std::string Asset::GetName() const
{
	return m_Name;
}

void Asset::LoadAsset()
{
	throw NEW_AO CNotImplementedException("Asset::LoadAsset()");
}

void Asset::Read(const XMLElement& /*node_*/)
{

}

void Asset::Read(std::ifstream& /*in*/)
{

}

//#ifdef EDITOR

void Asset::Write(const XMLElement* /*node_*/)
{

}

void Asset::Write(std::ostream& /*os*/) const
{

}


// #endif // EDITOR

} // namespace CasaEngine
