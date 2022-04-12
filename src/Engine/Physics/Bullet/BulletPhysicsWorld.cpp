#include "BulletCollision\CollisionDispatch\btCollisionWorld.h"
#include "BulletCollision\CollisionShapes\btBox2dShape.h"
#include "BulletCollision\CollisionShapes\btCylinderShape.h"
#include "BulletDynamics\Dynamics\btDiscreteDynamicsWorld.h"
#include "BulletPhysicsWorld.h"
#include "Maths\Shape\Circle.h"
#include "Maths\Shape\IShape.h"
#include "Exceptions.h"
#include "Maths/Rectangle.h"

#include "btBulletDynamicsCommon.h"
#include "BulletObjectsContainer.h"

namespace CasaEngine
{
	/**
	 *
	 */
	BulletPhysicsWorld::BulletPhysicsWorld(
		btDefaultCollisionConfiguration* pConfig_,
		btCollisionDispatcher* pDispatcher_,
		btBroadphaseInterface* pOverlappingPairCache_,
		btSequentialImpulseConstraintSolver* pConstraintSolver_) :
		IPhysicsWorld(),
		m_pBulletWorld(new btDynamicsWorldExt(pDispatcher_, pOverlappingPairCache_, pConstraintSolver_, pConfig_))
	{
	}

	/**
	 *
	 */
	BulletPhysicsWorld::~BulletPhysicsWorld()
	{
		delete m_pBulletWorld;
	}

	void BulletPhysicsWorld::SetGravity(const Vector3& gravity_)
	{
		m_pBulletWorld->setGravity(btVector3(gravity_.x, gravity_.y, gravity_.z));
	}

	Vector3 BulletPhysicsWorld::GetGravity() const
	{
		const auto vec = m_pBulletWorld->getGravity();
		return Vector3(vec.x(), vec.y(), vec.z());
	}

	/**
	 *
	 */
	void BulletPhysicsWorld::Update(const GameTime& gameTime_)
	{
		m_pBulletWorld->stepSimulation(gameTime_.FrameTime());

		//TODO: use a flag to des/activate debug drawing
		// optional but useful: debug drawing
		m_pBulletWorld->debugDrawWorld();
	}

	/**
	 *
	 */
	IRigidBodyContainer* BulletPhysicsWorld::AddRigidBody(const RigidBody* pRigidBody_, Vector3 position)
	{
		auto mass = pRigidBody_->mass;
		btTransform startTransform;
		startTransform.setIdentity();
		bool isDynamic;
		btVector3 localInertia(0, 0, 0);
		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = nullptr;
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, 0, 0);
		btRigidBody* body = nullptr;
		;
		btCollisionShape* pShape = CreateCollisionShape(pRigidBody_->pCollisionShape);

		startTransform.setOrigin(btVector3(position.x, position.y, position.z));

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		isDynamic = (mass != 0.0f);

		if (isDynamic)
			pShape->calculateLocalInertia(mass, localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		myMotionState = new btDefaultMotionState(startTransform);
		rbInfo = btRigidBody::btRigidBodyConstructionInfo(mass, myMotionState, pShape); //, localInertia);
		body = new btRigidBody(rbInfo);
		//body->setContactProcessingThreshold(colShape->getContactBreakingThreshold());
		//body->setActivationState(ISLAND_SLEEPING);
		//body->setLinearFactor(btVector3(1,1,0));
		body->setSleepingThresholds(0.0, 0.0);
		body->setAngularFactor(0.0);

		m_pBulletWorld->addRigidBody(body);
		//body->setActivationState(ISLAND_SLEEPING);

		return new BulletRigidBodyContainer(body);
	}

	/**
	 *
	 */
	void BulletPhysicsWorld::AddCollisionObject(btCollisionObject* pColObj_)
	{
		m_pBulletWorld->addCollisionObject(pColObj_);
	}

