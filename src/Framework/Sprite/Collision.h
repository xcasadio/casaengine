#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "CA_Export.h"
#include "Maths/Rectangle.h"

#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>

namespace CasaEngine
{
	enum CollisionType 
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
		~Collision();

		CollisionType GetType() const;
		void SetType(CollisionType type);
		IShape* GetShape() const;
		void SetShape(IShape *shape);

		Collision* Copy() const;

	private:
		CollisionType m_Type;
		IShape *m_pShape;

	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::make_nvp("collision_type", m_Type));
			m_pShape = new RectangleI(); //TODO : how works polymorphism with cereal ??
			ar(cereal::make_nvp("shape", *dynamic_cast<RectangleI*>(m_pShape)));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::make_nvp("collision_type", m_Type));
			ar(cereal::make_nvp("shape", *dynamic_cast<RectangleI *>(m_pShape)));
		}
	};
}

#endif
