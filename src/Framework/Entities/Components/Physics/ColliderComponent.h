#pragma once

#include <iosfwd>

#include "CA_Export.h"

#include "GameTime.h"
#include "Entities/Component.h"
#include "Sprite/SpriteRenderer.h"
#include "Physics/PhysicsObjectContainer.h"

namespace CasaEngine
{

	class CA_EXPORT ColliderComponent :
		public Component
	{
	public:
		~ColliderComponent() override;

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;

		IShape* GetShape() const;

		float Mass() const;
		void Mass(float val);

		AxisConstraints AxisConstraint() const;
		void AxisConstraint(AxisConstraints val);

		virtual void Write(std::ostream& os)const;
		virtual void Read(std::ifstream& is);

	protected:
		IShape* m_pShape;

		ColliderComponent(BaseEntity* pEntity_, int type_);
		void CreateAndSetRigidBody(float mass);

	private:
		AxisConstraints axisConstraint;
		float m_Mass;
		ICollisionObjectContainer* m_pCollisionObjectContainer;
	};
}
