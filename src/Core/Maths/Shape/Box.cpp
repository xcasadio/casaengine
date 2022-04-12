#include "Base.h"
#include "Box.h"

namespace CasaEngine
{
	Box::Box(Vector3 size_, Vector3 center_) :
		IShape(ShapeType::BOX)
	{
		m_Center = center_;
		m_Size = size_;
	}

	Box::Box(const Box& rsh) :
		IShape(ShapeType::BOX)
	{
		*this = rsh;
	}

	Box& Box::operator=(const Box& rsh)
	{
		m_Center = rsh.m_Center;
		m_Size = rsh.m_Size;

		IShape::operator=(rsh);

		return *this;
	}

	IShape* Box::Copy()
	{
		return new Box(*this);
	}

	Vector3 Box::Size() const
	{
		return m_Size;
	}

	void Box::Size(Vector3 val)
	{
		m_Size = val;
	}

	Vector3 Box::Center() const
	{
		return m_Center;
	}

	void Box::Center(Vector3 val)
	{
		m_Center = val;
	}
}