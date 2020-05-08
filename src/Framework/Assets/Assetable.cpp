
#include "Base.h"
#include "Assetable.h"

namespace CasaEngine
{

IAssetable::IAssetable()
{
}

IAssetable::~IAssetable()
{
}


std::string IAssetable::GetName() const 
{ 
	return m_Name; 
}

//#if EDITOR

void IAssetable::SetName(std::string val) 
{ 
	m_Name = val; 
}

//#endif // EDITOR

void IAssetable::Read(const tinyxml2::XMLElement& node_)
{
	m_Name = node_.Attribute("name");
}

void IAssetable::Read(std::ifstream& in)
{

}

void IAssetable::Write(tinyxml2::XMLElement& node_)
{

}

void IAssetable::Write(std::ostream& os)
{

}

}
