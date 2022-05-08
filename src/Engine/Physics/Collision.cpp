#include "Base.h"

#include "Physics/Collision.h"

namespace CasaEngine
{
	Collision::Collision() :
		_type(CollisionHitType::Unknown),
		_shape(nullptr)
	{
	}

	Collision::Collision(const Collision& rsh)
	{
		*this = rsh;
	}

	Collision& Collision::operator=(const Collision& rsh)
	{
		_type = rsh._type;
		_shape = rsh._shape->Copy();

		return *this;
	}

	Collision* Collision::Copy() const
	{
		return new Collision(*this);
	}

	CollisionHitType Collision::GetType() const
	{
		return _type;
	}

	void Collision::SetType(CollisionHitType type)
	{
		_type = type;
	}

	IShape* Collision::GetShape() const
	{
		return _shape;
	}

	void Collision::SetShape(IShape *shape)
	{
		_shape = shape;
	}
}
