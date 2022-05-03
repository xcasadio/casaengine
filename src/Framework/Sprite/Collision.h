#pragma once

#include "CA_Export.h"
#include "Maths/Rectangle.h"

#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>


namespace CasaEngine
{
	enum class CollisionType 
	{
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

		CollisionType GetType() const;
		void SetType(CollisionType type);
		IShape* GetShape() const;
		void SetShape(IShape *shape);

		Collision* Copy() const;

	private:
		CollisionType _type;
		IShape *_shape;

		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::make_nvp("collision_type", _type));
			_shape = new RectangleI(); //TODO : how works polymorphism with cereal ??
			ar(cereal::make_nvp("shape", *dynamic_cast<RectangleI*>(_shape)));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::make_nvp("collision_type", _type));
			ar(cereal::make_nvp("shape", *dynamic_cast<RectangleI *>(_shape)));
		}
	};
}
