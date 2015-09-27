#include "Base.h"
#include "CA_Assert.h"

#include "Polygon.h"

namespace CasaEngine
{


/**
 *
 */
Polygon::Polygon() :
	IShape(POLYGON)
{

}

/**
 *
 */
Polygon::~Polygon()
{
    
}

/**
 * 
 */
void Polygon::Read(const tinyxml2::XMLElement& pEl_)
{
	const tinyxml2::XMLElement* pPointList_ = pEl_.FirstChildElement("PointList");
	const tinyxml2::XMLElement *pPoint;

	pPoint = pPointList_->FirstChildElement("Point");
	m_PointList.clear();

	while (pPoint != nullptr)
	{
		Vector2F point;
		pPoint->QueryFloatAttribute("x", &point.x);
		pPoint->QueryFloatAttribute("y", &point.y);
		m_PointList.push_back(point);
		pPoint = pPoint->NextSiblingElement();
	}
}

/**
 * 
 */
void Polygon::Read( std::ifstream& /*in*/ )
{
		
}

/**
 * 
 */
void Polygon::Write( const tinyxml2::XMLElement& /*node_*/ )
{
		
}

/**
 * 
 */
void Polygon::Write( std::ostream& /*os*/ )
{
		
}

} // namespace CasaEngine
