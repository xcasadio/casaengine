#include "Base.h"
#include "PhysicalEntity.h"
#include <string>
#include "CA_Assert.h"
#include "Log/LogManager.h"
#include "Game/GameInfo.h"
#include "Entities/BaseEntity.h"
#include "Game/Game.h"

namespace CasaEngine
{
	PhysicalEntity::PhysicalEntity(BaseEntity* entity) :
		m_fMass(0),
		m_fMaxSpeed(0),
		m_fMaxForce(0),
		m_fMaxTurnRate(0)
	{
		CA_ASSERT(entity != nullptr, "PhysicalEntity() : BaseEntity is null");
		m_pEntity = entity;

		m_pRigidBody = nullptr;
	}

	PhysicalEntity::~PhysicalEntity()
	{
		for (std::map<std::string, std::vector<ICollisionObjectContainer*>>::iterator it = m_SpriteCollisionObjects.begin();
			it != m_SpriteCollisionObjects.end();
			++it)
		{
			std::vector<ICollisionObjectContainer*>::iterator itColObj;
			for (itColObj = it->second.begin();
				itColObj != it->second.end();
				++itColObj)
			{
				Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld().RemoveCollisionObject(*itColObj);
				delete* itColObj;
			}
		}
	}

	void PhysicalEntity::Update(const GameTime& gameTime_)
	{
		if (m_pRigidBody != nullptr)
		{
#if defined(CA_DEBUG)
			//m_pRigidBody->logInfo();
#endif // #if defined(CA_DEBUG)
			m_pRigidBody->setLinearVelocity(m_vVelocity);

			//ignore parent
			m_pEntity->GetCoordinates().SetLocalPosition(m_pRigidBody->getTranslation());
			m_pEntity->GetCoordinates().SetLocalRotation(m_pRigidBody->getRotation());
		}
		else if (!m_vVelocity.IsZero())
		{
			m_pEntity->GetCoordinates().SetLocalPosition(m_pEntity->GetCoordinates().GetLocalPosition() + m_vVelocity * gameTime_.FrameTime());
		}
	}

	IRigidBodyContainer* PhysicalEntity::GetRigidBody()
	{
		return m_pRigidBody;
	}

	void PhysicalEntity::SetRigidBody(IRigidBodyContainer* val_)
	{
		CA_ASSERT(m_pRigidBody == nullptr, "PhysicalEntity::SetRigidBody() : RigidBody is already set");
		m_pRigidBody = val_;
	}


	Vector3  PhysicalEntity::Velocity()const { return m_vVelocity; }
	void      PhysicalEntity::SetVelocity(const Vector3& NewVel) { m_vVelocity = NewVel; }

	float     PhysicalEntity::Mass()const { return m_fMass; }
	void      PhysicalEntity::Mass(float mass_) { m_fMass = mass_; }

	Vector3  PhysicalEntity::Side()const { return m_vSide; }
	void      PhysicalEntity::Side(Vector3 side_) { m_vSide = side_; }

	float     PhysicalEntity::MaxSpeed()const { return m_fMaxSpeed; }
	void      PhysicalEntity::SetMaxSpeed(float new_speed) { m_fMaxSpeed = new_speed; }

	float     PhysicalEntity::MaxForce()const { return m_fMaxForce; }
	void      PhysicalEntity::SetMaxForce(float mf) { m_fMaxForce = mf; }

	bool      PhysicalEntity::IsSpeedMaxedOut()const { return m_fMaxSpeed * m_fMaxSpeed >= m_vVelocity.LengthSquared(); }
	float     PhysicalEntity::Speed() const { return m_vVelocity.Length(); }
	float     PhysicalEntity::SpeedSq() const { return m_vVelocity.LengthSquared(); }

	Vector3  PhysicalEntity::Heading() const { return m_vHeading; }

	float     PhysicalEntity::MaxTurnRate() const { return m_fMaxTurnRate; }
	void      PhysicalEntity::SetMaxTurnRate(float val) { m_fMaxTurnRate = val; }


	//--------------------------- RotateHeadingToFacePosition ---------------------
	//
	//  given a target position, this method rotates the entity's heading and
	//  side vectors by an amount not greater than m_dMaxTurnRate until it
	//  directly faces the target.
	//
	//  returns true when the heading is facing in the desired direction
	//-----------------------------------------------------------------------------
	inline bool PhysicalEntity::RotateHeadingToFacePosition(Vector3 target)
	{
		// 	Vector3 toTarget = target - m_pTransform->GetPosition();
		// 	toTarget.Normalized();
		// 
		// 	//first determine the angle between the heading vector and the target
		// 	float angle = acos(m_vHeading.Dot(toTarget));
		// 
		// 	//return true if the player is facing the target
		// 	if (angle < 0.00001f) return true;
		// 
		// 	//clamp the amount to turn to the max turn rate
		// 	if (angle > m_fMaxTurnRate) angle = m_fMaxTurnRate;
		// 
		// 	//The next few lines use a rotation matrix to rotate the player's heading
		// 	//vector accordingly
		// 	Matrix3 RotationMatrix;
		// 
		// 	//notice how the direction of rotation has to be determined when creating
		// 	//the rotation matrix
		// 	RotationMatrix.Rotate(angle * m_vHeading.Sign(toTarget));	
		// 	RotationMatrix.TransformVector3F(m_vHeading);
		// 	RotationMatrix.TransformVector3F(m_vVelocity);
		// 
		// 	//finally recreate m_vSide
		// 	m_vSide = m_vHeading.GetOrthogonal();

		return false;
	}


	//------------------------- SetHeading ----------------------------------------
	//
	//  first checks that the given heading is not a vector of zero length. If the
	//  new heading is valid this fumction sets the entity's heading and side 
	//  vectors accordingly
	//-----------------------------------------------------------------------------
	inline void PhysicalEntity::SetHeading(Vector3 new_heading)
	{
		CA_ASSERT((new_heading.LengthSquared() - 1.0f) < 0.00001f, "PhysicalEntity::SetHeading() : don't use Vector::Zero");

		m_vHeading = new_heading;

		//the side vector must always be perpendicular to the heading
		m_vSide = m_vHeading.GetOrthogonal();
	}

	void PhysicalEntity::Write(std::ostream& /*os*/)
	{

	}

	void PhysicalEntity::Read(std::ifstream& /*is*/)
	{

	}
}
