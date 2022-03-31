#include "Circle.h"

namespace CasaEngine
{
	Circle::Circle() :
		IShape(CIRCLE2D)
	{
		m_Radius = 1.0f;
		m_Center = Vector3F::Zero();
	}

	Circle::Circle(const Circle& rsh) :
		IShape(CIRCLE2D)
	{
		*this = rsh;
	}

	Circle& Circle::operator=(const Circle& rsh)
	{
		m_Radius = rsh.m_Radius;
		m_Center = rsh.m_Center;

		return *this;
	}

	Circle::~Circle()
	{
	}

	Vector3F Circle::Center() const
	{
		return m_Center;
	}

	void Circle::Center(Vector3F val)
	{
		m_Center = val;
	}

	float Circle::Radius() const
	{
		return m_Radius;
	}

	void Circle::Radius(float val)
	{
		m_Radius = val;
	}

	IShape* Circle::Copy()
	{
		return new Circle(*this);
	}
}
