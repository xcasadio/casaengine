#include "Base.h"
#include "SteeringBehaviorComponent.h"

#include "Entities/BaseEntity.h"
#include "Entities/ComponentTypeEnum.h"
#include "Game/Game.h"
#include "Game/GameInfo.h"
#include "Graphics/Color.h"
#include "Maths/2D/Geometry.h"
#include "Maths/2D/Geometry.h"
#include "Maths/2D/Line2D.h"
#include "Maths/2D/Transformations.h"
#include "Maths/2D/Transformations.h"
#include "Maths/Math.h"
#include "Maths/Matrix4.h"
#include "Maths/Random.h"
#include "Maths/Vector2.h"
#include "MovingEntity2DComponent.h"
#include "Resources/ResourceManager.h"
#include "Sprite/SpriteRenderer.h"
#include "Sprite/SpriteTypes.h"
#include "Transform2DComponent.h"
#include "StringUtils.h"
#include "Exceptions.h"

namespace CasaEngine
{

/**
 * 
 */
SteeringBehaviorComponent::SteeringBehaviorComponent(BaseEntity* pEntity_)
	: Component(pEntity_, STEERING_BEHAVIOUR_2D),
		m_pMovingEntity(nullptr),
		m_iFlags(0),
		m_Deceleration(NORMAL),
		m_pTargetAgent1(nullptr),
		m_pTargetAgent2(nullptr),
		m_bCellSpaceOn(true),
		m_SummingMethod(PRIORITIZED)
{

}

/**
 * 
 */
SteeringBehaviorComponent::~SteeringBehaviorComponent()
{

}

/**
 * 
 */
void SteeringBehaviorComponent::Initialize()
{
	m_pTranform = GetEntity()->GetComponentMgr()->GetComponent<Transform3DComponent>();
	CA_ASSERT(m_pTranform != nullptr, 
		"SteeringBehaviorComponent::Initialize() can't find the Transform3DComponent. Please add it before add a SteeringBehaviorComponent");

	m_pMovingEntity = GetEntity()->GetComponentMgr()->GetComponent<MovingEntity2DComponent>();
	CA_ASSERT(m_pMovingEntity != nullptr,
		"SteeringBehaviorComponent::Initialize() can't find the MovingEntity2DComponent. Please add it before add a SteeringBehaviorComponent");
}

/**
 * 
 */
void SteeringBehaviorComponent::Update(const GameTime& gameTime_)
{
	Calculate(gameTime_.FrameTime());
	m_pTranform->SetLocalPosition(Vector3F(m_Position2D.x, m_pTranform->GetPosition().y, m_Position2D.y));
}

/**
 * 
 */
/*void SteeringBehaviourComponent::HandleEvent(const Event* pEvent_)
{

}*/

/**
 * 
 */
void SteeringBehaviorComponent::Write(std::ostream& /*os*/) const
{

}

/**
 * 
 */
void SteeringBehaviorComponent::Read (std::ifstream& /*is*/)
{

}

/////////////////////////////////////////////////////////////////////////////// CALCULATE METHODS 


//----------------------- Calculate --------------------------------------
//
//  calculates the accumulated steering force according to the method set
//  in m_SummingMethod
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::Calculate(float elapsedTime_)
{ 
	//reset the steering force
	m_vSteeringForce.Set(0.0f, 0.0f);

	//use space partitioning to calculate the neighbors of this BaseEntity
	//if switched on. If not, use the standard tagging system
// 	if (!isSpacePartitioningOn())
// 	{
// 		//tag neighbors if any of the following 3 group behaviors are switched on
// 		if (On(separation) || On(allignment) || On(cohesion))
// 		{
// 			GameInfo::Instance().GetWorld()->TagVehiclesWithinViewRange(GetEntity(), m_dViewDistance);
// 		}
// 	}
// 	else
// 	{
		//calculate neighbors in cell-space if any of the following 3 group
		//behaviors are switched on
		if (On(separation) || On(allignment) || On(cohesion))
		{
			GameInfo::Instance().GetWorld()->GetSpacePartition().CalculateNeighbors(m_Position2D, m_fViewDistance);
		}
// 	}

	switch (m_SummingMethod)
	{
	case WEIGHTED_AVERAGE:    
		m_vSteeringForce = CalculateWeightedSum(elapsedTime_); 
		break;

	case PRIORITIZED:
		m_vSteeringForce = CalculatePrioritized(elapsedTime_); 
		break;

	case DITHERED:    
		m_vSteeringForce = CalculateDithered(elapsedTime_);
		break;

	default:
		m_vSteeringForce = Vector2F(0,0);
	}//end switch

  return m_vSteeringForce;
}

//------------------------- ForwardComponent -----------------------------
//
//  returns the forward component of the steering force
//------------------------------------------------------------------------
float SteeringBehaviorComponent::ForwardComponent()
{
	Vector3F tmp = this->GetEntity()->GetPhysicalEntity().Heading();
	Vector2F heading(tmp.x, tmp.z);
	return heading.Dot(m_vSteeringForce);
}

//--------------------------- SideComponent ------------------------------
//  returns the side component of the steering force
//------------------------------------------------------------------------
float SteeringBehaviorComponent::SideComponent()
{
	Vector3F tmp = this->GetEntity()->GetPhysicalEntity().Side();
	Vector2F side(tmp.x, tmp.z);
	return side.Dot(m_vSteeringForce);
}


//--------------------- AccumulateForce ----------------------------------
//
//  This function calculates how much of its max steering force the 
//  BaseEntity has left to apply and then applies that amount of the
//  force to add.
//------------------------------------------------------------------------
bool SteeringBehaviorComponent::AccumulateForce(Vector2F &RunningTot, Vector2F ForceToAdd)
{
	//calculate how much steering force the BaseEntity has used so far
	float MagnitudeSoFar = RunningTot.Length();

	//calculate how much steering force remains to be used by this BaseEntity
	float MagnitudeRemaining = this->GetEntity()->GetPhysicalEntity().MaxForce() - MagnitudeSoFar;

	//return false if there is no more force left to use
	if (MagnitudeRemaining <= 0.0) return false;

	//calculate the magnitude of the force we want to add
	float MagnitudeToAdd = ForceToAdd.Length();
  
	//if the magnitude of the sum of ForceToAdd and the running total
	//does not exceed the maximum force available to this BaseEntity, just
	//add together. Otherwise add as much of the ForceToAdd vector is
	//possible without going over the max.
	if (MagnitudeToAdd < MagnitudeRemaining)
	{
		RunningTot += ForceToAdd;
	}
	else
	{
		ForceToAdd.Normalize();
		//add it to the steering force
		RunningTot += (ForceToAdd * MagnitudeRemaining); 
	}
}



//---------------------- CalculatePrioritized ----------------------------
//
//  this method calls each active steering behavior in order of priority
//  and accumulates their forces until the max steering force magnitude
//  is reached, at which time the function returns the steering force 
//  accumulated to that  point
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::CalculatePrioritized(float elapsedTime_)
{       
	Vector2F force;
  
// 	if (On(wall_avoidance))
// 	{
// 		force = WallAvoidance(GameInfo::Instance().GetWorld()->Walls()) * m_fWeightWallAvoidance;
// 		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 	}
//    
// 	if (On(obstacle_avoidance))
// 	{
// 		force = ObstacleAvoidance(GameInfo::Instance().GetWorld()->Obstacles()) * m_fWeightObstacleAvoidance;
// 		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 	}
// 
// 	if (On(evade))
// 	{
// 		CA_ASSERT(m_pTargetAgent1 != nullptr, "Evade target not assigned");    
// 		force = Evade(m_pTargetAgent1) * m_fWeightEvade;
// 		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 	}
//   
// 	if (On(flee))
// 	{
// 		force = Flee(GameInfo::Instance().GetWorld()->Crosshair()) * m_fWeightFlee;
// 		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 	}
//  
// 	//these next three can be combined for flocking behavior (wander is
// 	//also a good behavior to add into this mix)
// 	if (!isSpacePartitioningOn())
// 	{
// 		if (On(separation))
// 		{
// 			force = Separation(GameInfo::Instance().GetWorld()->GetEntities()) * m_fWeightSeparation;
// 			if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 		}
// 
// 		if (On(allignment))
// 		{
// 			force = Alignment(GameInfo::Instance().GetWorld()->GetEntities()) * m_fWeightAlignment;
// 			if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 		}
// 
// 		if (On(cohesion))
// 		{
// 			force = Cohesion(GameInfo::Instance().GetWorld()->GetEntities()) * m_fWeightCohesion;
// 			if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 		}
// 	}
// 	else
// 	{
// 		if (On(separation))
// 		{
// 			force = SeparationPlus(GameInfo::Instance().GetWorld()->GetEntities()) * m_fWeightSeparation;
// 			if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 		}
// 
// 		if (On(allignment))
// 		{
// 			force = AlignmentPlus(GameInfo::Instance().GetWorld()->GetEntities()) * m_fWeightAlignment;
// 			if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 		}
// 
// 		if (On(cohesion))
// 		{
// 			force = CohesionPlus(GameInfo::Instance().GetWorld()->GetEntities()) * m_fWeightCohesion;
// 			if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 		}
// 	}
// 
// 	if (On(seek))
// 	{
// 		force = Seek(GameInfo::Instance().GetWorld()->Crosshair()) * m_fWeightSeek;
// 		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 	}
// 
// 	if (On(arrive))
// 	{
// 		force = Arrive(GameInfo::Instance().GetWorld()->Crosshair(), m_Deceleration) * m_fWeightArrive;
// 		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 	}
// 
// 	if (On(wander))
// 	{
// 		force = Wander(elapsedTime_) * m_fWeightWander;
// 		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 	}
// 
// 	if (On(pursuit))
// 	{
// 		CA_ASSERT(m_pTargetAgent1, "pursuit target not assigned");
// 		force = Pursuit(m_pTargetAgent1) * m_fWeightPursuit;
// 		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 	}
// 
// 	if (On(offset_pursuit))
// 	{
// 		CA_ASSERT(m_pTargetAgent1, "pursuit target not assigned");
// 		CA_ASSERT(!m_vOffset.IsZero(), "No offset assigned");
// 		force = OffsetPursuit(m_pTargetAgent1, m_vOffset);
// 		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 	}
// 
// 	if (On(interpose))
// 	{
// 		CA_ASSERT(m_pTargetAgent1 && m_pTargetAgent2, "Interpose agents not assigned");
// 		force = Interpose(m_pTargetAgent1, m_pTargetAgent2) * m_fWeightInterpose;
// 		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 	}
// 
// 	if (On(hide))
// 	{
// 		CA_ASSERT(m_pTargetAgent1, "Hide target not assigned");
// 		force = Hide(m_pTargetAgent1, GameInfo::Instance().GetWorld()->Obstacles()) * m_fWeightHide;
// 		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 	}
// 
// 	if (On(follow_path))
// 	{
// 		force = FollowPath() * m_fWeightFollowPath;
// 		if (!AccumulateForce(m_vSteeringForce, force)) return m_vSteeringForce;
// 	}

	return m_vSteeringForce;
}


//---------------------- CalculateWeightedSum ----------------------------
//
//  this simply sums up all the active behaviors X their weights and 
//  truncates the result to the max available steering force before 
//  returning
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::CalculateWeightedSum(float elapsedTime_)
{        
//   if (On(wall_avoidance))
//   {
//     m_vSteeringForce += WallAvoidance(GameInfo::Instance().GetWorld()->Walls()) *
//                          m_fWeightWallAvoidance;
//   }
//    
//   if (On(obstacle_avoidance))
//   {
//     m_vSteeringForce += ObstacleAvoidance(GameInfo::Instance().GetWorld()->Obstacles()) * 
//             m_fWeightObstacleAvoidance;
//   }
// 
//   if (On(evade))
//   {
//     CA_ASSERT(m_pTargetAgent1, "Evade target not assigned");
//     
//     m_vSteeringForce += Evade(m_pTargetAgent1) * m_fWeightEvade;
//   }
// 
// 
//   //these next three can be combined for flocking behavior (wander is
//   //also a good behavior to add into this mix)
//   /*if (!isSpacePartitioningOn())
//   {
//     if (On(separation))
//     {
//       m_vSteeringForce += Separation(GameInfo::Instance().GetWorld()->GetEntities()) * m_fWeightSeparation;
//     }
// 
//     if (On(allignment))
//     {
//       m_vSteeringForce += Alignment(GameInfo::Instance().GetWorld()->GetEntities()) * m_fWeightAlignment;
//     }
// 
//     if (On(cohesion))
//     {
//       m_vSteeringForce += Cohesion(GameInfo::Instance().GetWorld()->GetEntities()) * m_fWeightCohesion;
//     }
//   }
//   else
//   {*/
//     if (On(separation))
//     {
//       m_vSteeringForce += SeparationPlus(GameInfo::Instance().GetWorld()->GetEntities()) * m_fWeightSeparation;
//     }
// 
//     if (On(allignment))
//     {
//       m_vSteeringForce += AlignmentPlus(GameInfo::Instance().GetWorld()->GetEntities()) * m_fWeightAlignment;
//     }
// 
//     if (On(cohesion))
//     {
//       m_vSteeringForce += CohesionPlus(GameInfo::Instance().GetWorld()->GetEntities()) * m_fWeightCohesion;
//     }
//   //}
// 
// 
//   if (On(wander))
//   {
//     m_vSteeringForce += Wander(elapsedTime_) * m_fWeightWander;
//   }
// 
//   if (On(seek))
//   {
//     m_vSteeringForce += Seek(GameInfo::Instance().GetWorld()->Crosshair()) * m_fWeightSeek;
//   }
// 
//   if (On(flee))
//   {
//     m_vSteeringForce += Flee(GameInfo::Instance().GetWorld()->Crosshair()) * m_fWeightFlee;
//   }
// 
//   if (On(arrive))
//   {
//     m_vSteeringForce += Arrive(GameInfo::Instance().GetWorld()->Crosshair(), m_Deceleration) * m_fWeightArrive;
//   }
// 
//   if (On(pursuit))
//   {
//     CA_ASSERT(m_pTargetAgent1 != nullptr, "pursuit target not assigned");
// 
//     m_vSteeringForce += Pursuit(m_pTargetAgent1) * m_fWeightPursuit;
//   }
// 
//   if (On(offset_pursuit))
//   {
//     CA_ASSERT(m_pTargetAgent1, "pursuit target not assigned");
//     CA_ASSERT(!m_vOffset.IsZero(), "No offset assigned");
// 
//     m_vSteeringForce += OffsetPursuit(m_pTargetAgent1, m_vOffset) * m_fWeightOffsetPursuit;
//   }
// 
//   if (On(interpose))
//   {
//     CA_ASSERT(m_pTargetAgent1 && m_pTargetAgent2, "Interpose agents not assigned");
// 
//     m_vSteeringForce += Interpose(m_pTargetAgent1, m_pTargetAgent2) * m_fWeightInterpose;
//   }
// 
//   if (On(hide))
//   {
//     CA_ASSERT(m_pTargetAgent1, "Hide target not assigned");
// 
//     m_vSteeringForce += Hide(m_pTargetAgent1, GameInfo::Instance().GetWorld()->Obstacles()) * m_fWeightHide;
//   }
// 
//   if (On(follow_path))
//   {
//     m_vSteeringForce += FollowPath() * m_fWeightFollowPath;
//   }
// 
//   m_vSteeringForce.Truncate(this->GetEntity()->GetPhysicalEntity().MaxForce());
//  
   return m_vSteeringForce;
}


//---------------------- CalculateDithered ----------------------------
//
//  this method sums up the active behaviors by assigning a probability
//  of being calculated to each behavior. It then tests the first priority
//  to see if it should be calculated this simulation-step. If so, it
//  calculates the steering force resulting from this behavior. If it is
//  more than zero it returns the force. If zero, or if the behavior is
//  skipped it continues onto the next priority, and so on.
//
//  NOTE: Not all of the behaviors have been implemented in this method,
//        just a few, so you get the general idea
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::CalculateDithered(float elapsedTime_)
{  
//   //reset the steering force
//    m_vSteeringForce.Set(0.0f, 0.0f);
// 
//   if (On(wall_avoidance) && RandFloat() < PrWallAvoidance())
//   {
//     m_vSteeringForce = WallAvoidance(GameInfo::Instance().GetWorld()->Walls()) *
//                          m_fWeightWallAvoidance / PrWallAvoidance();
// 
//     if (!m_vSteeringForce.IsZero())
//     {
//       m_vSteeringForce.Truncate(this->GetEntity()->GetPhysicalEntity().MaxForce()); 
//       
//       return m_vSteeringForce;
//     }
//   }
//    
//   if (On(obstacle_avoidance) && RandFloat() < PrObstacleAvoidance())
//   {
//     m_vSteeringForce += ObstacleAvoidance(GameInfo::Instance().GetWorld()->Obstacles()) * 
//             m_fWeightObstacleAvoidance / PrObstacleAvoidance();
// 
//     if (!m_vSteeringForce.IsZero())
//     {
//       m_vSteeringForce.Truncate(this->GetEntity()->GetPhysicalEntity().MaxForce()); 
//       
//       return m_vSteeringForce;
//     }
//   }
// 
//   /*if (!isSpacePartitioningOn())
//   {
//     if (On(separation) && RandFloat() < PrSeparation())
//     {
//       m_vSteeringForce += Separation(GameInfo::Instance().GetWorld()->GetEntities()) * 
//                           m_fWeightSeparation / PrSeparation();
// 
//       if (!m_vSteeringForce.IsZero())
//       {
//         m_vSteeringForce.Truncate(this->GetEntity()->GetPhysicalEntity().MaxForce()); 
//       
//         return m_vSteeringForce;
//       }
//     }
//   }
// 
//   else
//   {*/
//     if (On(separation) && RandFloat() < PrSeparation())
//     {
//       m_vSteeringForce += SeparationPlus(GameInfo::Instance().GetWorld()->GetEntities()) * 
//                           m_fWeightSeparation / PrSeparation();
// 
//       if (!m_vSteeringForce.IsZero())
//       {
//         m_vSteeringForce.Truncate(this->GetEntity()->GetPhysicalEntity().MaxForce()); 
//       
//         return m_vSteeringForce;
//       }
//     }
//   //}
// 
// 
//   if (On(flee) && RandFloat() < PrFlee())
//   {
//     m_vSteeringForce += Flee(GameInfo::Instance().GetWorld()->Crosshair()) * m_fWeightFlee / PrFlee();
// 
//     if (!m_vSteeringForce.IsZero())
//     {
//       m_vSteeringForce.Truncate(this->GetEntity()->GetPhysicalEntity().MaxForce()); 
//       
//       return m_vSteeringForce;
//     }
//   }
// 
//   if (On(evade) && RandFloat() < PrEvade())
//   {
//     CA_ASSERT(m_pTargetAgent1, "Evade target not assigned");
//     
//     m_vSteeringForce += Evade(m_pTargetAgent1) * m_fWeightEvade / PrEvade();
// 
//     if (!m_vSteeringForce.IsZero())
//     {
//       m_vSteeringForce.Truncate(this->GetEntity()->GetPhysicalEntity().MaxForce()); 
//       
//       return m_vSteeringForce;
//     }
//   }
// 
// 
//   /*if (!isSpacePartitioningOn())
//   {
//     if (On(allignment) && RandFloat() < PrAlignment())
//     {
//       m_vSteeringForce += Alignment(GameInfo::Instance().GetWorld()->GetEntities()) *
//                           m_fWeightAlignment / PrAlignment();
// 
//       if (!m_vSteeringForce.IsZero())
//       {
//         m_vSteeringForce.Truncate(this->GetEntity()->GetPhysicalEntity().MaxForce()); 
//       
//         return m_vSteeringForce;
//       }
//     }
// 
//     if (On(cohesion) && RandFloat() < PrCohesion())
//     {
//       m_vSteeringForce += Cohesion(GameInfo::Instance().GetWorld()->GetEntities()) * 
//                           m_fWeightCohesion / PrCohesion();
// 
//       if (!m_vSteeringForce.IsZero())
//       {
//         m_vSteeringForce.Truncate(this->GetEntity()->GetPhysicalEntity().MaxForce()); 
//       
//         return m_vSteeringForce;
//       }
//     }
//   }
//   else
//   {*/
//     if (On(allignment) && RandFloat() < PrAlignment())
//     {
//       m_vSteeringForce += AlignmentPlus(GameInfo::Instance().GetWorld()->GetEntities()) *
//                           m_fWeightAlignment / PrAlignment();
// 
//       if (!m_vSteeringForce.IsZero())
//       {
//         m_vSteeringForce.Truncate(this->GetEntity()->GetPhysicalEntity().MaxForce()); 
//       
//         return m_vSteeringForce;
//       }
//     }
// 
//     if (On(cohesion) && RandFloat() < PrCohesion())
//     {
//       m_vSteeringForce += CohesionPlus(GameInfo::Instance().GetWorld()->GetEntities()) *
//                           m_fWeightCohesion / PrCohesion();
// 
//       if (!m_vSteeringForce.IsZero())
//       {
//         m_vSteeringForce.Truncate(this->GetEntity()->GetPhysicalEntity().MaxForce()); 
//       
//         return m_vSteeringForce;
//       }
//     }
//   //}
// 
//   if (On(wander) && RandFloat() < PrWander())
//   {
//     m_vSteeringForce += Wander(elapsedTime_) * m_fWeightWander / PrWander();
// 
//     if (!m_vSteeringForce.IsZero())
//     {
//       m_vSteeringForce.Truncate(this->GetEntity()->GetPhysicalEntity().MaxForce()); 
//       
//       return m_vSteeringForce;
//     }
//   }
// 
//   if (On(seek) && RandFloat() < PrSeek())
//   {
//     m_vSteeringForce += Seek(GameInfo::Instance().GetWorld()->Crosshair()) * m_fWeightSeek / PrSeek();
// 
//     if (!m_vSteeringForce.IsZero())
//     {
//       m_vSteeringForce.Truncate(this->GetEntity()->GetPhysicalEntity().MaxForce()); 
//       
//       return m_vSteeringForce;
//     }
//   }
// 
//   if (On(arrive) && RandFloat() < PrArrive())
//   {
//     m_vSteeringForce += Arrive(GameInfo::Instance().GetWorld()->Crosshair(), m_Deceleration) * 
//                         m_fWeightArrive / PrArrive();
// 
//     if (!m_vSteeringForce.IsZero())
//     {
//       m_vSteeringForce.Truncate(this->GetEntity()->GetPhysicalEntity().MaxForce()); 
//       
//       return m_vSteeringForce;
//     }
//   }
 
  return m_vSteeringForce;
}



/////////////////////////////////////////////////////////////////////////////// START OF BEHAVIORS

//------------------------------- Seek -----------------------------------
//
//  Given a target, this behavior returns a steering force which will
//  direct the agent towards the target
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::Seek(Vector2F TargetPos)
{
//   Vector2F DesiredVelocity = TargetPos - m_Position2D;
//   DesiredVelocity.Normalize();
//   DesiredVelocity *= this->GetEntity()->GetPhysicalEntity().MaxSpeed();
// 
//   return (DesiredVelocity - this->GetEntity()->GetPhysicalEntity().Velocity());
	return Vector2F::Zero();
}

//----------------------------- Flee -------------------------------------
//
//  Does the opposite of Seek
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::Flee(Vector2F TargetPos)
{
//   //only flee if the target is within 'panic distance'. Work in distance
//   //squared space.
//  /* const float PanicDistanceSq = 100.0f * 100.0;
//   if (Vec2DDistanceSq(m_Position2D, target) > PanicDistanceSq)
//   {
//     return Vector2F(0,0);
//   }
//   */
// 
//   Vector2F DesiredVelocity = m_Position2D - TargetPos;
//   DesiredVelocity.Normalize();
//   DesiredVelocity *= this->GetEntity()->GetPhysicalEntity().MaxSpeed();
// 
//   return (DesiredVelocity - this->GetEntity()->GetPhysicalEntity().Velocity());
	return Vector2F::Zero();
}

//--------------------------- Arrive -------------------------------------
//
//  This behavior is similar to seek but it attempts to arrive at the
//  target with a zero velocity
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::Arrive(Vector2F     TargetPos,
                                  Deceleration deceleration)
{
//   Vector2F ToTarget = TargetPos - m_Position2D;
// 
//   //calculate the distance to the target
//   float dist = ToTarget.Length();
// 
//   if (dist > 0)
//   {
//     //because Deceleration is enumerated as an int, this value is required
//     //to provide fine tweaking of the deceleration..
//     const float DecelerationTweaker = 0.3f;
// 
//     //calculate the speed required to reach the target given the desired
//     //deceleration
//     float speed =  dist / ((float)deceleration * DecelerationTweaker);     
// 
//     //make sure the velocity does not exceed the max
//     speed = MinOf(speed, this->GetEntity()->GetPhysicalEntity().MaxSpeed());
// 
//     //from here proceed just like Seek except we don't need to normalize 
//     //the ToTarget vector because we have already gone to the trouble
//     //of calculating its length: dist. 
//     Vector2F DesiredVelocity =  ToTarget * speed / dist;
// 
//     return (DesiredVelocity - this->GetEntity()->GetPhysicalEntity().Velocity());
//   }

  return Vector2F::Zero();
}

//------------------------------ Pursuit ---------------------------------
//
//  this behavior creates a force that steers the agent towards the 
//  evader
//------------------------------------------------------------------------
CasaEngine::Vector2F SteeringBehaviorComponent::Pursuit( BaseEntity* evader )
{
// 	Transform2DComponent *pEvaderTrans2D = evader->GetComponentMgr()->GetComponent<Transform2DComponent>();
// 	PhysicComponent *pEvaderPhysic = evader->GetComponentMgr()->GetComponent<PhysicComponent>();
// 
//   //if the evader is ahead and facing the agent then we can just seek
//   //for the evader's current position.
//   Vector2F ToEvader = pEvaderTrans2D->GetPosition() - m_Position2D;
// 
//   float RelativeHeading = this->GetEntity()->GetPhysicalEntity().Heading().Dot(pEvaderPhysic->Heading());
// 
//   if ( (ToEvader.Dot(this->GetEntity()->GetPhysicalEntity().Heading()) > 0.0f) &&  
//        (RelativeHeading < -0.95f))  //acos(0.95)=18 degs
//   {
//     return Seek(pEvaderTrans2D->GetPosition());
//   }
// 
//   //Not considered ahead so we predict where the evader will be.
//  
//   //the lookahead time is propotional to the distance between the evader
//   //and the pursuer; and is inversely proportional to the sum of the
//   //agent's velocities
//   float LookAheadTime = ToEvader.Length() / 
//                         (this->GetEntity()->GetPhysicalEntity().MaxSpeed() + pEvaderPhysic->Speed());
//   
//   //now seek to the predicted future position of the evader
//   return Seek(pEvaderTrans2D->GetPosition() + pEvaderPhysic->Velocity() * LookAheadTime);

	return Vector2F::Zero();
}


//----------------------------- Evade ------------------------------------
//
//  similar to pursuit except the agent Flees from the estimated future
//  position of the pursuer
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::Evade( BaseEntity* pursuer )
{
// 	Transform2DComponent *pEvaderTrans2D = pursuer->GetComponentMgr()->GetComponent<Transform2DComponent>();
// 	PhysicComponent *pEvaderPhysic = pursuer->GetComponentMgr()->GetComponent<PhysicComponent>();
// 
//   /* Not necessary to include the check for facing direction this time */
// 
//   Vector2F ToPursuer = pEvaderTrans2D->GetPosition() - m_Position2D;
// 
//   //uncomment the following two lines to have Evade only consider pursuers 
//   //within a 'threat range'
//   const float ThreatRange = 100.0f;
//   if (ToPursuer.LengthSquared() > ThreatRange * ThreatRange) return Vector2F();
//  
//   //the lookahead time is propotional to the distance between the pursuer
//   //and the pursuer; and is inversely proportional to the sum of the
//   //agents' velocities
//   float LookAheadTime = ToPursuer.Length() / 
//                          (this->GetEntity()->GetPhysicalEntity().MaxSpeed() + pEvaderPhysic->Speed());
//   
//   //now flee away from predicted future position of the pursuer
//   return Flee(pEvaderTrans2D->GetPosition() + pEvaderPhysic->Velocity() * LookAheadTime);

	return Vector2F::Zero();
}


//--------------------------- Wander -------------------------------------
//
//  This behavior makes the agent wander about randomly
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::Wander(float elapsedTime_)
{ 
//   //this behavior is dependent on the update rate, so this line must
//   //be included when using time independent framerate.
//   float JitterThisTimeSlice = m_fWanderJitter * elapsedTime_;
// 
//   //first, add a small random vector to the target's position
//   m_vWanderTarget += Vector2F(RandomClamped() * JitterThisTimeSlice,
//                               RandomClamped() * JitterThisTimeSlice);
// 
//   //reproject this new vector back on to a unit circle
//   m_vWanderTarget.Normalize();
// 
//   //increase the length of the vector to the same as the radius
//   //of the wander circle
//   m_vWanderTarget *= m_fWanderRadius;
// 
//   //move the target into a position WanderDist in front of the agent
//   Vector2F target = m_vWanderTarget + Vector2F(m_fWanderDistance, 0);
// 
//   //project the target into world space
//   Vector2F res = Transformation::PointToWorldSpace(target,
//                                        this->GetEntity()->GetPhysicalEntity().Heading(),
//                                        this->GetEntity()->GetPhysicalEntity().Side(), 
//                                        m_Position2D );
// 
//   //and steer towards it
//   return res - m_Position2D; 
	return Vector2F::Zero();
}


//---------------------- ObstacleAvoidance -------------------------------
//
//  Given a vector of CObstacles, this method returns a steering force
//  that will prevent the agent colliding with the closest obstacle
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::ObstacleAvoidance(const std::vector<BaseEntity*>& obstacles)
{
//   //the detection box length is proportional to the agent's velocity
//   m_fDBoxLength = DBoxLength() + 
//                   (this->GetEntity()->GetPhysicalEntity().Speed() / this->GetEntity()->GetPhysicalEntity().MaxSpeed()) *
//                   DBoxLength();
// 
//   std::vector<BaseEntity*> obstaclesWithinViewRange;
// 
//   //tag all obstacles within range of the box for processing
//   //GameInfo::Instance().GetWorld()->TagObstaclesWithinViewRange(GetEntity(), m_dDBoxLength);
//   //iterate through all entities checking for range
//   for (std::vector<BaseEntity *>::const_iterator curEntity = obstacles.cbegin();
// 	  curEntity != obstacles.cend();
// 	  ++curEntity)
//   {
// 	  //first clear any current tag
// 	  //(*curEntity)->UnTag();
// 	  Transform2DComponent *pTrans = (*curEntity)->GetComponentMgr()->GetComponent<Transform2DComponent>();
// 	  PhysicComponent *pPhysic = (*curEntity)->GetComponentMgr()->GetComponent<PhysicComponent>();
// 
// 	  Vector2F to = pTrans->GetPosition() - m_Position2D;
// 
// 	  //the bounding radius of the other is taken into account by adding it 
// 	  //to the range
// 	  float range = m_fDBoxLength + pPhysic->GetRadius();
// 
// 	  //if entity within range, tag for further consideration. (working in
// 	  //distance-squared space to avoid sqrts)
// 	  if ( ((*curEntity) != GetEntity()) && (to.LengthSquared() < range * range))
// 	  {
// 		  obstaclesWithinViewRange.push_back((*curEntity));
// 	  }
//   }//next entity
// 
//   //this will keep track of the closest intersecting obstacle (CIB)
//   BaseEntity* ClosestIntersectingObstacle = nullptr;
//  
//   //this will be used to track the distance to the CIB
//   float DistToClosestIP = MaxFloat;
// 
//   //this will record the transformed local coordinates of the CIB
//   Vector2F LocalPosOfClosestObstacle;
// 
//   std::vector<BaseEntity*>::const_iterator curOb = obstaclesWithinViewRange.begin();
// 
//   while(curOb != obstaclesWithinViewRange.end())
//   {
//     //if the obstacle has been tagged within range proceed
//     //if ((*curOb)->IsTagged())
//     //{
// 		Transform2DComponent *pCurObTrans2D = (*curOb)->GetComponentMgr()->GetComponent<Transform2DComponent>();
// 
// 		//calculate this obstacle's position in local space
// 		Vector2F obPos = pCurObTrans2D->GetPosition();
// 		Vector2F heading = this->GetEntity()->GetPhysicalEntity().Heading();
// 		Vector2F side = this->GetEntity()->GetPhysicalEntity().Side();
// 		Vector2F pos = m_Position2D;
// 
//       Vector2F LocalPos = Transformation::PointToLocalSpace(obPos, heading, side, pos);
// 
//       //if the local position has a negative x value then it must lay
//       //behind the agent. (in which case it can be ignored)
//       if (LocalPos.x >= 0)
//       {
// 		  PhysicComponent *pEvaderPhysic = (*curOb)->GetComponentMgr()->GetComponent<PhysicComponent>();
// 
//         //if the distance from the x axis to the object's position is less
//         //than its radius + half the width of the detection box then there
//         //is a potential intersection.
//         float ExpandedRadius = pEvaderPhysic->GetRadius() + this->GetEntity()->GetPhysicalEntity().GetRadius();
// 
//         if (fabs(LocalPos.y) < ExpandedRadius)
//         {
//           //now to do a line/circle intersection test. The center of the 
//           //circle is represented by (cX, cY). The intersection points are 
//           //given by the formula x = cX +/-sqrt(r^2-cY^2) for y=0. 
//           //We only need to look at the smallest positive value of x because
//           //that will be the closest point of intersection.
//           float cX = LocalPos.x;
//           float cY = LocalPos.y;
//           
//           //we only need to calculate the sqrt part of the above equation once
//           float SqrtPart = sqrt(ExpandedRadius*ExpandedRadius - cY*cY);
// 
//           float ip = cX - SqrtPart;
// 
//           if (ip <= 0.0)
//           {
//             ip = cX + SqrtPart;
//           }
// 
//           //test to see if this is the closest so far. If it is keep a
//           //record of the obstacle and its local coordinates
//           if (ip < DistToClosestIP)
//           {
//             DistToClosestIP = ip;
// 
//             ClosestIntersectingObstacle = *curOb;
// 
//             LocalPosOfClosestObstacle = LocalPos;
//           }         
//         }
//       }
//     //}
// 
//     ++curOb;
//   }
// 
//   //if we have found an intersecting obstacle, calculate a steering 
//   //force away from it
//   Vector2F SteeringForce;
// 
//   if (ClosestIntersectingObstacle)
//   {
// 	  PhysicComponent *pClosestPhysic = ClosestIntersectingObstacle->GetComponentMgr()->GetComponent<PhysicComponent>();
// 
//     //the closer the agent is to an object, the stronger the 
//     //steering force should be
//     float multiplier = 1.0f + (m_fDBoxLength - LocalPosOfClosestObstacle.x) /
//                         m_fDBoxLength;
// 
//     //calculate the lateral force
//     SteeringForce.y = (pClosestPhysic->GetRadius()-
//                        LocalPosOfClosestObstacle.y)  * multiplier;   
// 
//     //apply a braking force proportional to the obstacles distance from
//     //the BaseEntity. 
//     const float BrakingWeight = 0.2f;
// 
//     SteeringForce.x = (pClosestPhysic->GetRadius() - 
//                        LocalPosOfClosestObstacle.x) * 
//                        BrakingWeight;
//   }
// 
//   //finally, convert the steering vector from local to world space
//   return Transformation::VectorToWorldSpace(SteeringForce,
//                             this->GetEntity()->GetPhysicalEntity().Heading(),
//                             this->GetEntity()->GetPhysicalEntity().Side());

	return Vector2F::Zero();
}


//--------------------------- WallAvoidance --------------------------------
//
//  This returns a steering force that will keep the agent away from any
//  walls it may encounter
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::WallAvoidance(const std::vector<Line2D>& walls)
{
  //the feelers are contained in a std::vector, m_Feelers
  CreateFeelers();
  
  float DistToThisIP    = 0.0;
  float DistToClosestIP = MaxFloat;

  //this will hold an index into the vector of walls
  int ClosestWall = -1;

  Vector2F SteeringForce,
            point,         //used for storing temporary info
            ClosestPoint;  //holds the closest intersection point



  Vector2F pos = GetEntity()->GetComponentMgr()->GetComponent<Transform2DComponent>()->GetPosition();

  //examine each feeler in turn
  for (unsigned int flr=0; flr<m_Feelers.size(); ++flr)
  {
    //run through each wall checking for any intersection points
    for (unsigned int w=0; w<walls.size(); ++w)
    {
		if (Geometry::LineIntersection2D(pos,
								m_Feelers[flr],
								walls[w].From(),
								walls[w].To(),
								DistToThisIP,
								point))
		{
			//is this the closest found so far? If so keep a record
			if (DistToThisIP < DistToClosestIP)
			{
				DistToClosestIP = DistToThisIP;

				ClosestWall = w;

				ClosestPoint = point;
			}
		}
    }//next wall

  
    //if an intersection point has been detected, calculate a force  
    //that will direct the agent away
    if (ClosestWall >=0)
    {
      //calculate by what distance the projected position of the agent
      //will overshoot the wall
      Vector2F OverShoot = m_Feelers[flr] - ClosestPoint;

      //create a force in the direction of the wall normal, with a 
      //magnitude of the overshoot
      SteeringForce = walls[ClosestWall].Normal() * OverShoot.Length();
    }

  }//next feeler

  return SteeringForce;
}

//------------------------------- CreateFeelers --------------------------
//
//  Creates the antenna utilized by WallAvoidance
//------------------------------------------------------------------------
void SteeringBehaviorComponent::CreateFeelers()
{
// 	Vector2F pos = GetEntity()->GetComponentMgr()->GetComponent<Transform2DComponent>()->GetPosition();
// 	Vector2F heading = GetEntity()->GetComponentMgr()->GetComponent<PhysicComponent>()->Heading();
// 
//   //feeler pointing straight in front
//   m_Feelers[0] = pos + m_fWallDetectionFeelerLength * heading;
// 
//   //feeler to left
//   Vector2F temp = heading;
//   Transformation::Vec2DRotateAroundOrigin(temp, MATH_PI_DIV_2 * 3.5f);
//   m_Feelers[1] = pos + m_fWallDetectionFeelerLength / 2.0f * temp;
// 
//   //feeler to right
//   temp = heading;
//   Transformation::Vec2DRotateAroundOrigin(temp, MATH_PI_DIV_2 * 0.5f);
//   m_Feelers[2] = pos + m_fWallDetectionFeelerLength / 2.0f * temp;
}


//---------------------------- Separation --------------------------------
//
// this calculates a force repelling from the other neighbors
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::Separation(const std::vector<BaseEntity*>& /*neighbors*/)
{  
  Vector2F SteeringForce;
  Vector2F pos = GetEntity()->GetComponentMgr()->GetComponent<Transform2DComponent>()->GetPosition();

  throw CException("SteeringBehaviorComponent::Separation() not implemented");

  /*
  for (unsigned int a=0; a<neighbors.size(); ++a)
  {
    //make sure this agent isn't included in the calculations and that
    //the agent being examined is close enough. ***also make sure it doesn't
    //include the evade target ***
    if((neighbors[a] != GetEntity()) && neighbors[a]->IsTagged() &&
      (neighbors[a] != m_pTargetAgent1))
    {
      Vector2F ToAgent = pos - neighbors[a]->GetComponentMgr()->GetComponent<Transform2DComponent>()->GetPosition();
	  float l = ToAgent.Length();
	  ToAgent.Normalize();

      //scale the force inversely proportional to the agents distance  
      //from its neighbor.
      SteeringForce += ToAgent / l;
    }
  }*/

  return SteeringForce;
}


//---------------------------- Alignment ---------------------------------
//
//  returns a force that attempts to align this agents heading with that
//  of its neighbors
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::Alignment(const std::vector<BaseEntity*>& /*neighbors*/)
{
  //used to record the average heading of the neighbors
  Vector2F AverageHeading;

  throw CException("SteeringBehaviorComponent::Alignment() not implemented");

  /*
  //used to count the number of vehicles in the neighborhood
  int    NeighborCount = 0;

  //iterate through all the tagged vehicles and sum their heading vectors  
  for (unsigned int a=0; a<neighbors.size(); ++a)
  {
    //make sure *this* agent isn't included in the calculations and that
    //the agent being examined  is close enough ***also make sure it doesn't
    //include any evade target ***
    if((neighbors[a] != GetEntity()) && neighbors[a]->IsTagged() &&
      (neighbors[a] != m_pTargetAgent1))
    {
      AverageHeading += neighbors[a]->GetComponentMgr()->GetComponent<PhysicComponent>()->Heading();
      ++NeighborCount;
    }
  }

  //if the neighborhood contained one or more vehicles, average their
  //heading vectors.
  if (NeighborCount > 0)
  {
    AverageHeading /= (float)NeighborCount;
    AverageHeading -= GetEntity()->GetComponentMgr()->GetComponent<PhysicComponent>()->Heading();
  }*/
  
  return AverageHeading;
}

//-------------------------------- Cohesion ------------------------------
//
//  returns a steering force that attempts to move the agent towards the
//  center of mass of the agents in its immediate area
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::Cohesion(const std::vector<BaseEntity*>& /*neighbors*/)
{
  //first find the center of mass of all the agents
  Vector2F CenterOfMass, SteeringForce;

  throw CException("SteeringBehaviorComponent::Cohesion() not implemented");

  /*
  int NeighborCount = 0;

  //iterate through the neighbors and sum up all the position vectors
  for (unsigned int a=0; a<neighbors.size(); ++a)
  {
	  Transform2DComponent *pTrans2D = neighbors[a]->GetComponentMgr()->GetComponent<Transform2DComponent>();

    //make sure *this* agent isn't included in the calculations and that
    //the agent being examined is close enough ***also make sure it doesn't
    //include the evade target ***
    if((neighbors[a] != GetEntity()) && neighbors[a]->IsTagged() &&
      (neighbors[a] != m_pTargetAgent1))
    {
      CenterOfMass += pTrans2D->GetPosition();
      ++NeighborCount;
    }
  }

  if (NeighborCount > 0)
  {
    //the center of mass is the average of the sum of positions
    CenterOfMass /= (float)NeighborCount;

    //now seek towards that position
    SteeringForce = Seek(CenterOfMass);
  }

  //the magnitude of cohesion is usually much larger than separation or
  //allignment so it usually helps to normalize it.
  SteeringForce.Normalize();*/
  return SteeringForce;
}


/* NOTE: the next three behaviors are the same as the above three, except
          that they use a cell-space partition to find the neighbors
*/


//---------------------------- Separation --------------------------------
//
// this calculates a force repelling from the other neighbors
//
//  USES SPACIAL PARTITIONING
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::SeparationPlus(const std::vector<BaseEntity*>& /*neighbors*/)
{  
   Vector2F SteeringForce;
//   Vector2F pos = GetEntity()->GetComponentMgr()->GetComponent<Transform2DComponent>()->GetPosition();
// 
//   //iterate through the neighbors and sum up all the position vectors
//   for (BaseEntity* pV = GameInfo::Instance().GetWorld()->GetCellSpcEntity()->begin();
//                          !GameInfo::Instance().GetWorld()->GetCellSpcEntity()->end();     
//                        pV = GameInfo::Instance().GetWorld()->GetCellSpcEntity()->next())
//   {    
//     //make sure this agent isn't included in the calculations and that
//     //the agent being examined is close enough
//     if(pV != GetEntity())
//     {
//       Vector2F ToAgent = pos - pV->GetComponentMgr()->GetComponent<Transform2DComponent>()->GetPosition();
// 	  float l = ToAgent.Length();
// 	  ToAgent.Normalize();
// 
//       //scale the force inversely proportional to the agents distance  
//       //from its neighbor.
//       SteeringForce += ToAgent / l;
//     }
// 
//   }

  return SteeringForce;
}
//---------------------------- Alignment ---------------------------------
//
//  returns a force that attempts to align this agents heading with that
//  of its neighbors
//
//  USES SPACIAL PARTITIONING
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::AlignmentPlus(const std::vector<BaseEntity*>& /*neighbors*/)
{
	//This will record the average heading of the neighbors
 	Vector2F AverageHeading;
// 
// 	//This count the number of vehicles in the neighborhood
// 	float    NeighborCount = 0.0f;
// 
// 	//iterate through the neighbors and sum up all the position vectors
// 	for (BaseEntity* pV = GameInfo::Instance().GetWorld()->GetCellSpcEntity()->begin();
// 							!GameInfo::Instance().GetWorld()->GetCellSpcEntity()->end();     
// 						pV = GameInfo::Instance().GetWorld()->GetCellSpcEntity()->next())
// 	{
// 		//make sure *this* agent isn't included in the calculations and that
// 		//the agent being examined  is close enough
// 		if(pV != GetEntity())
// 		{
// 			AverageHeading += pV->GetComponentMgr()->GetComponent<PhysicComponent>()->Heading();
// 			++NeighborCount;
// 		}
// 	}
// 
// 	//if the neighborhood contained one or more vehicles, average their
// 	//heading vectors.
// 	if (NeighborCount > 0.0f)
// 	{
// 		AverageHeading /= NeighborCount;
// 		AverageHeading -= GetEntity()->GetComponentMgr()->GetComponent<PhysicComponent>()->Heading();
// 	}
//   
	return AverageHeading;
}


//-------------------------------- Cohesion ------------------------------
//
//  returns a steering force that attempts to move the agent towards the
//  center of mass of the agents in its immediate area
//
//  USES SPACIAL PARTITIONING
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::CohesionPlus(const std::vector<BaseEntity*>& /*neighbors*/)
{
   //first find the center of mass of all the agents
   Vector2F CenterOfMass, SteeringForce;
//   //Transform2DComponent* pTrans = nullptr;
// 
//   int NeighborCount = 0;
// 
// 	//iterate through the neighbors and sum up all the position vectors
// 	for (BaseEntity* pV = GameInfo::Instance().GetWorld()->GetCellSpcEntity()->begin();
// 							!GameInfo::Instance().GetWorld()->GetCellSpcEntity()->end();     
// 						pV = GameInfo::Instance().GetWorld()->GetCellSpcEntity()->next())
// 	{
// 		//make sure *this* agent isn't included in the calculations and that
// 		//the agent being examined is close enough
// 		if(pV != GetEntity())
// 		{
// 			CenterOfMass += pV->GetComponentMgr()->GetComponent<Transform2DComponent>()->GetPosition();
// 			++NeighborCount;
// 		}
// 	}
// 
// 	if (NeighborCount > 0)
// 	{
// 		//the center of mass is the average of the sum of positions
// 		CenterOfMass /= (float)NeighborCount;
// 
// 		//now seek towards that position
// 		SteeringForce = Seek(CenterOfMass);
// 	}
// 
// 	//the magnitude of cohesion is usually much larger than separation or
// 	//allignment so it usually helps to normalize it.
// 	SteeringForce.Normalize();
	return SteeringForce;
}


//--------------------------- Interpose ----------------------------------
//
//  Given two agents, this method returns a force that attempts to 
//  position the BaseEntity between them
//------------------------------------------------------------------------
CasaEngine::Vector2F SteeringBehaviorComponent::Interpose( BaseEntity* AgentA, BaseEntity* AgentB )
{
// 	Transform2DComponent* pATrans2D = AgentA->GetComponentMgr()->GetComponent<Transform2DComponent>();
// 	//MovingEntity2DComponent* pAMoving = AgentA->GetComponentMgr()->GetComponent<MovingEntity2DComponent>();
// 	PhysicComponent* pAPhysic = AgentA->GetComponentMgr()->GetComponent<PhysicComponent>();
// 
// 	Transform2DComponent* pBTrans2D = AgentB->GetComponentMgr()->GetComponent<Transform2DComponent>();
// 	//MovingEntity2DComponent* pBMoving = AgentB->GetComponentMgr()->GetComponent<MovingEntity2DComponent>();
// 	PhysicComponent* pBPhysic = AgentB->GetComponentMgr()->GetComponent<PhysicComponent>();
// 
//   //first we need to figure out where the two agents are going to be at 
//   //time T in the future. This is approximated by determining the time
//   //taken to reach the mid way point at the current time at at max speed.
//   Vector2F MidPoint = (pATrans2D->GetPosition() + pBTrans2D->GetPosition()) / 2.0f;
// 
//   float TimeToReachMidPoint = m_Position2D.DistanceSq(MidPoint) /
//                                this->GetEntity()->GetPhysicalEntity().MaxSpeed();
// 
//   //now we have T, we assume that agent A and agent B will continue on a
//   //straight trajectory and extrapolate to get their future positions
//   Vector2F APos = pATrans2D->GetPosition() + pAPhysic->Velocity() * TimeToReachMidPoint;
//   Vector2F BPos = pBTrans2D->GetPosition() + pBPhysic->Velocity() * TimeToReachMidPoint;
// 
//   //calculate the mid point of these predicted positions
//   MidPoint = (APos + BPos) / 2.0f;
// 
//   //then steer to Arrive at it
//   return Arrive(MidPoint, FAST);

	return Vector2F::Zero();
}

//--------------------------- Hide ---------------------------------------
//
//------------------------------------------------------------------------
CasaEngine::Vector2F SteeringBehaviorComponent::Hide( BaseEntity* hunter, 
							const std::vector<BaseEntity*>& obstacles )
{
//   float    DistToClosest = MaxFloat;
//   Vector2F BestHidingSpot;
// 
//   Transform2DComponent* pHunterTransform2D = hunter->GetComponentMgr()->GetComponent<Transform2DComponent>();
//   //MovingEntity2DComponent* pHunterMoving = hunter->GetComponentMgr()->GetComponent<MovingEntity2DComponent>();
//   //PhysicComponent* pHunterPhysic = hunter->GetComponentMgr()->GetComponent<PhysicComponent>();
// 
//   std::vector<BaseEntity*>::const_iterator curOb = obstacles.begin();
//   std::vector<BaseEntity*>::const_iterator closest;
// 
//   while(curOb != obstacles.end())
//   {
// 	  Transform2DComponent* pObtTransform2D = (*curOb)->GetComponentMgr()->GetComponent<Transform2DComponent>();
// 	  PhysicComponent* pObtPhysic = (*curOb)->GetComponentMgr()->GetComponent<PhysicComponent>();
// 
// 	//calculate the position of the hiding spot for this obstacle
// 	Vector2F HidingSpot = GetHidingPosition(pObtTransform2D->GetPosition(),
// 												pObtPhysic->GetRadius(),
// 												pHunterTransform2D->GetPosition());
//             
// 	//work in distance-squared space to find the closest hiding
// 	//spot to the agent
// 	float dist = HidingSpot.DistanceSq(m_Position2D);
// 
// 	if (dist < DistToClosest)
// 	{
// 		DistToClosest = dist;
// 
// 		BestHidingSpot = HidingSpot;
// 
// 		closest = curOb;
// 	}  
//             
// 	++curOb;
// 
//   }//end while
//   
//   //if no suitable obstacles found then Evade the hunter
//   if (DistToClosest == MaxFloat)
//   {
//     return Evade(hunter);
//   }
//       
//   //else use Arrive on the hiding spot
//   return Arrive(BestHidingSpot, FAST);

	return Vector2F::Zero();
}

//------------------------- GetHidingPosition ----------------------------
//
//  Given the position of a hunter, and the position and radius of
//  an obstacle, this method calculates a position DistanceFromBoundary 
//  away from its bounding radius and directly opposite the hunter
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::GetHidingPosition(const Vector2F& posOb,
                                              const float     radiusOb,
                                              const Vector2F& posHunter)
{
  //calculate how far away the agent is to be from the chosen obstacle's
  //bounding radius
  const float DistanceFromBoundary = 30.0f;
  float       DistAway    = radiusOb + DistanceFromBoundary;

  //calculate the heading toward the object from the hunter
  Vector2F ToOb = posOb - posHunter;
  ToOb.Normalize();

  //scale it to size and add to the obstacles position to get
  //the hiding spot.
  return (ToOb * DistAway) + posOb;
}


//------------------------------- FollowPath -----------------------------
//
//  Given a series of Vector2Ds, this method produces a force that will
//  move the agent along the waypoints in order. The agent uses the
// 'Seek' behavior to move to the next waypoint - unless it is the last
//  waypoint, in which case it 'Arrives'
//------------------------------------------------------------------------
Vector2F SteeringBehaviorComponent::FollowPath()
{ 
	throw CNotImplementedException("SteeringBehaviorComponent::FollowPath() not implemented");

  //move to next target if close enough to current target (working in
  //distance squared space)
  /*if(Vec2DDistanceSq(m_pPath->CurrentWaypoint(), m_Position2D) <
     m_fWaypointSeekDistSq)
  {
    m_pPath->SetNextWaypoint();
  }

  if (!m_pPath->Finished())
  {
    return Seek(m_pPath->CurrentWaypoint());
  }

  else
  {
    return Arrive(m_pPath->CurrentWaypoint(), normal);
  }*/
	return Vector2F();
}

//------------------------- Offset Pursuit -------------------------------
//
//  Produces a steering force that keeps a BaseEntity at a specified offset
//  from a leader BaseEntity
//------------------------------------------------------------------------
CasaEngine::Vector2F SteeringBehaviorComponent::OffsetPursuit(BaseEntity* leader, const Vector2F offset)
{
	Transform3DComponent* pLeaderTransform2D = leader->GetComponentMgr()->GetComponent<Transform3DComponent>();
	//MovingEntity2DComponent* pLeaderMoving = leader->GetComponentMgr()->GetComponent<MovingEntity2DComponent>();
	PhysicalEntity &pLeaderPhysic = leader->GetPhysicalEntity();

	//calculate the offset's position in world space
	Vector3F WorldOffsetPos;
// 	Vector2F WorldOffsetPos = Transformation::PointToWorldSpace(offset,
// 													pLeaderPhysic.Heading(),
// 													pLeaderPhysic.Side(),
// 													pLeaderTransform2D->GetPosition());

	Vector2F ToOffset = WorldOffsetPos - m_Position2D;

	//the lookahead time is proportional to the distance between the leader
	//and the pursuer; and is inversely proportional to the sum of both
	//agent's velocities
	float LookAheadTime = ToOffset.Length() / 
						(this->GetEntity()->GetPhysicalEntity().MaxSpeed() + pLeaderPhysic.Speed());
  
	//now Arrive at the predicted future position of the offset
	//return Arrive(WorldOffsetPos + pLeaderPhysic.Velocity() * LookAheadTime, FAST);
	return Vector2F::Zero();
}

//----------------------------- RenderAids -------------------------------
//
//------------------------------------------------------------------------
void SteeringBehaviorComponent::RenderAids( )
{ 
  /*
  gdi->TransparentText();
  gdi->TextColor(Cgdi::grey);

  int NextSlot = 0; int SlotSize = 20;

  if (KEYDOWN(VK_INSERT)){GetEntity()->SetMaxForce(this->GetEntity()->GetPhysicalEntity().MaxForce() + 1000.0f*GetEntity()->TimeElapsed());} 
  if (KEYDOWN(VK_DELETE)){if (this->GetEntity()->GetPhysicalEntity().MaxForce() > 0.2f) GetEntity()->SetMaxForce(this->GetEntity()->GetPhysicalEntity().MaxForce() - 1000.0f*GetEntity()->TimeElapsed());}
  if (KEYDOWN(VK_HOME)){GetEntity()->SetMaxSpeed(GetEntity()->MaxSpeed() + 50.0f*GetEntity()->TimeElapsed());}
  if (KEYDOWN(VK_END)){if (GetEntity()->MaxSpeed() > 0.2f) GetEntity()->SetMaxSpeed(GetEntity()->MaxSpeed() - 50.0f*GetEntity()->TimeElapsed());}

  if (this->GetEntity()->GetPhysicalEntity().MaxForce() < 0) GetEntity()->SetMaxForce(0.0f);
  if (GetEntity()->MaxSpeed() < 0) GetEntity()->SetMaxSpeed(0.0f);
  
  if (GetEntity()->ID() == 0){ gdi->TextAtPos(5,NextSlot,"MaxForce(Ins/Del):"); gdi->TextAtPos(160,NextSlot,ttos(this->GetEntity()->GetPhysicalEntity().MaxForce()/Prm.SteeringForceTweaker)); NextSlot+=SlotSize;}
  if (GetEntity()->ID() == 0){ gdi->TextAtPos(5,NextSlot,"MaxSpeed(Home/End):"); gdi->TextAtPos(160,NextSlot,ttos(GetEntity()->MaxSpeed()));NextSlot+=SlotSize;}

  //render the steering force
  if (GameInfo::Instance().GetWorld()->RenderSteeringForce())
  {  
    gdi->RedPen();
    Vector2F F = (m_vSteeringForce / Prm.SteeringForceTweaker) * Prm.VehicleScale ;
    gdi->Line(m_Position2D, m_Position2D + F);
  }

  //render wander stuff if relevant
  if (On(wander) && GameInfo::Instance().GetWorld()->RenderWanderCircle())
  {    
    if (KEYDOWN('F')){m_fWanderJitter+=1.0f*GetEntity()->TimeElapsed(); Clamp(m_fWanderJitter, 0.0f, 100.0f);}
    if (KEYDOWN('V')){m_fWanderJitter-=1.0f*GetEntity()->TimeElapsed(); Clamp(m_fWanderJitter, 0.0f, 100.0f );}
    if (KEYDOWN('G')){m_fWanderDistance+=2.0f*GetEntity()->TimeElapsed(); Clamp(m_fWanderDistance, 0.0f, 50.0f);}
    if (KEYDOWN('B')){m_fWanderDistance-=2.0f*GetEntity()->TimeElapsed(); Clamp(m_fWanderDistance, 0.0f, 50.0f);}
    if (KEYDOWN('H')){m_fWanderRadius+=2.0f*GetEntity()->TimeElapsed(); Clamp(m_fWanderRadius, 0.0f, 100.0f);}
    if (KEYDOWN('N')){m_fWanderRadius-=2.0f*GetEntity()->TimeElapsed(); Clamp(m_fWanderRadius, 0.0f, 100.0f);}

 
    if (GetEntity()->ID() == 0){ gdi->TextAtPos(5,NextSlot, "Jitter(F/V): "); gdi->TextAtPos(160, NextSlot, ttos(m_fWanderJitter));NextSlot+=SlotSize;}
    if (GetEntity()->ID() == 0) {gdi->TextAtPos(5,NextSlot,"Distance(G/B): "); gdi->TextAtPos(160, NextSlot, ttos(m_fWanderDistance));NextSlot+=SlotSize;}
    if (GetEntity()->ID() == 0) {gdi->TextAtPos(5,NextSlot,"Radius(H/N): ");gdi->TextAtPos(160, NextSlot,  ttos(m_fWanderRadius));NextSlot+=SlotSize;}

    
    //calculate the center of the wander circle
    Vector2F m_vTCC = PointToWorldSpace(Vector2F(m_fWanderDistance*GetEntity()->BRadius(), 0),
                                         GetEntity()->Heading(),
                                         GetEntity()->Side(),
                                         m_Position2D);
    //draw the wander circle
    gdi->GreenPen();
    gdi->HollowBrush();
    gdi->Circle(m_vTCC, m_fWanderRadius*GetEntity()->BRadius()); 

    //draw the wander target
    gdi->RedPen();
    gdi->Circle(PointToWorldSpace((m_vWanderTarget + Vector2F(m_fWanderDistance,0))*GetEntity()->BRadius(),
                                  GetEntity()->Heading(),
                                  GetEntity()->Side(),
                                  m_Position2D), 3);                                  
  }

  //render the detection box if relevant
  if (GameInfo::Instance().GetWorld()->RenderDetectionBox())
  {
    gdi->GreyPen();

    //a vertex buffer rqd for drawing the detection box
    static std::vector<Vector2F> box(4);

    float length = Prm.MinDetectionBoxLength + 
                  (GetEntity()->Speed()/GetEntity()->MaxSpeed()) *
                  Prm.MinDetectionBoxLength;

    //verts for the detection box buffer
    box[0] = Vector2F(0,GetEntity()->BRadius());
    box[1] = Vector2F(length, GetEntity()->BRadius());
    box[2] = Vector2F(length, -GetEntity()->BRadius());
    box[3] = Vector2F(0, -GetEntity()->BRadius());
 
  
    if (!GetEntity()->isSmoothingOn())
    {
      box = WorldTransform(box,m_Position2D,GetEntity()->Heading(),GetEntity()->Side());
      gdi->ClosedShape(box);
    }
    else
    {
      box = WorldTransform(box,m_Position2D,GetEntity()->SmoothedHeading(),GetEntity()->SmoothedHeading().Perp());
      gdi->ClosedShape(box);
    } 


    //////////////////////////////////////////////////////////////////////////
    //the detection box length is proportional to the agent's velocity
  m_dDBoxLength = Prm.MinDetectionBoxLength + 
                  (GetEntity()->Speed()/GetEntity()->MaxSpeed()) *
                  Prm.MinDetectionBoxLength;

  //tag all obstacles within range of the box for processing
  GameInfo::Instance().GetWorld()->TagObstaclesWithinViewRange(GetEntity(), m_dDBoxLength);

  //this will keep track of the closest intersecting obstacle (CIB)
  BaseEntity* ClosestIntersectingObstacle = nullptr;
 
  //this will be used to track the distance to the CIB
  float DistToClosestIP = MaxDouble;

  //this will record the transformed local coordinates of the CIB
  Vector2F LocalPosOfClosestObstacle;

  std::vector<BaseEntity*>::const_iterator curOb = GameInfo::Instance().GetWorld()->Obstacles().begin();

  while(curOb != GameInfo::Instance().GetWorld()->Obstacles().end())
  {
    //if the obstacle has been tagged within range proceed
    if ((*curOb)->IsTagged())
    {
      //calculate this obstacle's position in local space
      Vector2F LocalPos = PointToLocalSpace((*curOb)->Pos(),
                                             GetEntity()->Heading(),
                                             GetEntity()->Side(),
                                             m_Position2D);

      //if the local position has a negative x value then it must lay
      //behind the agent. (in which case it can be ignored)
      if (LocalPos.x >= 0)
      {
        //if the distance from the x axis to the object's position is less
        //than its radius + half the width of the detection box then there
        //is a potential intersection.
        if (fabs(LocalPos.y) < ((*curOb)->BRadius() + GetEntity()->BRadius()))
        {
          gdi->ThickRedPen();
          gdi->ClosedShape(box);        
        }
      }
    }

    ++curOb;
  }


/////////////////////////////////////////////////////
  }

  //render the wall avoidnace feelers
  if (On(wall_avoidance) && GameInfo::Instance().GetWorld()->RenderFeelers())
  {
    gdi->OrangePen();

    for (unsigned int flr=0; flr<m_Feelers.size(); ++flr)
    {

      gdi->Line(m_Position2D, m_Feelers[flr]);
    }            
  }  

  //render path info
  if (On(follow_path) && GameInfo::Instance().GetWorld()->RenderPath())
  {
    m_pPath->Render();
  }

  
  if (On(separation))
  {
    if (GetEntity()->ID() == 0){ gdi->TextAtPos(5, NextSlot, "Separation(S/X):");gdi->TextAtPos(160,NextSlot, ttos(m_fWeightSeparation/Prm.SteeringForceTweaker));NextSlot+=SlotSize;}

    if (KEYDOWN('S')){m_fWeightSeparation += 200*GetEntity()->TimeElapsed(); Clamp(m_fWeightSeparation, 0.0f, 50.0f * Prm.SteeringForceTweaker);}
    if (KEYDOWN('X')){m_fWeightSeparation -= 200*GetEntity()->TimeElapsed();Clamp(m_fWeightSeparation, 0.0f, 50.0f * Prm.SteeringForceTweaker);}
  }

  if (On(allignment))
  {
    if (GetEntity()->ID() == 0) {gdi->TextAtPos(5, NextSlot, "Alignment(A/Z):"); gdi->TextAtPos(160, NextSlot, ttos(m_fWeightAlignment/Prm.SteeringForceTweaker));NextSlot+=SlotSize;}

    if (KEYDOWN('A')){m_fWeightAlignment += 200*GetEntity()->TimeElapsed();Clamp(m_fWeightAlignment, 0.0f, 50.0f * Prm.SteeringForceTweaker);}
    if (KEYDOWN('Z')){m_fWeightAlignment -= 200*GetEntity()->TimeElapsed();Clamp(m_fWeightAlignment, 0.0f, 50.0f * Prm.SteeringForceTweaker);}
  }

  if (On(cohesion))
  {
    if (GetEntity()->ID() == 0) {gdi->TextAtPos(5, NextSlot, "Cohesion(D/C):"); gdi->TextAtPos(160, NextSlot, ttos(m_fWeightCohesion/Prm.SteeringForceTweaker));NextSlot+=SlotSize;}
    if (KEYDOWN('D')){m_fWeightCohesion += 200*GetEntity()->TimeElapsed();Clamp(m_fWeightCohesion, 0.0f, 50.0f * Prm.SteeringForceTweaker);}
    if (KEYDOWN('C')){m_fWeightCohesion -= 200*GetEntity()->TimeElapsed();Clamp(m_fWeightCohesion, 0.0f, 50.0f * Prm.SteeringForceTweaker);}
  }

  if (On(follow_path))
  { 
    float sd = sqrt(m_fWaypointSeekDistSq);
    if (GetEntity()->ID() == 0){ gdi->TextAtPos(5, NextSlot, "SeekDistance(D/C):");gdi->TextAtPos(160, NextSlot,ttos(sd));NextSlot+=SlotSize;}
    
    if (KEYDOWN('D')){m_fWaypointSeekDistSq += 1.0;}
    if (KEYDOWN('C')){m_fWaypointSeekDistSq -= 1.0; Clamp(m_fWaypointSeekDistSq, 0.0f, 400.0f);}
  }  
  */
}


}
