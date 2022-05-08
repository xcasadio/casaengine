#pragma once

#include <vector>

#include "CA_Export.h"
#include "GameTime.h"
#include "Entities/Component.h"
#include "ColliderComponent.h"
#include "Physics/RigidBodyParameters.h"

#include "Messaging/Telegram.h"

namespace CasaEngine
{
	class CA_EXPORT RigidBodyComponent :
		public Component
	{
	private:
		float m_Mass;
		bool m_UseGravity;
		bool m_IsKinematic;

		std::vector<ColliderComponent*> m_ListShapes;
		RigidBodyParameters m_RigidBody;

	public:
		RigidBodyComponent(BaseEntity* pEntity_);

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;

		bool HandleMessage(const Telegram& msg) override;

		RigidBodyParameters& GetRigidBody();
		void SetRigidBody(RigidBodyParameters& val);

		void AddShape(ColliderComponent* pShape_);
		void RemoveShape(ColliderComponent* pShape_);
	};
}
