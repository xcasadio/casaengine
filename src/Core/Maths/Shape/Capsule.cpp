#include "Base.h"
#include "CA_Assert.h"

#include "Capsule.h"

namespace CasaEngine
{


/**
 *
 */
Capsule::Capsule() :
	IShape(CAPSULE)
{

}

/**
 *
 */
Capsule::~Capsule()
{
    
}

/**
 * 
 */
void Capsule::Read( const tinyxml2::XMLElement& el_ )
{

}

/**
 * 
 */
void Capsule::Read( std::ifstream& /*in*/ )
{
		
}

/**
 * 
 */
void Capsule::Write( const tinyxml2::XMLElement& /*node_*/ )
{
		
}

/**
 * 
 */
void Capsule::Write( std::ostream& /*os*/ )
{
		
}

} // namespace CasaEngine
