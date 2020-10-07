
#include "Base.h"
#include "PhysicalEntity.h"
#include "Maths/Matrix3.h"
#include "Maths/Matrix4.h"
#include <string>
#include "CA_Assert.h"
#include "Log\LogManager.h"
#include "Game\GameInfo.h"
#include "Entities\Components\Transform3DComponent.h"
#include "Entities\BaseEntity.h"
#include "Game/Game.h"
#include "Maths\Vector2.h"


namespace CasaEngine
{

/**
 * 
 */
PhysicalEntity::PhysicalEntity(BaseEntity *pEntity_)
{
	CA_ASSERT(pEntity_ != nullptr, "PhysicalEntity() : BaseEntity is null");
	m_pEntity = pEntity_;

	m_pRigidBody = nullptr;
}

/**
 * 
 */
PhysicalEntity::~PhysicalEntity()
{
	std::map<std::string, std::vector<ICollisionObjectContainer *> >::iterator it;
	for (it = m_SpriteCollisionObjects.begin();
		it != m_SpriteCollisionObjects.end();
		it++)
	{
		std::vector<ICollisionObjectContainer *>::iterator itColObj;
		for (itColObj = it->second.begin();
			itColObj != it->second.end();
			itColObj++)
		{
			Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->RemoveCollisionObject(*itColObj);
			DELETE_AO *itColObj;
		}
	}
}

/**
 *
 */
void PhysicalEntity::Update(GameTime gameTime_)
{
	Transform3DComponent *pTrans = m_pEntity->GetComponentMgr()->GetComponent<Transform3DComponent>();

	if (pTrans!= nullptr)
	{
		if (m_pRigidBody != nullptr)
		{
#if defined(CA_DEBUG)
			//m_pRigidBody->logInfo();
#endif // #if defined(CA_DEBUG)
			m_pRigidBody->setLinearVelocity(m_vVelocity);

			//ignore parent
			pTrans->SetLocalPosition(m_pRigidBody->getTranslation());
			pTrans->SetLocalRotation(m_pRigidBody->getRotation());
		}
		else
		{
			pTrans->SetLocalPosition(pTrans->GetLocalPosition() + m_vVelocity * gameTime_.FrameTime());
		}
	}
}

/**
 * 
 */
void PhysicalEntity::AddSpritePhysics(Sprite *pSprite_)
{
	if (m_LastSpriteID == pSprite_->GetName())
	{
		return;
	}

	m_LastSpriteID = pSprite_->GetName();

	//
	if (m_SpriteCollisionObjects.find(m_LastSpriteID) == m_SpriteCollisionObjects.end())
	{
		//m_SpriteCollisionObjects[m_LastSpriteID] = std::vector<ICollisionObjectContainer *>();

		//TODO : compute the position of the shape with the offset of the sprite
		Transform3DComponent *pTrans = m_pEntity->GetComponentMgr()->GetComponent<Transform3DComponent>();
		Vector3F pos = pTrans->GetLocalPosition();
		Vector2F origin(static_cast<float>(pSprite_->GetOrigin().x) / 100.0f, static_cast<float>(pSprite_->GetOrigin().y) / 100.0f);
		Vector3F posWithOrigin(pos.x - origin.x, pos.y + origin.y, pos.z); 

		std::vector<IShape *>::iterator itShape;
		for (itShape = pSprite_->GetCollisionShapeIterator();
			itShape != pSprite_->GetCollisionShapeIteratorEnd();
			itShape++)
		{
			ICollisionObjectContainer *pObj = 
				Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->AddCollisionShape(*itShape, posWithOrigin);
			m_SpriteCollisionObjects[m_LastSpriteID].push_back(pObj);
		}
	}
	else
	{
		std::vector<ICollisionObjectContainer *>::iterator it;

		for (it = m_SpriteCollisionObjects[m_LastSpriteID].begin();
			it != m_SpriteCollisionObjects[m_LastSpriteID].end();
			it++)
		{
			Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->AddCollisionObject(*it);
		}
	}
}

/**
 * 
 */
void PhysicalEntity::RemoveSpritePhysics(Sprite *pSprite_)
{
	if (m_SpriteCollisionObjects.find(m_LastSpriteID) != m_SpriteCollisionObjects.end())
	{
		std::vector<ICollisionObjectContainer *>::iterator itColObj;
		for (itColObj = m_SpriteCollisionObjects[m_LastSpriteID].begin();
			itColObj != m_SpriteCollisionObjects[m_LastSpriteID].end();
			itColObj++)
		{
			Game::Instance().GetGameInfo().GetWorld()->GetPhysicsWorld()->RemoveCollisionObject(*itColObj);
		}
	}
}

/**
 *
 */
IRigidBodyContainer *PhysicalEntity::GetRigidBody()
{
	return m_pRigidBody;
}

/**
 * 
 */
void PhysicalEntity::SetRigidBody(IRigidBodyContainer *val_)
{
	CA_ASSERT(m_pRigidBody == nullptr, "PhysicalEntity::SetRigidBody() : RigidBody is already set");
	m_pRigidBody = val_;
}


Vector3F  PhysicalEntity::Velocity()const{return m_vVelocity;}
void      PhysicalEntity::SetVelocity(const Vector3F& NewVel){m_vVelocity = NewVel;}

float     PhysicalEntity::Mass()const{return m_fMass;}
void      PhysicalEntity::Mass(float mass_){m_fMass = mass_;}

Vector3F  PhysicalEntity::Side()const{return m_vSide;}
void      PhysicalEntity::Side(Vector3F side_){m_vSide = side_;}

float     PhysicalEntity::MaxSpeed()const{return m_fMaxSpeed;}
void      PhysicalEntity::SetMaxSpeed(float new_speed){m_fMaxSpeed = new_speed;}

float     PhysicalEntity::MaxForce()const{return m_fMaxForce;}
void      PhysicalEntity::SetMaxForce(float mf){m_fMaxForce = mf;}

bool      PhysicalEntity::IsSpeedMaxedOut()const{return m_fMaxSpeed*m_fMaxSpeed >= m_vVelocity.LengthSquared();}
float     PhysicalEntity::Speed() const{return m_vVelocity.Length();}
float     PhysicalEntity::SpeedSq() const{return m_vVelocity.LengthSquared();}

Vector3F  PhysicalEntity::Heading() const{return m_vHeading;}

float     PhysicalEntity::MaxTurnRate() const{return m_fMaxTurnRate;}
void      PhysicalEntity::SetMaxTurnRate(float val){m_fMaxTurnRate = val;}


//--------------------------- RotateHeadingToFacePosition ---------------------
//
//  given a target position, this method rotates the entity's heading and
//  side vectors by an amount not greater than m_dMaxTurnRate until it
//  directly faces the target.
//
//  returns true when the heading is facing in the desired direction
//-----------------------------------------------------------------------------
inline bool PhysicalEntity::RotateHeadingToFacePosition(Vector3F target)
{
// 	Vector3F toTarget = target - m_pTransform->GetPosition();
// 	toTarget.Normalize();
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
inline void PhysicalEntity::SetHeading(Vector3F new_heading)
{
	CA_ASSERT((new_heading.LengthSquared() - 1.0) < 0.00001, "PhysicalEntity::SetHeading() : don't use Vector::Zero");

	m_vHeading = new_heading;

	//the side vector must always be perpendicular to the heading
	m_vSide = m_vHeading.GetOrthogonal();
}


/**
 * 
 */
void PhysicalEntity::Write(std::ostream& /*os*/)
{

}

/**
 * 
 */
void PhysicalEntity::Read (std::ifstream& /*is*/)
{

}

}