	/**
	 *
	 */
	btCollisionShape* BulletPhysicsWorld::CreateCollisionShape(const IShape* pShape_)
	{
		switch (pShape_->Type())
		{
			/*case BOX:

				break;

			case SPHERE:

				break;

			case CAPSULE:

				break;*/

		case ShapeType::RECTANGLE:
		{
			const auto* pBox2D = dynamic_cast<const RectangleF*>(pShape_);
			const auto size = pBox2D->Size() / 2.0f;
			auto* const pBox = new btBoxShape(btVector3(size.x, size.y, 10.0f));
			//auto* const pBox = new btBox2dShape(btVector3(size.x, size.y, 0.0f));
			return pBox;
		}

		case ShapeType::CIRCLE2D:
		{
			const auto* const pCircle = dynamic_cast<const Circle*>(pShape_);
			auto* const pCylinder = new btCylinderShapeZ(btVector3(pCircle->Radius(), pCircle->Radius(), 10.0f));
			return pCylinder;
		}

		/*case POLYGON:

			break;*/

		default:
		{
			throw CUnsupported("BulletPhysicsWorld::AddRigidBody() : unknown type");
		}
		}
	}

	/**
	 *
	 */
	void BulletPhysicsWorld::RemoveCollisionObject(btCollisionObject* pColObj_)
	{
		m_pBulletWorld->removeCollisionObject(pColObj_);
	}

	/**
	 *
	 */
	btCollisionObject* BulletPhysicsWorld::CreateCollisionObjectFromShape(IShape* pShape_)
	{
		Vector3 origin;
		auto* const pbtShape = CreateCollisionShape(pShape_);
		auto* colShape = new btCollisionObject();
		colShape->getWorldTransform().setOrigin(btVector3(origin.x, origin.y, origin.z));
		colShape->setCollisionShape(pbtShape);

		return colShape;
	}

	/**
	 *
	 */
	btCollisionObject* BulletPhysicsWorld::CreateCollisionObjectFromShape(btCollisionShape* pshape_, Vector3 center_)
	{
		auto* colShape = new btCollisionObject();
		colShape->getWorldTransform().setOrigin(btVector3(center_.x, center_.y, center_.z));
		colShape->setCollisionShape(pshape_);
		return colShape;
	}

	/**
	 *
	 */
	void BulletPhysicsWorld::setDebugDraw(btIDebugDraw* pIDebugDraw_)
	{
		if (m_pBulletWorld != nullptr)
		{
			m_pBulletWorld->setDebugDrawer(pIDebugDraw_);
		}
	}

	/**
	 *
	 */
	ICollisionObjectContainer* BulletPhysicsWorld::CreateCollisionShape(const IShape* pShape_, const Vector3& origin_)
	{
		auto* colShape = new btCollisionObject();
		auto* const b3pShape = CreateCollisionShape(pShape_);
		colShape->getWorldTransform().setOrigin(btVector3(origin_.x, origin_.y, origin_.z));
		colShape->setCollisionShape(b3pShape);
		colShape->setCollisionFlags(btCollisionObject::CF_DYNAMIC_OBJECT);

		return new BulletCollisionObjectContainer(colShape);
	}

	/**
	 *
	 */
	void BulletPhysicsWorld::AddCollisionObject(ICollisionObjectContainer* pObj_)
	{
		auto* const pColl = dynamic_cast<BulletCollisionObjectContainer*>(pObj_);
		AddCollisionObject(pColl->GetCollisionObject());
	}

	/**
	 *
	 */
	void BulletPhysicsWorld::RemoveCollisionObject(ICollisionObjectContainer* pObj_)
	{
		auto* const pColl = dynamic_cast<BulletCollisionObjectContainer*>(pObj_);
		m_pBulletWorld->removeCollisionObject(pColl->GetCollisionObject());
	}

	/**
	 *
	 */
	void BulletPhysicsWorld::RemoveRigidBody(IRigidBodyContainer* pObj_)
	{
		auto* const pRB = dynamic_cast<BulletRigidBodyContainer*>(pObj_);
		m_pBulletWorld->removeRigidBody(pRB->GetRigidBody());
	}
}