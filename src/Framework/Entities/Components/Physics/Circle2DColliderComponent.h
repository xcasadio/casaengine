#ifndef CIRCLE2DCOLLIDERCOMPONENT_H_
#define CIRCLE2DCOLLIDERCOMPONENT_H_

#include <iosfwd>

#include "CA_Export.h"
#include "ColliderComponent.h"
#include "Maths/Shape/Circle.h"

namespace CasaEngine
{
	class CA_EXPORT Circle2DColliderComponent :
		public ColliderComponent
	{
	private:


	public:
		Circle2DColliderComponent(BaseEntity* pEntity_);
		virtual ~Circle2DColliderComponent();
		
		void Initialize() override;

		void SetPosition(const Vector3F& position);
		void SetRadius(float radius);

	private:
		Circle m_Circle;
	};

}

#endif // CIRCLE2DCOLLIDERCOMPONENT_H_


