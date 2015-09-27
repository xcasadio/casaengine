
#include "Base.h"
#include "Log/LogManager.h"
#include "AssetManager.h"
#include "Asset.h"
#include "Parsers/Xml/tinyxml2.h"
#include "Parsers/Xml/XMLHelper.h"
#include "StringUtils.h"
#include <iosfwd>
#include <string>
#include <map>
#include <string>
#include "Macro.h"
#include "CA_Assert.h"

using namespace tinyxml2;

namespace CasaEngine
{

SINGLETON_IMPL(AssetManager)

/**
 * 
 */
void AssetManager::AddAsset(Asset *asset_)
{
	CA_ASSERT(m_Assets.find(asset_->GetName()) == m_Assets.end(), 
		"AssetManager::AddAsset(): asset '%s' already exist", asset_->GetName().c_str());

	m_Assets.insert(std::make_pair(asset_->GetName(), asset_));
}

/**
 * 
 */
void AssetManager::Clear()
{
	std::map<std::string, Asset *>::iterator it;

	for (it = m_Assets.begin(); it != m_Assets.end(); it++)
	{
		DELETE_AO it->second;
	}
}

/**
 * 
 */
void AssetManager::Load(const XMLElement* /*node_*/)
{

}

/**
 * 
 */
void AssetManager::Load(std::ifstream& /*in*/)
{

}

#ifdef EDITOR

/**
 * 
 */
void AssetManager::Write(const XMLElement* /*node_*/)
{

}

/**
 * 
 */
void AssetManager::Write(std::ostream& /*os*/) const
{

}

#endif // EDITOR

} // namespace CasaEngine
