#include "IShape.h"

namespace CasaEngine
{
	IShape::IShape(ShapeType type_)
	{
		m_ShapeType = type_;
	}

	IShape& IShape::operator=(const IShape& rsh)
	{
		m_ShapeType = rsh.m_ShapeType;
		return *this;
	}

	IShape::~IShape()
	{
	}

	ShapeType IShape::Type() const
	{
		return m_ShapeType;
	}
}