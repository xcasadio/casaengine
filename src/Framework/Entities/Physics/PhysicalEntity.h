#pragma once

#include "CA_Export.h"

#include <iosfwd>
#include <string>
#include "Maths/Vector3.h"
#include "Physics/PhysicsObjectContainer.h"
#include "Sprite/Sprite.h"
#include <map>
#include <vector>
#include "GameTime.h"

namespace CasaEngine
{
	class BaseEntity;

	class CA_EXPORT PhysicalEntity
	{
	private:
		Vector3    m_vVelocity;

		//a normalized vector pointing in the direction the entity is heading. 
		Vector3    m_vHeading;

		//a vector perpendicular to the heading vector
		Vector3    m_vSide; 

		float       m_fMass;

		//the maximum speed this entity may travel at.
		float       m_fMaxSpeed;

		//the maximum force this entity can produce to power itself 
		//(think rockets and thrust)
		float        m_fMaxForce;

		//the maximum rate (radians per second)this vehicle can rotate         
		float       m_fMaxTurnRate;

		std::vector<ICollisionObjectContainer *> m_CollisionObjectContainers;
		IRigidBodyContainer *m_pRigidBody;

		// Sprite ID, list of physics object
		std::map<std::string, std::vector<ICollisionObjectContainer *> > m_SpriteCollisionObjects;
		std::string m_LastSpriteID;

		BaseEntity *m_pEntity;

	public:
		PhysicalEntity(BaseEntity *pEntity_);
		~PhysicalEntity();

		void Update(GameTime time_);

		IRigidBodyContainer *GetRigidBody();
		void SetRigidBody(IRigidBodyContainer *val_);

		//accessors
		Vector3  Velocity()const;
		void      SetVelocity(const Vector3& NewVel);

		float     Mass() const;
		void      Mass(float mass_);

		Vector3  Side() const;
		void      Side(Vector3 side_);

		float     MaxSpeed() const;                     
		void      SetMaxSpeed(float new_speed);

		float     MaxForce() const;
		void      SetMaxForce(float mf);

		bool      IsSpeedMaxedOut()const;
		float     Speed() const;
		float     SpeedSq() const;

		Vector3  Heading() const;
		void      SetHeading(Vector3 new_heading);
		bool      RotateHeadingToFacePosition(Vector3 target);

		float     MaxTurnRate() const;
		void      SetMaxTurnRate(float val);

		//entities should be able to read/write their data to a stream
		void Write(std::ostream&  os);
		void Read (std::ifstream& is);
	};

}
