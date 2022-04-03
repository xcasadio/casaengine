#include "Base.h"
#include "Box.h"

namespace CasaEngine
{
	Box::Box(Vector3F size_, Vector3F center_) :
		IShape(BOX)
	{
		m_Center = center_;
		m_Size = size_;
	}

	Box::Box(const Box& rsh) :
		IShape(BOX)
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
		return NEW_AO Box(*this);
	}

	Vector3F Box::Size() const
	{
		return m_Size;
	}

	void Box::Size(Vector3F val)
	{
		m_Size = val;
	}

	Vector3F Box::Center() const
	{
		return m_Center;
	}

	void Box::Center(Vector3F val)
	{
		m_Center = val;
	}
}