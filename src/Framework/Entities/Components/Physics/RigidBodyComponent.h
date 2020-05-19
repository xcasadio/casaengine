#ifndef RIGIDBODYCOMPONENT_H_
#define RIGIDBODYCOMPONENT_H_

#include <string>
#include <iosfwd>
#include <vector>

#include "CA_Export.h"
#include "GameTime.h"
#include "Entities/Component.h"
#include "Sprite/SpriteRenderer.h"
#include "Graphics/Color.h"
#include "Sprite/SpriteTypes.h"
#include "ColliderComponent.h"
#include "Physics/RigidBody.h"
#include "Parsers/Xml/tinyxml2.h"

#include "AI/Messaging/Telegram.h"

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
		RigidBody m_RigidBody;

	public:
		RigidBodyComponent(BaseEntity* pEntity_);
		virtual ~RigidBodyComponent();

		//all entities must implement an Initialize function
		void Initialize();

		/**
		 *
		 */
		void Update(const GameTime& gameTime_) override;

		/**
		 *
		 */
		bool HandleMessage(const Telegram& msg) override;

		/**
		 *
		 */
		RigidBody& GetRigidBody();

		/**
		 *
		 */
		void SetRigidBody(RigidBody& val);

		void AddShape(ColliderComponent* pShape_);
		void RemoveShape(ColliderComponent* pShape_);
	};
}

#endif
