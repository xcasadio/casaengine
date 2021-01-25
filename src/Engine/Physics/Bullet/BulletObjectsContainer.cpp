#include "Base.h"

#ifdef USE_BULLET_PHYSICS

#include "Log\LogManager.h"
#include "BulletObjectsContainer.h"
#include "CA_Assert.h"
#include "Log\LogManager.h"
#include "LinearMath\btVector3.h"
#include "LinearMath\btQuaternion.h"

namespace CasaEngine
{
	BulletRigidBodyContainer::BulletRigidBodyContainer(btRigidBody* pRB_)
	{
		CA_ASSERT(pRB_ != nullptr, "BulletRigidBodyContainer : btRigidBody is null");
		m_pRigidBody = pRB_;
	}

	BulletRigidBodyContainer::~BulletRigidBodyContainer()
	{
		//TODO : remove object from world here ?
	}

	btRigidBody* BulletRigidBodyContainer::GetRigidBody() const
	{
		return m_pRigidBody;
	}

#if defined(CA_DEBUG)

	/**
	 *
	 */
	void BulletRigidBodyContainer::logInfo()
	{
		if (m_pRigidBody != nullptr)
		{
			btVector3 vec = m_pRigidBody->getWorldTransform().getOrigin();
			btVector3 linVel = m_pRigidBody->getLinearVelocity();
			btQuaternion q = m_pRigidBody->getWorldTransform().getRotation();
			CA_INFO("pos %f %f %f  rot %f %f %f %f linearVelocity %f %f %f\n",
				vec.x(), vec.y(), vec.z(), q.x(), q.y(), q.z(), q.w(),
				linVel.x(), linVel.y(), linVel.z());
		}
	}

#endif // #if defined(CA_DEBUG)

	/**
	 *
	 */
	const Vector3F& BulletRigidBodyContainer::getLinearVelocity() const
	{
		CA_ASSERT(m_pRigidBody != nullptr, "BulletRigidBodyContainer::getLinearVelocity() : RigidBody is null");
		btVector3 vec = m_pRigidBody->getLinearVelocity();
		return Vector3F(vec.x(), vec.y(), vec.z());
	}

	/**
	 *
	 */
	Vector3F& BulletRigidBodyContainer::getAngularVelocity() const
	{
		CA_ASSERT(m_pRigidBody != nullptr, "BulletRigidBodyContainer::getAngularVelocity() : RigidBody is null");
		btVector3 vec = m_pRigidBody->getAngularVelocity();
		return Vector3F(vec.x(), vec.y(), vec.z());
	}

	/**
	 *
	 */
	void BulletRigidBodyContainer::setLinearVelocity(const Vector3F& lin_vel)
	{
		CA_ASSERT(m_pRigidBody != nullptr, "BulletRigidBodyContainer::setLinearVelocity() : RigidBody is null");
		m_pRigidBody->setLinearVelocity(btVector3(lin_vel.x, lin_vel.y, lin_vel.z));

		//m_pRigidBody->applyCentralImpulse(btVector3(10.0f, 10.0f, 10.0f));
	}

	/**
	 *
	 */
	void BulletRigidBodyContainer::setAngularVelocity(const Vector3F& ang_vel)
	{
		CA_ASSERT(m_pRigidBody != nullptr, "BulletRigidBodyContainer::setAngularVelocity() : RigidBody is null");
		m_pRigidBody->setAngularVelocity(btVector3(ang_vel.x, ang_vel.y, ang_vel.z));
	}

	/**
	 *
	 */
	Vector3F& BulletRigidBodyContainer::getTranslation() const
	{
		CA_ASSERT(m_pRigidBody != nullptr, "BulletRigidBodyContainer::getTranslation() : RigidBody is null");
		btVector3 vec = m_pRigidBody->getWorldTransform().getOrigin();
		return Vector3F(vec.x(), vec.y(), vec.z());
	}

	/**
	 *
	 */
	void BulletRigidBodyContainer::setTranslation(const Vector3F& vec_)
	{
		CA_ASSERT(m_pRigidBody != nullptr, "BulletRigidBodyContainer::setTranslation() : RigidBody is null");
		m_pRigidBody->getWorldTransform().getOrigin() = btVector3(vec_.x, vec_.y, vec_.z);
	}

	/**
	 *
	 */
	Quaternion& BulletRigidBodyContainer::getRotation() const
	{
		CA_ASSERT(m_pRigidBody != nullptr, "BulletRigidBodyContainer::getRotation() : RigidBody is null");
		btQuaternion q = m_pRigidBody->getWorldTransform().getRotation();
		return Quaternion(q.x(), q.y(), q.z(), q.w());
	}

	/**
	 *
	 */
	void BulletRigidBodyContainer::setRotation(const Quaternion& rot)
	{
		CA_ASSERT(m_pRigidBody != nullptr, "BulletRigidBodyContainer::setRotation() : RigidBody is null");
		m_pRigidBody->getWorldTransform().setRotation(btQuaternion(rot.getX(), rot.getY(), rot.getZ(), rot.getW()));
	}

	//////////////////////////////////////////////////////////////////////////

	/**
	 *
	 */
	BulletCollisionObjectContainer::BulletCollisionObjectContainer(btCollisionObject* pObj_)
	{
		CA_ASSERT(pObj_ != nullptr, "BulletCollisionObjectContainer : btCollisionObject is null");
		m_pCollisionObject = pObj_;
	}

	BulletCollisionObjectContainer::~BulletCollisionObjectContainer()
	{
		//TODO : remove object from world here ?
	}

	btCollisionObject* BulletCollisionObjectContainer::GetCollisionObject() const
	{
		return m_pCollisionObject;
	}
}

#endif // USE_BULLET_PHYSICS