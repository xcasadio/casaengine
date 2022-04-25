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
	private:
		//PhysicMaterial* m_pPhysicMaterial;
		bool m_IsTrigger;
		float m_Mass;

	protected:
		IShape* m_pShape;

	public:
		~ColliderComponent() override;

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;

		IShape* GetShape() const;

		float Mass() const;
		void Mass(float val);

		virtual void Write(std::ostream& os)const;
		virtual void Read(std::ifstream& is);

	protected:
		ColliderComponent(BaseEntity* pEntity_, int type_);
		void CreateAndSetRigidBody(float mass);

	private:
		ICollisionObjectContainer* m_pCollisionObjectContainer;
	};
}
