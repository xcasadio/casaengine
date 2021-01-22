#include "Base.h"

#include "Sprite/Collision.h"

namespace CasaEngine
{
	Collision::Collision()
	{
	}

	Collision::~Collision()
	{
	}

	CollisionType Collision::GetType() const
	{
		return m_Type;
	}

	void Collision::SetType(CollisionType val)
	{
		m_Type = val;
	}

	IShape* Collision::GetShape() const
	{
		return m_pShape;
	}

	void Collision::SetShape(IShape *val)
	{
		m_pShape = val;
	}
}
