#pragma once

#include "Physics\PhysicsObjectContainer.h"
#include "BulletDynamics\Dynamics\btRigidBody.h"
#include "BulletCollision\CollisionDispatch\btCollisionObject.h"
#include "CA_Export.h"

#include "Maths\Vector3.h"
#include "Maths\Quaternion.h"

namespace CasaEngine
{
	//TODO : when the container is deleted : remove from the physics world ?

	class CA_EXPORT BulletRigidBodyContainer :
		public IRigidBodyContainer
	{
	public:
		BulletRigidBodyContainer(btRigidBody* pRB_);
		~BulletRigidBodyContainer() override;

		btRigidBody* GetRigidBody() const;

		Vector3 GetLinearVelocity() const override;
		void setLinearVelocity(const Vector3& lin_vel) override;

		Vector3 getAngularVelocity() const override;
		void setAngularVelocity(const Vector3& ang_vel) override;

		Vector3 getTranslation() const override;
		void setTranslation(const Vector3& vec_) override;

		Quaternion getRotation() const override;
		void setRotation(const Quaternion& rot) override;

#if defined(CA_DEBUG)
		void logInfo() override;
#endif

	private:
		btRigidBody* m_pRigidBody;
	};

	//////////////////////////////////////////////////////////////////////////

	class CA_EXPORT BulletCollisionObjectContainer :
		public ICollisionObjectContainer
	{
	public:
		BulletCollisionObjectContainer(btCollisionObject* pObj_);
		~BulletCollisionObjectContainer() override;

		btCollisionObject* GetCollisionObject() const;

	private:
		btCollisionObject* m_pCollisionObject;
	};
}
