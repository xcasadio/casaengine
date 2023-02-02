#include "IShape.h"

namespace CasaEngine
{
	IShape::IShape(ShapeType type_)
	{
		m_ShapeType = type_;
	}

	IShape& IShape::operator=(const IShape& rsh)
		= default;

	IShape::~IShape()
		= default;

	ShapeType IShape::Type() const
	{
		return m_ShapeType;
	}
}