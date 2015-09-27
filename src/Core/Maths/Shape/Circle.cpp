#include "Base.h"
#include "CA_Assert.h"

#include "Circle.h"

namespace CasaEngine
{


/**
 *
 */
Circle::Circle(float radius_, Vector3F center_) :
	IShape(CIRCLE2D)
{
	m_Radius = radius_;
	m_Center = center_;
}

/**
 *
 */
Circle::~Circle()
{
    
}

/**
 * 
 */
CasaEngine::Vector3F Circle::Center() const
{
	return m_Center;
}

/**
 * 
 */
void Circle::Center( Vector3F val )
{
	m_Center = val;
}

/**
 * 
 */
float Circle::Radius() const
{
	return m_Radius;
}

/**
 * 
 */
void Circle::Radius( float val )
{
	m_Radius = val;
}


/**
 * 
 */
void Circle::Read( const tinyxml2::XMLElement& pEl_ )
{
	pEl_.QueryFloatAttribute("radius", &m_Radius);
	m_Radius /= 100.0f; // TODO : to remove only for testing purpose

	const tinyxml2::XMLElement* pLocation_ = pEl_.FirstChildElement("Location");
	pLocation_->QueryFloatAttribute("x", &m_Center.x);
	pLocation_->QueryFloatAttribute("y", &m_Center.y);
	m_Center /= 100.0f; // TODO : to remove only for testing purpose
	//m_Center.x = -m_Center.x;
}

/**
 * 
 */
void Circle::Read( std::ifstream& /*in*/ )
{
	
}

/**
 * 
 */
void Circle::Write( const tinyxml2::XMLElement& /*node_*/ )
{
		
}

/**
 * 
 */
void Circle::Write( std::ostream& /*os*/ )
{
		
}

} // namespace CasaEngine
