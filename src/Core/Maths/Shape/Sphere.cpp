#include "Base.h"
#include "CA_Assert.h"

#include "Sphere.h"

namespace CasaEngine
{


/**
 *
 */
Sphere::Sphere(Vector3F center_, float radius_) :
	IShape(SPHERE)
{
	m_Center = center_;
	m_Radius = radius_;
}

/**
 *
 */
Sphere::~Sphere()
{
    
}

/**
 * 
 */
void Sphere::Read( const tinyxml2::XMLElement& el_ )
{

}

/**
 * 
 */
void Sphere::Read( std::ifstream& /*in*/ )
{
	
}

/**
 * 
 */
void Sphere::Write( const tinyxml2::XMLElement& /*node_*/ )
{
	
}

/**
 * 
 */
void Sphere::Write( std::ostream& /*os*/ )
{
	
}

} // namespace CasaEngine
