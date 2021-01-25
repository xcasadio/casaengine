#ifndef RIGIDBODY_H_
#define RIGIDBODY_H_

#include "CA_Export.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	/**
	 *
	 */
	struct CA_EXPORT RigidBody :
		public AllocatedObject<RigidBody>
	{
		float			mass;

		IShape* pCollisionShape;
		Vector3F		localInertia;
		float			linearDamping;
		float			angularDamping;

		///best simulation results when friction is non-zero
		float			friction;
		///the rollingFriction prevents rounded shapes, such as spheres, cylinders and capsules from rolling forever.
		///See Bullet/Demos/RollingFrictionDemo for usage
		float			rollingFriction;
		float			restitution;
		float			linearSleepingThreshold;
		float			angularSleepingThreshold;

		//Additional damping can help avoiding lowpass jitter motion, help stability for ragdolls etc.
		//Such damping is undesirable, so once the overall simulation quality of the rigid body dynamics system has improved, this should become obsolete
		bool			additionalDamping;
		float			additionalDampingFactor;
		float			additionalLinearDampingThresholdSqr;
		float			additionalAngularDampingThresholdSqr;
		float			additionalAngularDampingFactor;

		RigidBody() :
			mass(1.0f),
			pCollisionShape(nullptr),
			localInertia(Vector3F::Zero()),
			linearDamping(0.f),
			angularDamping(0.f),
			friction(0.5f),
			rollingFriction(0.0f),
			restitution(0.f),
			linearSleepingThreshold(0.8f),
			angularSleepingThreshold(1.f),
			additionalDamping(false),
			additionalDampingFactor(0.005f),
			additionalLinearDampingThresholdSqr(0.01f),
			additionalAngularDampingThresholdSqr(0.01f),
			additionalAngularDampingFactor(0.01f)
		{}
	};
}

#endif // RIGIDBODY_H_
