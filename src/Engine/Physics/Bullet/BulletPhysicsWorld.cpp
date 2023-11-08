#include     "BulletCollision/CollisionDispatch/btCollisionWorld.h"
#include     "BulletCollision/CollisionDispatch/btGhostObject.h"
#include     "BulletCollision/CollisionShapes/btBox2dShape.h"
#include     "BulletCollision/CollisionShapes/btCylinderShape.h"
#include     "BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include  "BulletPhysicsWorld.hpp"
#include  "Maths/Shape/Circle.hpp"
#include  "Maths/Shape/IShape.hpp"
#include  "Exceptions.hpp"
#include  "Maths/Rectangle.hpp"

#include    "btBulletDynamicsCommon.h"
#include  "BulletObjectsContainer.hpp"
#include  "Entities/BaseEntity.hpp"
#include  "Game/Game.hpp"
#include  "GameDatas/MessageType.hpp"
#include  "Physics/CollisionParameters.hpp"
#include  "Physics/CollisionParametersBetween2Entities.hpp"

namespace CasaEngine
{
	BulletPhysicsWorld::BulletPhysicsWorld(
		btDefaultCollisionConfiguration* pConfig_,
		btCollisionDispatcher* pDispatcher_,
		btBroadphaseInterface* pOverlappingPairCache_,
		btSequentialImpulseConstraintSolver* pConstraintSolver_) :
		IPhysicsWorld(),
		_bulletWorld(new btDiscreteDynamicsWorld(pDispatcher_, pOverlappingPairCache_, pConstraintSolver_, pConfig_)),
		_dispatcher(pDispatcher_)
	{
		//_bulletWorld->getPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
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
		return { vec.x(), vec.y(), vec.z() };
	}

	void BulletPhysicsWorld::Update(const GameTime& gameTime_)
	{
		_bulletWorld->stepSimulation(gameTime_.FrameTime());

		//_bulletWorld->contactPairTest()
		//_bulletWorld->contactTest()

		for (int i = 0; i < _dispatcher->getNumManifolds(); i++)
		{
			const auto* manifold = _dispatcher->getManifoldByIndexInternal(i);
			auto* collisionParameters1 = static_cast<CollisionParameters*>(manifold->getBody0()->getUserPointer());
			auto* collisionParameters2 = static_cast<CollisionParameters*>(manifold->getBody1()->getUserPointer());

			collisionParameters1->GetEntity()->HandleMessage(
				Telegram(0.0,
					collisionParameters1->GetEntity()->Id(),
					collisionParameters2->GetEntity()->Id(),
					(int)MessageType::COLLISION,
					new CollisionParametersBetween2Entities(collisionParameters1, collisionParameters2)));
			/*
			collisionParameters2->_entity->HandleMessage(
				Telegram(0.0,
					collisionParameters2->_entity->Id(),
					collisionParameters1->_entity->Id(),
					(int)MessageType::COLLISION,
					collisionParameters2));
			*/
		}
	}

	void BulletPhysicsWorld::Draw()
	{
		_bulletWorld->debugDrawWorld();
	}

	int ConvertCollisionFlags(CollisionFlags flags)
	{
		switch (flags)
		{
		case CollisionFlags::Static:
			return btCollisionObject::CollisionFlags::CF_STATIC_OBJECT;
		case CollisionFlags::Dynamic:
			return btCollisionObject::CollisionFlags::CF_DYNAMIC_OBJECT;
		case CollisionFlags::NoResponse:
			return btCollisionObject::CollisionFlags::CF_NO_CONTACT_RESPONSE;
		default:
			throw std::logic_error("BulletPhysicsWorld::ConvertCollisionFlags() : Can't convert CollisionFlags.");
		}
	}

	IRigidBodyContainer* BulletPhysicsWorld::AddRigidBody(BaseEntity* entity, const RigidBodyParameters* pRigidBody_, const Vector3& position)
	{
		auto mass = pRigidBody_->mass;
		btTransform startTransform;
		startTransform.setIdentity();
		bool isDynamic;
		btVector3 localInertia(0, 0, 0);
		//using motion state is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = nullptr;
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, 0, 0);
		btRigidBody* body = nullptr;

		btCollisionShape* pShape = CreateCollisionShape(pRigidBody_->collisionShape);

		startTransform.setOrigin(btVector3(position.x, position.y, position.z));

		//rigid body is dynamic if and only if mass is non zero, otherwise static
		isDynamic = mass != 0.0f;

		if (isDynamic)
		{
			pShape->calculateLocalInertia(mass, localInertia);
		}

