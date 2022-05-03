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
		_type = rsh._type;
		_shape = rsh._shape->Copy();

		return *this;
	}

	Collision* Collision::Copy() const
	{
		return new Collision(*this);
	}

	CollisionType Collision::GetType() const
	{
		return _type;
	}

	void Collision::SetType(CollisionType type)
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
