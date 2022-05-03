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
		_bulletWorld(new btDynamicsWorldExt(pDispatcher_, pOverlappingPairCache_, pConstraintSolver_, pConfig_)),
		_dispatcher(pDispatcher_)
	{
	}

	BulletPhysicsWorld::~BulletPhysicsWorld()
	{
		delete _bulletWorld;
	}

	void BulletPhysicsWorld::SetGravity(const Vector3& gravity_)
	{
		_bulletWorld->setGravity(btVector3(gravity_.x, gravity_.y, gravity_.z));
	}

	Vector3 BulletPhysicsWorld::GetGravity() const
	{
		const auto vec = _bulletWorld->getGravity();
		return {vec.x(), vec.y(), vec.z()};
	}
	
	void BulletPhysicsWorld::Update(const GameTime& gameTime_)
	{
		_bulletWorld->stepSimulation(gameTime_.FrameTime());

		//_bulletWorld->contactPairTest()
		//_bulletWorld->contactTest()

		for (int i=0; i<_dispatcher->getNumManifolds(); i++)
		{
			const auto *manifold = _dispatcher->getInternalManifoldPointer()[i];
			auto *entity1 = static_cast<BaseEntity*>(manifold->getBody0()->getUserPointer());
			auto *entity2 = static_cast<BaseEntity*>(manifold->getBody1()->getUserPointer());

			entity1->HandleMessage(Telegram(0.0, entity1->Id(), entity2->Id(), 1, nullptr));
			//entity->GetComponentMgr()->GetComponent<>()
		}
	}

	void BulletPhysicsWorld::Draw()
	{
		_bulletWorld->debugDrawWorld();
	}

	IRigidBodyContainer* BulletPhysicsWorld::AddRigidBody(BaseEntity* entity, const RigidBodyParameters* pRigidBody_, const Vector3& position)
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
		
		btCollisionShape* pShape = CreateCollisionShape(pRigidBody_->collisionShape);

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
		body->setSleepingThresholds(0.0, 0.0);
		//TODO : config to apply constraint in axis (0 = non move)
		switch (pRigidBody_->axisConstraint)
		{
			case AxisConstraints::XY: body->setLinearFactor(btVector3(1, 1, 0)); break;
			case AxisConstraints::XZ: body->setLinearFactor(btVector3(1, 0, 1)); break;
			case AxisConstraints::YZ: body->setLinearFactor(btVector3(0, 1, 1)); break;
			case AxisConstraints::NONE:
			default: body->setLinearFactor(btVector3(1, 1, 1));
		}

		body->setAngularFactor(0.0); // no rotation

		body->setUserPointer(entity);
		_bulletWorld->addRigidBody(body);
		//body->setActivationState(ISLAND_SLEEPING);

		return new BulletRigidBodyContainer(body);
	}

	void BulletPhysicsWorld::AddCollisionObject(btCollisionObject* pColObj_)
	{
		_bulletWorld->addCollisionObject(pColObj_);
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

	void BulletPhysicsWorld::RemoveCollisionObject(btCollisionObject* collisionObject)
	{
		_bulletWorld->removeCollisionObject(collisionObject);
	}

	btCollisionObject* BulletPhysicsWorld::CreateCollisionObjectFromShape(IShape* shape)
	{
		auto* const pbtShape = CreateCollisionShape(shape);
		auto* colShape = new btCollisionObject();
		colShape->getWorldTransform().setOrigin(btVector3(0, 0, 0));
		colShape->setCollisionShape(pbtShape);

		return colShape;
	}

	btCollisionObject* BulletPhysicsWorld::CreateCollisionObjectFromShape(btCollisionShape* shape, Vector3 center)
	{
		auto* collision_object = new btCollisionObject();
		collision_object->getWorldTransform().setOrigin(btVector3(center.x, center.y, center.z));
		collision_object->setCollisionShape(shape);
		return collision_object;
	}

	void BulletPhysicsWorld::setDebugDraw(btIDebugDraw* IDebugDraw)
	{
		if (_bulletWorld != nullptr)
		{
			_bulletWorld->setDebugDrawer(IDebugDraw);
		}
	}

	ICollisionObjectContainer* BulletPhysicsWorld::CreateCollisionShape(const IShape* shape_, const Vector3& origin_)
	{
		auto* colShape = new btCollisionObject();
		auto* const b3pShape = CreateCollisionShape(shape_);
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
		_bulletWorld->removeCollisionObject(pColl->GetCollisionObject());
	}

	void BulletPhysicsWorld::RemoveRigidBody(IRigidBodyContainer* pObj_)
	{
		auto* const pRB = dynamic_cast<BulletRigidBodyContainer*>(pObj_);
		_bulletWorld->removeRigidBody(pRB->GetRigidBody());
	}
}
