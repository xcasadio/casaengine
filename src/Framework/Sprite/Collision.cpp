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

	Collision::~Collision()
	{
	}

	Collision* Collision::Copy() const
	{
		return NEW_AO Collision(*this);
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
