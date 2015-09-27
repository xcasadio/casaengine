#ifndef BULLETOBJECTSCONTAINER_H_
#define BULLETOBJECTSCONTAINER_H_

#include "Physics\PhysicsObjectContainer.h"
#include "BulletDynamics\Dynamics\btRigidBody.h"
#include "BulletCollision\CollisionDispatch\btCollisionObject.h"
#include "CA_Export.h"
#include "CompilationMacro.h"
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

		void logInfo() OVERRIDE;

#endif // #if defined(CA_DEBUG)

		const Vector3F& getLinearVelocity() const OVERRIDE;
		void setLinearVelocity(const Vector3F& lin_vel) OVERRIDE;

		Vector3F& getAngularVelocity() const OVERRIDE;
		void setAngularVelocity(const Vector3F& ang_vel) OVERRIDE;

		Vector3F& getTranslation() const OVERRIDE;
		void setTranslation(const Vector3F& ang_vel) OVERRIDE;

		Quaternion& getRotation() const OVERRIDE;
		void setRotation(const Quaternion& rot) OVERRIDE;

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

} // namespace CasaEngine

#endif // BULLETOBJECTSCONTAINER_H_