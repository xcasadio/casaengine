#include  "Base.hpp"
#include  "Physics/Collision.hpp"

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

	bool Collision::operator==(const Collision& rsh) const
	{
		if (_type != rsh._type)
		{
			return false;
		}

		if (_shape != nullptr && rsh._shape == nullptr
			|| _shape == nullptr && rsh._shape != nullptr)
		{
			return false;
		}

		return *_shape == *rsh._shape;
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

	void Collision::SetShape(IShape* shape)
	{
		_shape = shape;
	}
}
