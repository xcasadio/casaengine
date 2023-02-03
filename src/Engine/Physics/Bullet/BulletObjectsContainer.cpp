#include "Log/LogManager.h"
#include "BulletObjectsContainer.h"
#include "CA_Assert.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btQuaternion.h"

namespace CasaEngine
{
	BulletRigidBodyContainer::BulletRigidBodyContainer(btRigidBody* pRB_)
	{
		CA_ASSERT(pRB_ != nullptr, "BulletRigidBodyContainer : btRigidBody is null")
			m_pRigidBody = pRB_;
	}

	BulletRigidBodyContainer::~BulletRigidBodyContainer() = default;

	btRigidBody* BulletRigidBodyContainer::GetRigidBody() const
	{
		return m_pRigidBody;
	}

	Vector3 BulletRigidBodyContainer::GetLinearVelocity() const
	{
		CA_ASSERT(m_pRigidBody != nullptr, "BulletRigidBodyContainer::GetLinearVelocity() : RigidBody is null")
			const btVector3& vec = m_pRigidBody->getLinearVelocity();
		return { vec.x(), vec.y(), vec.z() };
	}

	Vector3 BulletRigidBodyContainer::getAngularVelocity() const
	{
		CA_ASSERT(m_pRigidBody != nullptr, "BulletRigidBodyContainer::getAngularVelocity() : RigidBody is null")
			const btVector3& vec = m_pRigidBody->getAngularVelocity();
		return { vec.x(), vec.y(), vec.z() };
	}

	void BulletRigidBodyContainer::setLinearVelocity(const Vector3& lin_vel)
	{
		CA_ASSERT(m_pRigidBody != nullptr, "BulletRigidBodyContainer::setLinearVelocity() : RigidBody is null")
			m_pRigidBody->setLinearVelocity(btVector3(lin_vel.x, lin_vel.y, lin_vel.z));
		//m_pRigidBody->applyCentralImpulse(btVector3(lin_vel.x, lin_vel.y, lin_vel.z));
	}

	void BulletRigidBodyContainer::setAngularVelocity(const Vector3& ang_vel)
	{
		CA_ASSERT(m_pRigidBody != nullptr, "BulletRigidBodyContainer::setAngularVelocity() : RigidBody is null")
			m_pRigidBody->setAngularVelocity(btVector3(ang_vel.x, ang_vel.y, ang_vel.z));
	}

	Vector3 BulletRigidBodyContainer::getTranslation() const
	{
		CA_ASSERT(m_pRigidBody != nullptr, "BulletRigidBodyContainer::getTranslation() : RigidBody is null")
			const btVector3& vec = m_pRigidBody->getWorldTransform().getOrigin();
		return { vec.x(), vec.y(), vec.z() };
	}

	void BulletRigidBodyContainer::setTranslation(const Vector3& vec_)
	{
		CA_ASSERT(m_pRigidBody != nullptr, "BulletRigidBodyContainer::setTranslation() : RigidBody is null")
			m_pRigidBody->getWorldTransform().getOrigin() = btVector3(vec_.x, vec_.y, vec_.z);
	}

	Quaternion BulletRigidBodyContainer::getRotation() const
	{
		CA_ASSERT(m_pRigidBody != nullptr, "BulletRigidBodyContainer::getRotation() : RigidBody is null")
			const btQuaternion q = m_pRigidBody->getWorldTransform().getRotation();
		return { q.x(), q.y(), q.z(), q.w() };
	}

	void BulletRigidBodyContainer::setRotation(const Quaternion& rot)
	{
		CA_ASSERT(m_pRigidBody != nullptr, "BulletRigidBodyContainer::setRotation() : RigidBody is null")
			m_pRigidBody->getWorldTransform().setRotation(btQuaternion(rot.GetX(), rot.GetY(), rot.GetZ(), rot.GetW()));
	}

#if defined(CA_DEBUG)

	void BulletRigidBodyContainer::logInfo()
	{
		if (m_pRigidBody != nullptr)
		{
			const btVector3 vec = m_pRigidBody->getWorldTransform().getOrigin();
			const btVector3 linVel = m_pRigidBody->getLinearVelocity();
			const btQuaternion q = m_pRigidBody->getWorldTransform().getRotation();
			CA_INFO("pos %f %f %f rot %f %f %f %f linearVelocity %f %f %f\n", vec.x(), vec.y(), vec.z(), q.x(), q.y(), q.z(), q.w(), linVel.x(), linVel.y(), linVel.z());
		}
	}

#endif

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