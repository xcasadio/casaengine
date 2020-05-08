#include "Base.h"
#include "CA_Assert.h"

#include "IShape.h"
#include "Parsers\Xml\tinyxml2.h"
#include "Memory\MemoryAllocation.h"
#include "Box2D.h"
#include "Exceptions.h"
#include "Circle.h"
#include "Polygon.h"

namespace CasaEngine
{


/**
 *
 */
IShape::IShape(ShapeType type_)
{
	m_ShapeType = type_;
}

/**
 *
 */
IShape::~IShape()
{
    
}

/**
 * 
 */
void IShape::Read( const tinyxml2::XMLElement& el_ )
{

}

/**
 * 
 */
void IShape::Read( std::ifstream& /*in*/ )
{
	
}

/**
 * 
 */
void IShape::Write( const tinyxml2::XMLElement& /*node_*/ )
{
	
}

/**
 * 
 */
void IShape::Write( std::ostream& /*os*/ )
{
	
}

IShape *IShape::LoadShape( const tinyxml2::XMLElement& pElt_ )
{
	IShape *pShape = nullptr;
	const tinyxml2::XMLElement *pElem, *pChild;

	// TODO convert in int
	const char *pType = pElt_.Attribute("type"); 
	int type = -1;
	//pElt_->QueryIntAttribute("type", &type);

	// TODO : only for testing
	if (pType == nullptr)
	{
		return nullptr;
	}

	// TODO : only for testing
	if (strcmp(pType, "Box2D") == 0)
	{
		type = BOX2D;
	}
	else if (strcmp(pType, "Circle") == 0)
	{
		type = CIRCLE2D;
	}
	else if (strcmp(pType, "Polygone") == 0)
	{
		type = POLYGON;
	}	

	switch (type)
	{
	case BOX2D:
		pShape = NEW_AO Box2D();
		break;

	case CIRCLE2D:
		pShape = NEW_AO Circle();
		break;

	case POLYGON:
		pShape = NEW_AO Polygon();
		break;

	default:
		throw CUnsupported("IShape::LoadShape() : type unsupported");
		break;
	}

	if (pShape != nullptr)
	{
		pShape->Read(pElt_);
	}

	return pShape;
}

ShapeType IShape::Type() const
{
	return m_ShapeType;
}

}
