#ifndef _COLLISION_H_
#define _COLLISION_H_

#include "CA_Export.h"
#include "Maths/Rectangle.h"

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
		~Collision();

		CollisionType GetType() const;
		void SetType(CollisionType type);
		IShape* GetShape() const;
		void SetShape(IShape *shape);

	private:
		CollisionType m_Type;
		IShape *m_pShape;
	};
}

#endif
