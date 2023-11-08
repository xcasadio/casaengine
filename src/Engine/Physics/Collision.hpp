#pragma once

#include "CA_Export.hpp"
#include  "Maths/Shape/IShape.hpp"

namespace CasaEngine
{
	enum class CollisionFlags
	{
		Static = 0,
		Dynamic,
		NoResponse
	};

	enum class CollisionHitType
	{
		Unknown = 0,
		Attack = 1,
		Defense
	};

	class CA_EXPORT Collision
	{
	public:
		Collision();
		Collision(const Collision& rsh);
		Collision& operator=(const Collision& rsh);
		~Collision() = default;
		Collision(Collision&& rsh) = default;
		Collision& operator=(Collision&& rsh) = default;

		CollisionHitType GetType() const;
		void SetType(CollisionHitType type);
		IShape* GetShape() const;
		void SetShape(IShape* shape);

		Collision* Copy() const;

		bool operator ==(const Collision& rsh) const;

	private:
		CollisionHitType _type;
		IShape* _shape;
	};
}
