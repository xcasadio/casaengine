#include "BulletCollision\CollisionDispatch\btCollisionWorld.h"
#include "BulletCollision\CollisionShapes\btBox2dShape.h"
#include "BulletCollision\CollisionShapes\btConvex2dShape.h"
#include "BulletCollision\CollisionShapes\btConvexShape.h"
#include "BulletCollision\CollisionShapes\btCylinderShape.h"
#include "BulletDynamics\Dynamics\btDiscreteDynamicsWorld.h"
#include "BulletPhysicsWorld.h"
#include "CA_Assert.h"
#include "Maths\Shape\Circle.h"
#include "Maths\Shape\IShape.h"
#include "Exceptions.h"
#include "Maths/Rectangle.h"

#include "btBulletDynamicsCommon.h"
#include "Memory\MemoryAllocation.h"
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
		IPhysicsWorld()
	{
		m_pBulletWorld = new btDynamicsWorldExt(
			pDispatcher_, pOverlappingPairCache_, pConstraintSolver_, pConfig_);
	}

	/**
	 *
	 */
	BulletPhysicsWorld::~BulletPhysicsWorld()
	{
		delete m_pBulletWorld;
	}

	void BulletPhysicsWorld::SetGravity(const Vector3F& gravity_)
	{
		m_pBulletWorld->setGravity(btVector3(gravity_.x, gravity_.y, gravity_.z));
	}

	Vector3F BulletPhysicsWorld::GetGravity() const
	{
		const auto vec = m_pBulletWorld->getGravity();
		return Vector3F(vec.x(), vec.y(), vec.z());
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
	IRigidBodyContainer* BulletPhysicsWorld::AddRigidBody(const RigidBody* pRigidBody_, const Vector3F position)
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

		auto pShape = CreateCollisionShape(pRigidBody_->pCollisionShape, Vector3F::Zero());

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

		return NEW_AO BulletRigidBodyContainer(body);
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
	btCollisionShape* BulletPhysicsWorld::CreateCollisionShape(const IShape* pShape_, Vector3F& origin_)
	{
		switch (pShape_->Type())
		{
			/*case BOX:

				break;

			case SPHERE:

				break;

			case CAPSULE:

				break;*/

		case RECTANGLE:
		{
			const auto* pBox2D = dynamic_cast<const RectangleF*>(pShape_);
			const auto center = pBox2D->Center();
			origin_ = Vector3F(center.x, center.y);
			const auto size = pBox2D->Size() / 2;
			auto* const pBox = new btBox2dShape(btVector3(size.x, size.y, 0.0f));
			return pBox;
		}

		case CIRCLE2D:
		{
			const auto* const pCircle = dynamic_cast<const Circle*>(pShape_);
			origin_ = pCircle->Center();
			auto* const pCylinder = new btCylinderShapeZ(btVector3(btScalar(pCircle->Radius()), btScalar(pCircle->Radius()), btScalar(0.0f)));
			return pCylinder;
		}

		/*case POLYGON:

			break;*/

		default:
		{
			throw CUnsupported("BulletPhysicsWorld::AddRigidBody() : unknown type");
			break;
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
		Vector3F origin;
		auto* const pbtShape = CreateCollisionShape(pShape_, origin);
		auto* colShape = new btCollisionObject();
		colShape->getWorldTransform().setOrigin(btVector3(origin.x, origin.y, origin.z));
		colShape->setCollisionShape(pbtShape);

		return colShape;
	}

	/**
	 *
	 */
	btCollisionObject* BulletPhysicsWorld::CreateCollisionObjectFromShape(btCollisionShape* pshape_, Vector3F center_)
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
	ICollisionObjectContainer* BulletPhysicsWorld::AddCollisionShape(const IShape* pShape_, const Vector3F& origin_)
	{
		auto* colShape = new btCollisionObject();
		Vector3F shapeOrigin;
		auto* const b3pShape = CreateCollisionShape(pShape_, shapeOrigin);
		colShape->getWorldTransform().setOrigin(btVector3(origin_.x + shapeOrigin.x, origin_.y + shapeOrigin.y, origin_.z + shapeOrigin.z));
		colShape->setCollisionShape(b3pShape);
		colShape->setCollisionFlags(btCollisionObject::CF_DYNAMIC_OBJECT);
		AddCollisionObject(colShape);

		return NEW_AO BulletCollisionObjectContainer(colShape);
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