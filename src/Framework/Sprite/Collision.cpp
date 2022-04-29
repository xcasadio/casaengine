#include "Base.h"

#include "Sprite/Collision.h"

namespace CasaEngine
{
	Collision::Collision()
	{
	}

	Collision::Collision(const Collision& rsh)
	{
		*this = rsh;
	}

	Collision& Collision::operator=(const Collision& rsh)
	{
		m_Type = rsh.m_Type;
		m_pShape = rsh.m_pShape->Copy();

		return *this;
	}

	Collision* Collision::Copy() const
	{
		return new Collision(*this);
	}

	CollisionType Collision::GetType() const
	{
		return m_Type;
	}

	void Collision::SetType(CollisionType type)
	{
		m_Type = type;
	}

	IShape* Collision::GetShape() const
	{
		return m_pShape;
	}

	void Collision::SetShape(IShape *shape)
	{
		m_pShape = shape;
	}
}
