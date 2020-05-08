#ifndef BULLETOBJECTSCONTAINER_H_
#define BULLETOBJECTSCONTAINER_H_

#include "Physics\PhysicsObjectContainer.h"
#include "BulletDynamics\Dynamics\btRigidBody.h"
#include "BulletCollision\CollisionDispatch\btCollisionObject.h"
#include "CA_Export.h"

#include "Maths\Vector3.h"
#include "Maths\Quaternion.h"

namespace CasaEngine
{
	//TODO : when the container is deleted : remove from the physics world ?

	/**
	 * 
	 */
	class CA_EXPORT BulletRigidBodyContainer :
		public IRigidBodyContainer
	{
	public:
		BulletRigidBodyContainer(btRigidBody *pRB_);
		~BulletRigidBodyContainer();

		btRigidBody *GetRigidBody() const;

#if defined(CA_DEBUG)

		void logInfo() override;

#endif // #if defined(CA_DEBUG)

		const Vector3F& getLinearVelocity() const override;
		void setLinearVelocity(const Vector3F& lin_vel) override;

		Vector3F& getAngularVelocity() const override;
		void setAngularVelocity(const Vector3F& ang_vel) override;

		Vector3F& getTranslation() const override;
		void setTranslation(const Vector3F& ang_vel) override;

		Quaternion& getRotation() const override;
		void setRotation(const Quaternion& rot) override;

	private:
		btRigidBody *m_pRigidBody;
	};

	//////////////////////////////////////////////////////////////////////////

	/**
	 * 
	 */
	class CA_EXPORT BulletCollisionObjectContainer :
		public ICollisionObjectContainer
	{
	public:
		BulletCollisionObjectContainer(btCollisionObject *pObj_);
		~BulletCollisionObjectContainer();

		btCollisionObject * GetCollisionObject() const;

	private:
		btCollisionObject *m_pCollisionObject;
	};

}

#endif // BULLETOBJECTSCONTAINER_H_