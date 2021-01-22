#include "Base.h"
#include "CA_Assert.h"

#include "IShape.h"
#include "Parsers\Xml\tinyxml2.h"
#include "Memory\MemoryAllocation.h"
#include "Exceptions.h"

namespace CasaEngine
{
	IShape::IShape(ShapeType type_)
	{
		m_ShapeType = type_;
	}

	IShape::~IShape()
	{

	}

	ShapeType IShape::Type() const
	{
		return m_ShapeType;
	}
}
