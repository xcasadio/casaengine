#include "Circle.h"

namespace CasaEngine
{
	Circle::Circle() :
		IShape(ShapeType::CIRCLE2D), m_Radius(1.0f)
	{
		m_Center = Vector3::Zero();
	}

	Circle::Circle(float radius) : Circle()
	{
		Radius(radius);
	}

	Circle::Circle(const Circle& rsh) :
		Circle()
	{
		*this = rsh;
	}

	Circle& Circle::operator=(const Circle& rsh)
	{
		m_Radius = rsh.m_Radius;
		m_Center = rsh.m_Center;

		return *this;
	}

	Circle::~Circle() = default;

	Vector3 Circle::Center() const
	{
		return m_Center;
	}

	void Circle::Center(const Vector3 val)
	{
		m_Center = val;
	}

	float Circle::Radius() const
	{
		return m_Radius;
	}

	void Circle::Radius(const float val)
	{
		m_Radius = val;
	}

	IShape* Circle::Copy()
	{
		return new Circle(*this);
	}

	bool Circle::operator==(const IShape& rsh) const
	{
		if (rsh.Type() != Type())
		{
			return false;
		}

		return *this == dynamic_cast<const Circle&>(rsh);
	}
}
