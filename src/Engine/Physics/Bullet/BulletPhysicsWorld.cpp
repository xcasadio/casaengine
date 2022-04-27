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
#include "Entities/BaseEntity.h"

namespace CasaEngine
{
	BulletPhysicsWorld::BulletPhysicsWorld(
		btDefaultCollisionConfiguration* pConfig_,
		btCollisionDispatcher* pDispatcher_,
		btBroadphaseInterface* pOverlappingPairCache_,
		btSequentialImpulseConstraintSolver* pConstraintSolver_) :
		IPhysicsWorld(),
		m_pBulletWorld(new btDynamicsWorldExt(pDispatcher_, pOverlappingPairCache_, pConstraintSolver_, pConfig_)),
		dispatcher_(pDispatcher_)
	{
	}

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
		return {vec.x(), vec.y(), vec.z()};
	}
	
	void BulletPhysicsWorld::Update(const GameTime& gameTime_)
	{
		m_pBulletWorld->stepSimulation(gameTime_.FrameTime());

		for (int i=0; i<dispatcher_->getNumManifolds(); i++)
		{
			const auto *manifold = dispatcher_->getInternalManifoldPointer()[i];
			auto *entity1 = static_cast<BaseEntity*>(manifold->getBody0()->getUserPointer());
			auto *entity2 = static_cast<BaseEntity*>(manifold->getBody1()->getUserPointer());

			entity1->HandleMessage(Telegram(0.0, entity1->ID(), entity2->ID(), 1, nullptr));
			//entity->GetComponentMgr()->GetComponent<>()
		}
	}

	void BulletPhysicsWorld::Draw()
	{
		m_pBulletWorld->debugDrawWorld();
	}

	IRigidBodyContainer* BulletPhysicsWorld::AddRigidBody(BaseEntity* entity, const RigidBody* pRigidBody_, Vector3 position)
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
		
		btCollisionShape* pShape = CreateCollisionShape(pRigidBody_->pCollisionShape);

		startTransform.setOrigin(btVector3(position.x, position.y, position.z));

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		isDynamic = (mass != 0.0f);

		if (isDynamic)
		{
			pShape->calculateLocalInertia(mass, localInertia);
		}

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		myMotionState = new btDefaultMotionState(startTransform);
		rbInfo = btRigidBody::btRigidBodyConstructionInfo(mass, myMotionState, pShape); //, localInertia);
		body = new btRigidBody(rbInfo);
		//body->setContactProcessingThreshold(colShape->getContactBreakingThreshold());
		//body->setActivationState(ISLAND_SLEEPING);
		//body->setLinearFactor(btVector3(1,1,0));
		body->setSleepingThresholds(0.0, 0.0);
		body->setAngularFactor(0.0);
		body->setUserPointer(entity);

		m_pBulletWorld->addRigidBody(body);
		//body->setActivationState(ISLAND_SLEEPING);

		return new BulletRigidBodyContainer(body);
	}

	void BulletPhysicsWorld::AddCollisionObject(btCollisionObject* pColObj_)
	{
		m_pBulletWorld->addCollisionObject(pColObj_);
	}

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
			const auto* pBox2D = dynamic_cast<const Rectangle*>(pShape_);
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

	void BulletPhysicsWorld::RemoveCollisionObject(btCollisionObject* pColObj_)
	{
		m_pBulletWorld->removeCollisionObject(pColObj_);
	}

	btCollisionObject* BulletPhysicsWorld::CreateCollisionObjectFromShape(IShape* shape)
	{
		Vector3 origin;
		auto* const pbtShape = CreateCollisionShape(shape);
		auto* colShape = new btCollisionObject();
		colShape->getWorldTransform().setOrigin(btVector3(origin.x, origin.y, origin.z));
		colShape->setCollisionShape(pbtShape);

		return colShape;
	}

	btCollisionObject* BulletPhysicsWorld::CreateCollisionObjectFromShape(btCollisionShape* shape, Vector3 center)
	{
		auto* colShape = new btCollisionObject();
		colShape->getWorldTransform().setOrigin(btVector3(center.x, center.y, center.z));
		colShape->setCollisionShape(shape);
		return colShape;
	}

	void BulletPhysicsWorld::setDebugDraw(btIDebugDraw* pIDebugDraw_)
	{
		if (m_pBulletWorld != nullptr)
		{
			m_pBulletWorld->setDebugDrawer(pIDebugDraw_);
		}
	}

	ICollisionObjectContainer* BulletPhysicsWorld::CreateCollisionShape(const IShape* pShape_, const Vector3& origin_)
	{
		auto* colShape = new btCollisionObject();
		auto* const b3pShape = CreateCollisionShape(pShape_);
		colShape->getWorldTransform().setOrigin(btVector3(origin_.x, origin_.y, origin_.z));
		colShape->setCollisionShape(b3pShape);
		colShape->setCollisionFlags(btCollisionObject::CF_DYNAMIC_OBJECT);

		return new BulletCollisionObjectContainer(colShape);
	}

	void BulletPhysicsWorld::AddCollisionObject(ICollisionObjectContainer* pObj_)
	{
		auto* const pColl = dynamic_cast<BulletCollisionObjectContainer*>(pObj_);
		AddCollisionObject(pColl->GetCollisionObject());
	}

	void BulletPhysicsWorld::RemoveCollisionObject(ICollisionObjectContainer* pObj_)
	{
		auto* const pColl = dynamic_cast<BulletCollisionObjectContainer*>(pObj_);
		m_pBulletWorld->removeCollisionObject(pColl->GetCollisionObject());
	}

	void BulletPhysicsWorld::RemoveRigidBody(IRigidBodyContainer* pObj_)
	{
		auto* const pRB = dynamic_cast<BulletRigidBodyContainer*>(pObj_);
		m_pBulletWorld->removeRigidBody(pRB->GetRigidBody());
	}
}
