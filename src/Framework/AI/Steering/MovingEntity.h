#pragma once
//------------------------------------------------------------------------
//
//  Name:   MovingEntity.h
//
//  Desc:   A base class defining an entity that moves. The entity has 
//          a local coordinate system and members for defining its
//          mass and velocity.
//
//  Author: Mat Buckland (fup@ai-junkie.com)
//
//------------------------------------------------------------------------

#include "Entities/BaseEntity.h"
#include "Maths/Vector2.h"
#include "Maths/Math.h"
#include "Maths/Matrix3.h"

namespace CasaEngine
{

	class MovingEntity : public BaseEntity
	{
	protected:

		Vector2    m_vVelocity;

		//a normalized vector pointing in the direction the entity is heading. 
		Vector2    m_vHeading;

		//a vector perpendicular to the heading vector
		Vector2    m_vSide;

		float      m_fMass;

		//the maximum speed this entity may travel at.
		float      m_fMaxSpeed;

		//the maximum force this entity can produce to power itself 
		//(think rockets and thrust)
		float      m_fMaxForce;

		//the maximum rate (radians per second)this MovingEntity can rotate         
		float      m_fMaxTurnRate;

	public:


		MovingEntity(Vector2 position,
			float   radius,
			Vector2 velocity,
			float   max_speed,
			Vector2 heading,
			float   mass,
			Vector2 scale,
			float   turn_rate,
			float   max_force) :
			m_vHeading(heading),
			m_vVelocity(velocity),
			m_fMass(mass),
			m_vSide(m_vHeading.GetOrthogonal()),
			m_fMaxSpeed(max_speed),
			m_fMaxTurnRate(turn_rate),
			m_fMaxForce(max_force)
		{
			//m_vPosition = position;
			//m_fBoundingRadius = radius; 
			//m_vScale = scale;
		}


		virtual ~MovingEntity() {}

		//accessors
		Vector2  Velocity()const { return m_vVelocity; }
		void      SetVelocity(const Vector2& NewVel) { m_vVelocity = NewVel; }

		float    Mass()const { return m_fMass; }

		Vector2  Side()const { return m_vSide; }

		float    MaxSpeed()const { return m_fMaxSpeed; }
		void      SetMaxSpeed(float new_speed) { m_fMaxSpeed = new_speed; }

		float    MaxForce()const { return m_fMaxForce; }
		void      SetMaxForce(float mf) { m_fMaxForce = mf; }

		bool      IsSpeedMaxedOut()const { return m_fMaxSpeed * m_fMaxSpeed >= m_vVelocity.LengthSquared(); }
		float    Speed()const { return m_vVelocity.Length(); }
		float    SpeedSq()const { return m_vVelocity.LengthSquared(); }

		Vector2  Heading()const { return m_vHeading; }
		void      SetHeading(Vector2 new_heading);
		bool      RotateHeadingToFacePosition(Vector2 target);

		float    MaxTurnRate()const { return m_fMaxTurnRate; }
		void      SetMaxTurnRate(float val) { m_fMaxTurnRate = val; }

	};


	//--------------------------- RotateHeadingToFacePosition ---------------------
	//
	//  given a target position, this method rotates the entity's heading and
	//  side vectors by an amount not greater than m_fMaxTurnRate until it
	//  directly faces the target.
	//
	//  returns true when the heading is facing in the desired direction
	//-----------------------------------------------------------------------------
	inline bool MovingEntity::RotateHeadingToFacePosition(Vector2 target)
	{
		Vector2 toTarget = target - m_vPosition;
		toTarget.Normalize();

		float dot = m_vHeading.Dot(toTarget);

		//some compilers lose accuracy so the value is clamped to ensure it
		//remains valid for the acos
		Clamp(dot, -1, 1);

		//first determine the angle between the heading vector and the target
		float angle = acos(dot);

		//return true if the player is facing the target
		if (angle < 0.00001f) return true;

		//clamp the amount to turn to the max turn rate
		if (angle > m_fMaxTurnRate) angle = m_fMaxTurnRate;

		//The next few lines use a rotation matrix to rotate the player's heading
		//vector accordingly
		Matrix3 RotationMatrix;

		//notice how the direction of rotation has to be determined when creating
		//the rotation matrix
		RotationMatrix.Rotate(angle * m_vHeading.Sign(toTarget));
		RotationMatrix.TransformVector(m_vHeading);
		RotationMatrix.TransformVector(m_vVelocity);

		//finally recreate m_vSide
		m_vSide = m_vHeading.GetOrthogonal();

		return false;
	}


	//------------------------- SetHeading ----------------------------------------
	//
	//  first checks that the given heading is not a vector of zero length. If the
	//  new heading is valid this fumction sets the entity's heading and side 
	//  vectors accordingly
	//-----------------------------------------------------------------------------
	inline void MovingEntity::SetHeading(Vector2 new_heading)
	{
		CA_ASSERT((new_heading.LengthSquared() - 1.0f) < 0.00001f,
			"MovingEntity::SetHeading() : don't use a vector equal to Vector::Zero");

		m_vHeading = new_heading;

		//the side vector must always be perpendicular to the heading
		m_vSide = m_vHeading.GetOrthogonal();
	}

}
