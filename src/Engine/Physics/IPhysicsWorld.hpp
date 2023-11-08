#pragma once

#include "CA_Export.hpp"

#include  "Maths/Vector3.hpp"
#include  "Maths/Shape/IShape.hpp"
#include  "GameTime.hpp"
#include  "RigidBodyParameters.hpp"
#include  "PhysicsObjectContainer.hpp"
#include  "Entities/BaseEntity.hpp"

namespace CasaEngine
{
	class CA_EXPORT IPhysicsWorld
	{
	public:
		IPhysicsWorld();
		virtual ~IPhysicsWorld();

		virtual void Update(const GameTime& gameTime_) = 0;
		virtual void Draw() = 0;

		virtual void SetGravity(const Vector3& gravity_) = 0;
		virtual Vector3 GetGravity() const = 0;

		virtual ICollisionObjectContainer* CreateCollisionShape(BaseEntity* entity, IShape* shape_, const Vector3& origin_, CollisionHitType hitType = CollisionHitType::Unknown, CollisionFlags flags = CollisionFlags::Dynamic) = 0;
		virtual ICollisionObjectContainer* CreateSensor(BaseEntity* entity, IShape* shape, const Vector3& origin, CollisionHitType hitType) = 0;

		virtual void AddCollisionObject(ICollisionObjectContainer*) = 0;
		virtual void RemoveCollisionObject(ICollisionObjectContainer*) = 0;

		virtual IRigidBodyContainer* AddRigidBody(BaseEntity* entity, const RigidBodyParameters* pRigidBody_, const Vector3& position) = 0;
		virtual void RemoveRigidBody(IRigidBodyContainer*) = 0;

		virtual void ContactTest(ICollisionObjectContainer* collision_object_container) = 0;
	};
}
