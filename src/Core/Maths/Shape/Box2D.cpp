#include "Base.h"
#include "CA_Assert.h"

#include "Box2D.h"
#include "Parsers/Xml/tinyxml2.h"
#include <iosfwd>

namespace CasaEngine
{


/**
 *
 */
Box2D::Box2D(Vector2F size_, Vector3F center_) :
	IShape(BOX2D)
{

}

/**
 *
 */
Box2D::~Box2D()
{
    
}

Vector2F Box2D::Size() const
{
	return m_Size;
}

void Box2D::Size(Vector2F val )
{
	m_Size = val;
}

Vector3F Box2D::Center() const
{
	return m_Center;
}

void Box2D::Center(Vector3F val )
{
	m_Center = val;
}

/**
 * 
 */
void Box2D::Read(const tinyxml2::XMLElement& pEl_)
{
	//TODO


	const tinyxml2::XMLElement* pLocation_ = pEl_.FirstChildElement("Location");
	pLocation_->QueryFloatAttribute("x", &m_Center.x);
	pLocation_->QueryFloatAttribute("y", &m_Center.y);
	m_Center /= 100.0f; // TODO : to remove only for testing purpose
	//m_Offset.x = -m_Offset.x;
}

/**
 * 
 */
void Box2D::Read( std::ifstream& /*in*/ )
{
		
}

/**
 * 
 */
void Box2D::Write( const tinyxml2::XMLElement& /*node_*/ )
{
		
}

/**
 * 
 */
void Box2D::Write( std::ostream& /*os*/ )
{
		
}

}
