#include "Base.h"
#include "CA_Assert.h"

#include "Circle.h"

namespace CasaEngine
{
	Circle::Circle(float radius_, Vector3F center_) :
		IShape(CIRCLE2D)
	{
		m_Radius = radius_;
		m_Center = center_;
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
}