		//using motion state is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
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
		case AxisConstraints::NONE: body->setLinearFactor(btVector3(1, 1, 1)); break;
		}

		body->setAngularFactor(0.0); // no rotation

		auto* collision = new Collision();
		collision->SetShape(pRigidBody_->collisionShape);
		collision->SetType(CollisionHitType::Defense);
		auto* collisionParameters = new CollisionParameters(entity, collision);
		body->setUserPointer(collisionParameters);
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
			auto* const pBox = new btBoxShape(btVector3(size.x, size.y, 5.0f));
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
			throw Unsupported("BulletPhysicsWorld::AddRigidBody() : unknown type");
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

	ICollisionObjectContainer* BulletPhysicsWorld::CreateCollisionShape(BaseEntity* entity, IShape* shape, const Vector3& origin, CollisionHitType hitType, CollisionFlags flags)
	{
		auto* collisionShape = new btCollisionObject();
		auto* const b3pShape = CreateCollisionShape(shape);
		collisionShape->getWorldTransform().setOrigin(btVector3(origin.x, origin.y, origin.z));
		collisionShape->setCollisionShape(b3pShape);
		collisionShape->setCollisionFlags(collisionShape->getCollisionFlags() | ConvertCollisionFlags(flags));
		auto* collision = new Collision();
		collision->SetType(hitType);
		collision->SetShape(shape);
		auto* collisionParameters = new CollisionParameters(entity, collision);
		collisionShape->setUserPointer(collisionParameters);

		return new BulletCollisionObjectContainer(collisionShape);
	}

	ICollisionObjectContainer* BulletPhysicsWorld::CreateSensor(BaseEntity* entity, IShape* shape, const Vector3& origin, CollisionHitType hitType)
	{
		auto* ghost_object = new btGhostObject();
		ghost_object->setCollisionFlags(ghost_object->getCollisionFlags() | btCollisionObject::CollisionFlags::CF_NO_CONTACT_RESPONSE);
		auto* const b3pShape = CreateCollisionShape(shape);
		ghost_object->getWorldTransform().setOrigin(btVector3(origin.x, origin.y, origin.z));
		ghost_object->setCollisionShape(b3pShape);
		auto* collision = new Collision();
		collision->SetType(hitType);
		collision->SetShape(shape);
		auto* collisionParameters = new CollisionParameters(entity, collision);
		ghost_object->setUserPointer(collisionParameters);

		return new BulletCollisionObjectContainer(ghost_object);
	}


	struct ContactSensorCallback : public btCollisionWorld::ContactResultCallback {

		//! Constructor, pass whatever context you want to have available when processing contacts
		/*! You may also want to set m_collisionFilterGroup and m_collisionFilterMask
		 *  (supplied by the superclass) for needsCollision() */
		 //ContactSensorCallback(btRigidBody& tgtBody, YourContext& context /*, ... */)
		 //	: btCollisionWorld::ContactResultCallback(), body(tgtBody), ctxt(context) { }
		ContactSensorCallback() : ContactResultCallback() { }

		//btRigidBody& body; //!< The body the sensor is monitoring
		//YourContext& ctxt; //!< External information for contact processing

		//! If you don't want to consider collisions where the bodies are joined by a constraint, override needsCollision:
		/*! However, if you use a btCollisionObject for #body instead of a btRigidBody,
		 *  then this is unnecessary—checkCollideWithOverride isn't available */
		bool needsCollision(btBroadphaseProxy* proxy) const override
		{
			if (!ContactResultCallback::needsCollision(proxy))
			{
				return false;
			}
			// if passed filters, may also want to avoid contacts between constraints
			//return body.checkCollideWithOverride(static_cast<btCollisionObject*>(proxy->m_clientObject));
			return true;
		}

		btScalar addSingleResult(btManifoldPoint& cp,
			const btCollisionObjectWrapper* colObj0, int partId0, int index0,
			const btCollisionObjectWrapper* colObj1, int partId1, int index1) override
		{
			auto* collisionParameters1 = static_cast<CollisionParameters*>(colObj0->getCollisionObject()->getUserPointer());
			auto* collisionParameters2 = static_cast<CollisionParameters*>(colObj1->getCollisionObject()->getUserPointer());

			//std::ostringstream oss;
			//oss << collisionParameters1->GetEntity()->GetName() << " collide with " << collisionParameters2->GetEntity()->GetName() << std::endl;
			//OutputDebugStringA(oss.str().c_str());

			collisionParameters1->GetEntity()->HandleMessage(
				Telegram(0.0,
					collisionParameters1->GetEntity()->Id(),
					collisionParameters2->GetEntity()->Id(),
					(int)MessageType::COLLISION,
					new CollisionParametersBetween2Entities(collisionParameters1, collisionParameters2)));

			return 0;
		}
	};

	void BulletPhysicsWorld::ContactTest(ICollisionObjectContainer* collision_object_container)
	{
		static ContactSensorCallback callback;
		auto* bullet_collision_object_container = (BulletCollisionObjectContainer*)collision_object_container;
		_bulletWorld->contactTest(bullet_collision_object_container->GetCollisionObject(), callback);
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
