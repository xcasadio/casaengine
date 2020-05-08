
#include "Base.h"
#include "IGameData.h"


namespace CasaEngine
{

/**
 * 
 */
IGameData::IGameData()
{
}

/**
 * 
 */
IGameData::~IGameData()
{
}

/**
 * 
 */
void IGameData::Read(const tinyxml2::XMLElement& xmlElt)
{
	IAssetable::Read(xmlElt);
}

/**
 * 
 */
void IGameData::Read(std::ifstream& is)
{
	IAssetable::Read(is);
}

/**
 * 
 */
void IGameData::Write(tinyxml2::XMLElement& xmlElt)
{
	IAssetable::Write(xmlElt);
}

/**
 * 
 */
void IGameData::Write(std::ostream& os)
{
	IAssetable::Write(os);
}

}
